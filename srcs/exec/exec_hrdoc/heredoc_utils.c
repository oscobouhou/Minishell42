/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 09:27:51 by oboutarf          #+#    #+#             */
/*   Updated: 2023/02/10 15:21:35 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	eof_heredoc(char *usr_input, t_mshell *mshell, int line)
{
	if (!check_eof(usr_input))
	{
		close(mshell->heredoc->pipe_heredoc[1]);
		return (eof_err_heredoc(mshell, line), 1);
	}
	return (0);
}

int	delimiter_detected(char *usr_input, t_mshell *mshell)
{
	if (!ft_strcmp(usr_input, mshell->tkn->tkn))
	{
		close(mshell->heredoc->pipe_heredoc[1]);
		return (1);
	}
	return (0);
}
