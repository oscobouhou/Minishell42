/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connect_redirs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 14:26:03 by oboutarf          #+#    #+#             */
/*   Updated: 2023/02/08 13:08:45 by oboutarf         ###   ########.fr       */
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
