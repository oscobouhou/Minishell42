/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 13:34:34 by oboutarf          #+#    #+#             */
/*   Updated: 2023/02/03 06:41:08 by oboutarf         ###   ########.fr       */
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

int	search_next_pipe(t_mshell *mshell)
{
	t_tkn	*head;

	head = mshell->tkn;
	while (mshell->tkn->next)
	{
		if (mshell->tkn->next->type == PIPE)
			return (mshell->tkn = head, 1);
		mshell->tkn = mshell->tkn->next;
	}
	return (mshell->tkn = head, 0);
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

int	build_commands_chains(t_mshell *mshell)
{
	t_tkn	*skip;

	skip = NULL;
	mshell->exec->start_exec = mshell->tkn;
	mshell->exec->start_exec_head = mshell->exec->start_exec;
	while (mshell->tkn->next)
	{
		if (mshell->tkn->next->type == PIPE)
		{
			skip_pipe_token(mshell, skip);
			if (!make_new_exec(mshell))
				return (0);
			mshell->exec->start_exec = mshell->tkn;
			mshell->exec->start_exec_head = mshell->exec->start_exec;
			if (!new_exec_line(mshell))
				break ;
		}
		else
			mshell->tkn = mshell->tkn->next;
	}
	mshell->exec->next = NULL;
	mshell->exec = mshell->head_exec;
	return (1);
}
