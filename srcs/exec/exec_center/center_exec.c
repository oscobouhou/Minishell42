/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   center_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 11:53:47 by oboutarf          #+#    #+#             */
/*   Updated: 2023/01/21 23:34:49 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	make_new_exec(t_mshell *mshell)
{
	mshell->exec->next = malloc(sizeof(t_exec));
	if (!mshell->exec->next)
		return (0);
	mshell->exec = mshell->exec->next;
	mshell->exec->next = NULL;
	return (1);
}

// int	set_pipe_to_null(t_mshell *mshell)
// {
// 	return (1);
// }

int center_exec(t_mshell *mshell)
{
    if (!init_exec(mshell))
		return (0);
    while (mshell->tkn->next)
    {
		// if (mshell->tkn->next->type == PIPE && !search_next_pipe(mshell))
		// {
			
		// }
		if (mshell->tkn->next->type == PIPE)
		{
			make_new_exec(mshell);
			mshell->exec->start_exec = mshell->tkn->next->next;
			// set_pipe_to_null(mshell);
			free(mshell->tkn);
			mshell->tkn = NULL;
			mshell->tkn = mshell->exec->start_exec;
		}
		mshell->tkn = mshell->tkn->next;
    }
	mshell->exec = mshell->head_exec;

    while (mshell->exec)
	{
		while (mshell->exec->start_exec->next)
		{
			dprintf(2, "%s --> ", mshell->exec->start_exec->tkn);
			mshell->exec->start_exec = mshell->exec->start_exec->next;
		}
		dprintf(2, "\n");
		mshell->exec = mshell->exec->next;
    }
	mshell->exec = mshell->head_exec;
    return (1);
}
