/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connect_redirs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 14:26:03 by oboutarf          #+#    #+#             */
/*   Updated: 2023/01/25 16:39:12 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int number_redirs_in_start_exec(t_mshell *mshell)
{
    int fd;

    fd = 0;
	mshell->exec->start_exec = mshell->exec->start_exec_head;
    while (mshell->exec->start_exec)
    {
        if (mshell->exec->start_exec->type == RDIR_L || mshell->exec->start_exec->type == RDIR_R
            || mshell->exec->start_exec->type == APPEND)
            fd++;
        mshell->exec->start_exec = mshell->exec->start_exec->next;
    }
    return (fd);
}

int	enable_redirections(t_mshell *mshell)
{
    int fd;

	fd = number_redirs_in_start_exec(mshell);
    mshell->exec->fd = malloc(sizeof(int) * fd);
    if (!mshell->exec->fd)
        return (0);
    fd = 0;
	mshell->exec->start_exec = mshell->exec->start_exec_head;
    while (mshell->exec->start_exec)
	{
        dprintf(2, "%s\n", mshell->exec->start_exec->tkn);
		if (mshell->exec->start_exec->type == RDIR_R)
		{
			mshell->exec->fd[fd] = open(mshell->exec->start_exec->next->tkn, O_CREAT | O_WRONLY | O_TRUNC, 0644);
			if (mshell->exec->fd[fd] == -1)
				return (dprintf(2, "Couldn't open fd %s\n", mshell->exec->start_exec->tkn));
            fd++;
		}
        else if (mshell->exec->start_exec->type == RDIR_L)
        {
            mshell->exec->fd[fd] = open(mshell->exec->start_exec->next->tkn, O_RDONLY);
            if (!mshell->exec->fd[fd])
                return (dprintf(2, "Couldn't open fd %s\n", mshell->exec->start_exec->tkn));
            fd++;
        }
		else if (mshell->exec->start_exec->type == APPEND)
		{
			mshell->exec->fd[fd] = open(mshell->exec->start_exec->next->tkn, O_APPEND);
            if (!mshell->exec->fd[fd])
                return (dprintf(2, "Couldn't open fd %s\n", mshell->exec->start_exec->tkn));
			fd++;
		}
        if (!mshell->exec->start_exec->next)
			break ;
        mshell->exec->start_exec = mshell->exec->start_exec->next;
	}
	return (1);
}
