/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connect_redirs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 14:26:03 by oboutarf          #+#    #+#             */
/*   Updated: 2023/01/29 15:39:26 by oboutarf         ###   ########.fr       */
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

int hrdoc_rdir(t_mshell *mshell)
{
    dup2(mshell->pipe_fd_hrdoc[0], STDIN_FILENO);
    close(mshell->pipe_fd_hrdoc[1]);
    return (1);
}

int append(t_mshell *mshell, int *fd)
{
    mshell->exec->fd[*fd] = open(mshell->exec->start_exec->next->tkn, O_CREAT | O_RDWR | O_APPEND, 0644);
    if (!mshell->exec->fd[*fd])
        return (dprintf(2, "Couldn't open fd %s\n", mshell->exec->start_exec->tkn));
    dup2(mshell->exec->fd[*fd], STDOUT_FILENO);
    mshell->exec->fd_out = mshell->exec->fd[*fd];
    (*fd)++;
    return (1);
}

int rdir_l(t_mshell *mshell, int *fd)
{
    if (access(mshell->exec->start_exec->next->tkn, F_OK) < 0)
    {
        dprintf(2, "minishell: %s: %s\n", mshell->exec->start_exec->next->tkn, strerror(errno));
        exit(1);
    }
    mshell->exec->fd[*fd] = open(mshell->exec->start_exec->next->tkn, O_RDONLY);
    if (!mshell->exec->fd[*fd])
        return (dprintf(2, "Couldn't open fd %s\n", mshell->exec->start_exec->tkn));
    dup2(mshell->exec->fd[*fd], STDIN_FILENO);
    mshell->exec->fd_in = mshell->exec->fd[*fd];
    (*fd)++;
    return (1);
}

int rdir_r(t_mshell *mshell, int *fd)
{
    mshell->exec->fd[*fd] = open(mshell->exec->start_exec->next->tkn, O_CREAT | O_RDWR | O_TRUNC, 0644);
    if (mshell->exec->fd[*fd] == -1)
        return (dprintf(2, "Couldn't open fd %s\n", mshell->exec->start_exec->tkn));
    dup2(mshell->exec->fd[*fd], STDOUT_FILENO);
    mshell->exec->fd_out = mshell->exec->fd[*fd];
    (*fd)++;
    return (1);
}

int no_redirs_case(t_mshell *mshell, int *fd)
{
    if (*fd == 0)
    {
        free(mshell->exec->fd);
        mshell->exec->fd = NULL;
    }
    return (1);
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
		if (mshell->exec->start_exec->type == RDIR_R)
			rdir_r(mshell, &fd);
        else if (mshell->exec->start_exec->type == RDIR_L)
            rdir_l(mshell, &fd);
		else if (mshell->exec->start_exec->type == APPEND)
            append(mshell, &fd);
		else if (mshell->exec->start_exec->type == HRDOC_RDIR)
            hrdoc_rdir(mshell);
        if (!mshell->exec->start_exec->next)
			break ;
        mshell->exec->start_exec = mshell->exec->start_exec->next;
	}
    no_redirs_case(mshell, &fd);
	return (1);
}
