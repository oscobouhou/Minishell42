/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 13:34:34 by oboutarf          #+#    #+#             */
/*   Updated: 2023/01/22 13:41:38 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	make_new_exec(t_mshell *mshell)
{
	mshell->exec->next = malloc(sizeof(t_exec));
	if (!mshell->exec->next)
		return (0);
	mshell->exec = mshell->exec->next;
	mshell->exec->start_exec = NULL;
	mshell->exec->next = NULL;
	return (1);
}

int	search_next_pipe(t_mshell *mshell)
{
	t_tkn 	*head;

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

int build_commands_chains(t_mshell *mshell)
{
	t_tkn	*skip;

    mshell->exec->start_exec = mshell->tkn;
	mshell->exec->start_exec_head = mshell->exec->start_exec;
	while (mshell->tkn->next)
	{
		if (mshell->tkn->next->type == PIPE)
		{
			skip = mshell->tkn->next->next;
			free(mshell->tkn->next);
			mshell->tkn->next = NULL;
			mshell->tkn = skip;
			if (!make_new_exec(mshell))
				return (0);
			mshell->exec->start_exec = mshell->tkn;
			mshell->exec->start_exec_head = mshell->exec->start_exec;
			if (!search_next_pipe(mshell))
			{
				set_end_of_command_chain(mshell);
				break ;
			}
		}
		else
			mshell->tkn = mshell->tkn->next;
	}
	mshell->exec = mshell->head_exec;
	return (1);
}
