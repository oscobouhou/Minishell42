/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 18:51:32 by oboutarf          #+#    #+#             */
/*   Updated: 2023/01/22 14:01:14 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_exec(t_mshell *mshell)
{
	mshell->exec = malloc(sizeof(t_exec));
	if (!mshell->exec)
		return (0);
	mshell->exec->pipe_fd[0] = -42;
	mshell->exec->pipe_fd[1] = -42;
	mshell->exec->fd = NULL;
	mshell->exec->start_exec = NULL;
	mshell->exec->start_exec_head = NULL;
	mshell->head_exec = mshell->exec;
	mshell->exec->next = NULL;
	return (1);
}
