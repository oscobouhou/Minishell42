/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_hrdoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 13:32:48 by oboutarf          #+#    #+#             */
/*   Updated: 2023/02/08 23:28:55 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	types_expd_cut__hrdoc(t_mshell *mshell, char *usr_input, int n_tp)
{
	int	i[2];

	i[0] = 0;
	i[1] = 0;
	while (usr_input[i[0]])
	{
		if (usr_input[i[0]] == EXPAND)
			types_expd_cut_expander__hrdoc(mshell, usr_input, &n_tp, i);
		else if (usr_input[i[0]] != EXPAND)
			types_expd_cut_usr_input__hrdoc(mshell, usr_input, &n_tp, i);
	}
	return (1);
}

int	hrdoc_expander(char **usr_input, t_mshell *mshell)
{
	int	n_tp;

	n_tp = lens_types_expd__hrdoc((*usr_input));
	mshell->expd->types = malloc(sizeof(char *) * (n_tp + 1));
	if (!mshell->expd->types)
		return (0);
	mshell->expd->types[n_tp] = NULL;
	n_tp = 0;
	types_expd_cut__hrdoc(mshell, (*usr_input), n_tp);
	while (mshell->expd->types[n_tp])
	{
		make_expands_types__hrdoc(mshell, n_tp);
		n_tp++;
	}
	free((*usr_input));
	(*usr_input) = NULL;
	(*usr_input) = join_types_expanded__hrdoc(mshell);
	if (!usr_input)
		return (0);
	return (1);
}

int	eof_err_heredoc(t_mshell *mshell, int l)
{
	char	*line;

	line = ft_itoa(l);
	ft_putstr_fd(2, "minishell: warning: here-document at line ");
	ft_putstr_fd(2, line);
	free(line);
	ft_putchar(32);
	ft_putstr_fd(2, "delimited by end-of-file (wanted `");
	ft_putstr_fd(2, mshell->tkn->tkn);
	ft_putstr_fd(2, "')\n");
	return (1);
}

int	execute_hrdoc(t_mshell *mshell, int expander)
{
	char	*usr_input;
	int		line;
	int		p;

	p = -42;
	line = 0;
	if (mshell->heredoc->pipe_heredoc[0] != -42)
		close(mshell->heredoc->pipe_heredoc[0]);
	p = pipe(mshell->heredoc->pipe_heredoc);
	if (p == -1)
		return (dprintf(2, "\tpipe: creation failure\n"));
	while (1)
	{
		usr_input = readline("> ");
		if (!check_eof(usr_input))
		{
			close(mshell->heredoc->pipe_heredoc[1]);
			return (eof_err_heredoc(mshell, line), 1);
		}
		if (!ft_strcmp(usr_input, mshell->tkn->tkn))
		{
			if (usr_input)
				free(usr_input);
			close(mshell->heredoc->pipe_heredoc[1]);
			break ;
		}
		if (expander == -42)
			hrdoc_expander(&usr_input, mshell);
		write(mshell->heredoc->pipe_heredoc[1], usr_input, \
		ft_strlen(usr_input));
		write(mshell->heredoc->pipe_heredoc[1], "\n", 1);
		line++;
		free(usr_input);
	}
	return (1);
}
