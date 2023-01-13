/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mshell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 19:52:04 by oboutarf          #+#    #+#             */
/*   Updated: 2023/01/13 20:37:18 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_dependencies(t_mshell *mshell, char **env)
{
	if (!init_t_token(mshell))
		return (0);
	if (!init_builtins(mshell))
		return (0);
	if (!dup_env(&mshell->env, env, &mshell->envc))
		return (0);
	if (!dup_env(&mshell->exprt, env, &mshell->exprtc))
		return (0);
	return (1);
}

t_mshell	*init_mshell(char **env)
{
	t_mshell	*mshell;

	mshell = malloc(sizeof(t_mshell));
	if (!mshell)
		return (NULL);
	mshell->exprt = NULL;
	mshell->env = NULL;
	mshell->tkn = NULL;
	if (!init_dependencies(mshell, env))
		return (NULL);
	return (mshell);
}
