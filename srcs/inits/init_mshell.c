/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mshell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 19:52:04 by oboutarf          #+#    #+#             */
/*   Updated: 2023/01/22 14:47:36 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_dependencies(t_mshell *mshell, char **env)
{
	if (!init_builtins(mshell))
		return (0);
	if (!dup_env(&mshell->env, env, &mshell->envc))
		return (0);
	if (!sort_export(mshell))
		return (0);
	if (!init_expansion(mshell))
		return (0);
	if (!init_execve(mshell))
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
	if (!init_dependencies(mshell, env))
		return (NULL);
	return (mshell);
}
