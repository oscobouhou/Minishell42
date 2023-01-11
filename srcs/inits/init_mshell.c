/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mshell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 19:52:04 by oboutarf          #+#    #+#             */
/*   Updated: 2023/01/11 19:32:58 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_mshell	*init_mshell(char **env)
{
	t_mshell	*mshell;

	mshell = malloc(sizeof(t_mshell));
	if (!mshell)
		return (NULL);
	mshell->exprt = NULL;
	mshell->env = NULL;
	mshell->tkn = NULL;
	init_t_token(mshell);
	if (!dup_env(&mshell->env, env, &mshell->envc))
		return (NULL);												// Don't forget free if function 'malloc' crashes
	if (!dup_env(&mshell->exprt, env, &mshell->exprtc))
		return (NULL);												// Don't forget free if function 'malloc' crashes
	return (mshell);
}
