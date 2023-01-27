/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 18:51:32 by oboutarf          #+#    #+#             */
/*   Updated: 2023/01/27 20:51:37 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_exec(t_mshell *mshell)
{
	mshell->exec = malloc(sizeof(t_exec));
	if (!mshell->exec)
		return (0);
	mshell->exec->fd = NULL;
	mshell->exec->fd_in = -42;
	mshell->exec->fd_out = -42;
	mshell->exec->fd_p[0] = -42;
	mshell->exec->fd_p[1] = -42;
	mshell->exec->start_exec = NULL;
	mshell->exec->start_exec_head = NULL;
	mshell->head_exec = mshell->exec;
	mshell->exec->next = NULL;
	return (1);
}
