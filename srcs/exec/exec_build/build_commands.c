/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 13:34:34 by oboutarf          #+#    #+#             */
/*   Updated: 2023/02/08 19:10:19 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
