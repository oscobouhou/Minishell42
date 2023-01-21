/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 18:51:32 by oboutarf          #+#    #+#             */
/*   Updated: 2023/01/21 22:51:34 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_execve(t_mshell *mshell)
{
	mshell->execve = malloc(sizeof(t_execve));
	if (!mshell->execve)
		return (0);
	mshell->execve->cmd = NULL;
	mshell->execve->cmd_args = NULL;
	mshell->execve->paths = NULL;
	mshell->execve->next = NULL;
	return (1);
}

int	init_exec(t_mshell *mshell)
{
	if (!init_execve(mshell))
		return (0);
	mshell->exec = malloc(sizeof(t_exec));
	if (!mshell->exec)
		return (0);
	mshell->exec->pipe_fd[0] = -42;
	mshell->exec->pipe_fd[1] = -42;
	mshell->exec->fd = NULL;
	mshell->exec->start_exec = mshell->head_tkn;
	mshell->head_exec = mshell->exec;
	mshell->exec->next = NULL;
	return (1);
}

// dprintf(2, "%d\n", (int)sizeof(i) / (int)sizeof(int));