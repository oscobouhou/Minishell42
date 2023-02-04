/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connect_redirs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 14:26:03 by oboutarf          #+#    #+#             */
/*   Updated: 2023/02/04 12:57:11 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	number_redirs_in_start_exec(t_mshell *mshell)
{
	int	fd;

	fd = 0;
	mshell->exec->start_exec = mshell->exec->start_exec_head;
	while (mshell->exec->start_exec)
	{
		if (mshell->exec->start_exec->type == RDIR_L
			|| mshell->exec->start_exec->type == RDIR_R
			|| mshell->exec->start_exec->type == APPEND)
			fd++;
		mshell->exec->start_exec = mshell->exec->start_exec->next;
	}
	return (fd);
}

int	hrdoc_rdir(t_mshell *mshell)
{
	if (mshell->exec->no_cmd != 42)
	{
		close(mshell->exec->start_exec->pipe_fd_hrdoc[1]);
		dup2(mshell->exec->start_exec->pipe_fd_hrdoc[0], STDIN_FILENO);
		close(mshell->exec->start_exec->pipe_fd_hrdoc[0]);
	}
	else
	{
		close(mshell->exec->start_exec->pipe_fd_hrdoc[0]);
		close(mshell->exec->start_exec->pipe_fd_hrdoc[1]);
	}
	return (1);
}

int	append(t_mshell *mshell, int *fd)
{
	mshell->exec->fd[*fd] = open(mshell->exec->start_exec->next->tkn,
			O_CREAT | O_RDWR | O_APPEND, 0644);
	if (mshell->exec->fd[*fd] == -1)
		return (dprintf(2, "Couldn't open fd %s\n",
				mshell->exec->start_exec->tkn));
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
		return (dprintf(2, "minishell: %s: %s\n",
				mshell->exec->start_exec->next->tkn, strerror(errno)), 0);
	dup2(mshell->exec->fd[*fd], STDIN_FILENO);
	mshell->exec->fd_in = mshell->exec->fd[*fd];
	mshell->exec->no_redirs = 42;
	(*fd)++;
	return (1);
}

int	rdir_r(t_mshell *mshell, int *fd)
{
	mshell->exec->fd[*fd] = open(mshell->exec->start_exec->next->tkn,
			O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (mshell->exec->fd[*fd] == -1)
		return (dprintf(2, "minishell: %s: %s\n",
				mshell->exec->start_exec->next->tkn, strerror(errno)), 0);
	dup2(mshell->exec->fd[*fd], STDOUT_FILENO);
	mshell->exec->fd_out = mshell->exec->fd[*fd];
	mshell->exec->no_redirs = 42;
	(*fd)++;
	return (1);
}

int	fds_redirections_center__exec(t_mshell *mshell, int *fd)
{
	if (mshell->exec->start_exec->type == RDIR_R)
	{
		if (!rdir_r(mshell, fd))
			return (0);
	}
	else if (mshell->exec->start_exec->type == RDIR_L)
	{
		if (!rdir_l(mshell, fd))
			return (0);
	}
	else if (mshell->exec->start_exec->type == APPEND)
	{
		if (!append(mshell, fd))
			return (0);
	}
	else if (mshell->exec->start_exec->type == HRDOC_RDIR)
	{
		if (!hrdoc_rdir(mshell))
			return (0);
	}
	return (1);
}

int	enable_redirections(t_mshell *mshell)
{
	int	fd;

	mshell->exec->start_exec = mshell->exec->start_exec_head;
	fd = number_redirs_in_start_exec(mshell);
	mshell->exec->fd = malloc(sizeof(int) * (fd + 1));
	if (!mshell->exec->fd)
		return (0);
	mshell->exec->n_fd = fd;
	fd = 0;
	mshell->exec->start_exec = mshell->exec->start_exec_head;
	while (mshell->exec->start_exec)
	{
		if (!fds_redirections_center__exec(mshell, &fd))
			return (0);
		if (!mshell->exec->start_exec->next)
			break ;
		mshell->exec->start_exec = mshell->exec->start_exec->next;
	}
	return (1);
}
