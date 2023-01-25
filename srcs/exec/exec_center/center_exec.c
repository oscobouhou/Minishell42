/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   center_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 11:53:47 by oboutarf          #+#    #+#             */
/*   Updated: 2023/01/25 16:48:36 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_pipes(t_mshell *mshell)
{
	while (mshell->exec)
	{
		if (pipe(mshell->exec->pipe_fd) == -1)
			return (0);
		if (!mshell->exec->next)
			break ;
		mshell->exec = mshell->exec->next;
	}
	mshell->exec = mshell->head_exec;
	return (1);
}

int center_exec(t_mshell *mshell)
{
    if (!init_exec(mshell))
		return (0);
	if (!build_commands_chains(mshell))
		return (0);
	print_exec_chains(mshell);
	if (mshell->exec->next)
		open_pipes(mshell);
	mshell->exec = mshell->head_exec;
	while (mshell->exec)
	{
		enable_redirections(mshell);
		// execute_command(mshell);
		mshell->exec = mshell->exec->next;
	}
    return (1);
}
