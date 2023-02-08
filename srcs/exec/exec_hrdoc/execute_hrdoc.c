/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_hrdoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 13:32:48 by oboutarf          #+#    #+#             */
/*   Updated: 2023/02/08 23:19:33 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	gather_usr_input(char *content, t_mshell *mshell)
{
	free(mshell->tkn->tkn);
	mshell->tkn->tkn = content;
	return (1);
}

int	dup_expander___hrdoc(t_mshell *mshell, char *exptval, int n_tp)
{
	int	i;

	i = 0;
	free(mshell->expd->types[n_tp]);
	mshell->expd->types[n_tp] = NULL;
	mshell->expd->types[n_tp] = malloc(sizeof(char) * (ft_strlen(exptval) + 1));
	if (!mshell->expd->types[n_tp])
		return (0);
	while (exptval[i])
	{
		mshell->expd->types[n_tp][i] = exptval[i];
		i++;
	}
	mshell->expd->types[n_tp][i] = '\0';
	return (1);
}

int	lens_types_expd__hrdoc(char *usr_input)
{
	int	cuts;
	int	i;

	i = 0;
	cuts = 0;
	while (usr_input[i])
	{
		if (usr_input[i] == EXPAND)
		{
			i += 1;
			while (usr_input[i] && usr_input[i] != DOUBLE_QUOTE
				&& usr_input[i] != SINGLE_QUOTE && usr_input[i] != EXPAND
				&& usr_input[i] != '\n' && usr_input[i] != ' ')
				i++;
			cuts++;
		}
		else if (usr_input[i] != EXPAND)
		{
			while (usr_input[i] && usr_input[i] != EXPAND)
				i++;
			cuts++;
		}
	}
	return (cuts);
}

int	alloc__hrdoc_for_join(t_mshell *mshell)
{
	int	n_tp;
	int	i0;
	int	i1;

	i1 = 0;
	n_tp = 0;
	while (mshell->expd->types[n_tp])
	{
		i0 = 0;
		while (mshell->expd->types[n_tp][i0])
			i0++;
		i1 += i0;
		n_tp++;
	}
	return (i1);
}

int	joinit_heredoc(t_mshell *mshell, char **new_token, int n_tp, int *i1)
{
	int	i0;

	i0 = 0;
	while (mshell->expd->types[n_tp][i0])
	{
		(*new_token)[*i1] = mshell->expd->types[n_tp][i0];
		i0++;
		(*i1)++;
	}
	return (1);
}

char	*join_types_expanded__hrdoc(t_mshell *mshell)
{
	char	*new_token;
	int		n_tp;
	int		i1;

	n_tp = 0;
	i1 = alloc__hrdoc_for_join(mshell);
	new_token = malloc(sizeof(char) * (i1 + 1));
	if (!new_token)
		return (NULL);
	i1 = 0;
	while (mshell->expd->types[n_tp])
	{
		joinit_heredoc(mshell, &new_token, n_tp, &i1);
		if (mshell->expd->types[n_tp][0])
			free(mshell->expd->types[n_tp]);
		n_tp++;
	}
	new_token[i1] = '\0';
	free(mshell->expd->types);
	return (new_token);
}

int	check_expander__hrdoc(char *expander, t_mshell *mshell, int n_tp)
{
	t_expt	*head;

	head = mshell->expt;
	while (mshell->expt->next)
	{
		if (!ft_strcmp(expander, mshell->expt->exptvar))
		{
			if (!dup_expander___hrdoc(mshell, mshell->expt->value, n_tp))
				return (0);
			mshell->expt = head;
			return (1);
		}
		mshell->expt = mshell->expt->next;
	}
	free(mshell->expd->types[n_tp]);
	mshell->expd->types[n_tp] = "";
	mshell->expt = head;
	return (1);
}

int	make_expands_types__hrdoc(t_mshell *mshell, int n_tp)
{
	if (mshell->expd->types[n_tp][0] == EXPAND
		&& !mshell->expd->types[n_tp][0 + 1])
		return (1);
	else if (mshell->expd->types[n_tp][0] == EXPAND)
		check_expander__hrdoc(&mshell->expd->types[n_tp][1], mshell, n_tp);
	return (1);
}

int	types_expd_cut_expander__hrdoc(t_mshell *mshell, char *usr_input, \
	int *n_tp, int *i)
{
	int	j;

	i[1] = i[0];
	i[0] += 1;
	while (usr_input[i[0]] && usr_input[i[0]] != DOUBLE_QUOTE \
		&& usr_input[i[0]] != SINGLE_QUOTE && usr_input[i[0]] != EXPAND \
		&& usr_input[i[0]] != '\n' && usr_input[i[0]] != ' ')
		i[0]++;
	mshell->expd->types[*n_tp] = malloc(sizeof(char) * (i[0] - i[1]) + 1);
	if (!mshell->expd->types[*n_tp])
		return (0);
	j = 0;
	while (usr_input[i[1]] && i[1] < i[0])
	{
		mshell->expd->types[*n_tp][j] = usr_input[i[1]];
		i[1]++;
		j++;
	}
	mshell->expd->types[*n_tp][j] = '\0';
	(*n_tp)++;
	return (1);
}

int	types_expd_cut_usr_input__hrdoc(t_mshell *mshell, char *usr_input, \
	int *n_tp, int *i)
{
	int	j;

	while (usr_input[i[0]] && usr_input[i[0]] != EXPAND)
		i[0]++;
	mshell->expd->types[*n_tp] = malloc(sizeof(char) * (i[0] - i[1]) + 1);
	if (!mshell->expd->types[*n_tp])
		return (0);
	j = 0;
	while (usr_input[i[1]] && i[1] < i[0])
	{
		mshell->expd->types[*n_tp][j] = usr_input[i[1]];
		i[1]++;
		j++;
	}
	mshell->expd->types[*n_tp][j] = '\0';
	(*n_tp)++;
	return (1);
}

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
