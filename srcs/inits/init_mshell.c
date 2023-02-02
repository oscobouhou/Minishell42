/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mshell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 19:52:04 by oboutarf          #+#    #+#             */
/*   Updated: 2023/02/02 10:45:00 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	begin_command(t_mshell *mshell, char **env)
{
	if (!dup_env(&mshell->env, env, &mshell->envc))
		return (0);
	if (!sort_export(mshell))
		return (0);
	return (1);
}

t_mshell	*init_mshell(char **env)
{
	t_mshell	*mshell;

	mshell = malloc(sizeof(t_mshell));
	if (!mshell)
		return (NULL);
	mshell->env = NULL;
	mshell->tkn = NULL;
	mshell->expt = NULL;
	mshell->expd = NULL;
	mshell->exec = NULL;
	mshell->execve = NULL;
	mshell->pipe_fd[0] = -42;
	mshell->pipe_fd[1] = -42;
	mshell->exit_status = -42;
	mshell->old_expd__hrdoc = -42;
	if (!begin_command(mshell, env))
		return (NULL);
	return (mshell);
}
