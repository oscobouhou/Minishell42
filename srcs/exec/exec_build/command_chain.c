/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_chain.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 19:08:42 by oboutarf          #+#    #+#             */
/*   Updated: 2023/02/08 19:14:12 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	make_new_exec(t_mshell *mshell)
{
	mshell->exec->next = malloc(sizeof(t_exec));
	if (!mshell->exec->next)
		return (0);
	mshell->exec = mshell->exec->next;
	mshell->exec->fd = NULL;
	mshell->exec->pid = -42;
	mshell->exec->n_fd = -42;
	mshell->exec->fd_in = 0;
	mshell->exec->fd_out = 1;
	mshell->exec->no_cmd = -42;
	mshell->exec->no_redirs = -42;
	mshell->exec->p_listener = -42;
	mshell->exec->next = NULL;
	mshell->exec->start_exec = NULL;
	return (1);
}

int	set_end_of_command_chain(t_mshell *mshell)
{
	t_tkn	*head;

	head = mshell->exec->start_exec;
	mshell->exec->start_exec_head = head;
	while (mshell->exec->start_exec->next)
		mshell->exec->start_exec = mshell->exec->start_exec->next;
	free(mshell->exec->start_exec->next);
	mshell->exec->start_exec->next = NULL;
	mshell->exec->start_exec = head;
	return (1);
}

int	skip_pipe_token(t_mshell *mshell, t_tkn *skip)
{
	skip = mshell->tkn->next->next;
	free(mshell->tkn->next->tkn);
	free(mshell->tkn->next);
	mshell->tkn->next = NULL;
	mshell->tkn = skip;
	return (1);
}		

int	new_exec_line(t_mshell *mshell)
{
	if (!search_next_pipe(mshell))
	{
		set_end_of_command_chain(mshell);
		return (0);
	}
	return (1);
}
