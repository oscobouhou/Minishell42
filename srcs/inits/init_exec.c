/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 18:51:32 by oboutarf          #+#    #+#             */
/*   Updated: 2023/02/04 15:09:02 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_exec(t_mshell *mshell)
{
	mshell->exec = malloc(sizeof(t_exec));
	if (!mshell->exec)
		return (0);
	mshell->exec->fd = NULL;
	mshell->exec->fd_in = 0;
	mshell->exec->n_fd = -42;
	mshell->exec->fd_out = 1;
	mshell->exec->no_cmd = -42;
	mshell->exec->no_redirs = -42;
	mshell->exec->p_listener = -42;
	mshell->exec->start_exec = NULL;
	mshell->exec->start_exec_head = NULL;
	mshell->head_exec = mshell->exec;
	mshell->exec->next = NULL;
	return (1);
}
