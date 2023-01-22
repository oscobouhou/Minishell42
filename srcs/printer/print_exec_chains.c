/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_exec_chains.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 12:37:40 by oboutarf          #+#    #+#             */
/*   Updated: 2023/01/22 12:47:54 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int print_exec_chains(t_mshell *mshell)
{
    dprintf(2, "\n");
	while (mshell->exec)
	{
		while (mshell->exec->start_exec)
		{
			dprintf(2, " %s  ---  ", mshell->exec->start_exec->tkn);
			mshell->exec->start_exec = mshell->exec->start_exec->next;
		}
        mshell->exec->start_exec = mshell->exec->start_exec_head;
		mshell->exec = mshell->exec->next;
		dprintf(2, "\n\n%s\n\n", " --- ############## - ############ --- ");
	}
    mshell->exec = mshell->head_exec;
    return (1);
}
