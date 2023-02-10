/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 03:37:03 by oboutarf          #+#    #+#             */
/*   Updated: 2023/02/10 14:26:19 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	absolute_cmd_exec(char *tkn)
{
	int	i;

	i = 0;
	while (tkn[i])
	{
		if (tkn[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

int	close_pipe_fds(t_mshell *mshell)
{
	while (mshell->exec->next)
	{
		if (mshell->exec->fd_out != 1)
			close(mshell->exec->fd_out);
		if (mshell->exec->fd_in != 0)
			close(mshell->exec->next->fd_in);
		mshell->exec = mshell->exec->next;
	}
	mshell->exec = mshell->head_exec;
	return (1);
}

int	handle_tube(t_mshell *mshell)
{
	if (mshell->exec->fd_in != 0)
	{
		dup2(mshell->exec->fd_in, STDIN_FILENO);
		close(mshell->exec->fd_in);
	}
	if (mshell->exec->fd_out != 1)
	{
		dup2(mshell->exec->fd_out, STDOUT_FILENO);
		close(mshell->exec->fd_out);
	}
	if (mshell->exec->next)
		close(mshell->exec->next->fd_in);
	return (1);
}

int	pclose_tube(t_mshell *mshell)
{
	if (mshell->exec->fd_in != 0)
		close(mshell->exec->fd_in);
	if (mshell->exec->fd_out != 1)
		close(mshell->exec->fd_out);
	return (1);
}

int	popen_tube(t_mshell *mshell)
{
	if (mshell->exec->next)
	{
		if (pipe(mshell->pipe_fd) == -1)
			return (ft_putstr_fd(2, "\tpipe: open failure\n"), 0);
		mshell->exec->next->fd_in = mshell->pipe_fd[0];
		mshell->exec->fd_out = mshell->pipe_fd[1];
	}
	return (1);
}
