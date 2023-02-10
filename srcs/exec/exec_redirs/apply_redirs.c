/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_redirs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 13:01:13 by oboutarf          #+#    #+#             */
/*   Updated: 2023/02/10 14:25:35 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	hrdoc_rdir(t_mshell *mshell)
{
	if (mshell->exec->no_cmd != 42)
	{
		close(mshell->heredoc->pipe_heredoc[1]);
		dup2(mshell->heredoc->pipe_heredoc[0], STDIN_FILENO);
		close(mshell->heredoc->pipe_heredoc[0]);
	}
	else
	{
		close(mshell->heredoc->pipe_heredoc[0]);
		close(mshell->heredoc->pipe_heredoc[1]);
	}
	return (1);
}

int	append(t_mshell *mshell, int *fd)
{
	if (!ft_strcmp(mshell->exec->start_exec->next->tkn, "/dev/stdout"))
		return (1);
	mshell->exec->fd[*fd] = open(mshell->exec->start_exec->next->tkn,
			O_CREAT | O_RDWR | O_APPEND, 0644);
	if (mshell->exec->fd[*fd] == -1)
		return (open_error(mshell), 0);
	dup2(mshell->exec->fd[*fd], STDOUT_FILENO);
	mshell->exec->fd_out = mshell->exec->fd[*fd];
	mshell->exec->no_redirs = 42;
	(*fd)++;
	return (1);
}

int	rdir_l(t_mshell *mshell, int *fd)
{
	mshell->exec->fd[*fd] = open(mshell->exec->start_exec->next->tkn, O_RDONLY);
	if (mshell->exec->fd[*fd] == -1)
		return (open_error(mshell), 0);
	dup2(mshell->exec->fd[*fd], STDIN_FILENO);
	mshell->exec->fd_in = mshell->exec->fd[*fd];
	mshell->exec->no_redirs = 42;
	(*fd)++;
	return (1);
}

int	rdir_r(t_mshell *mshell, int *fd)
{
	if (!ft_strcmp(mshell->exec->start_exec->next->tkn, "/dev/stdout"))
		return (1);
	mshell->exec->fd[*fd] = open(mshell->exec->start_exec->next->tkn,
			O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (mshell->exec->fd[*fd] == -1)
		return (open_error(mshell), 0);
	dup2(mshell->exec->fd[*fd], STDOUT_FILENO);
	mshell->exec->fd_out = mshell->exec->fd[*fd];
	mshell->exec->no_redirs = 42;
	(*fd)++;
	return (1);
}
