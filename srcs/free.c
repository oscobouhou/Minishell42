/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 19:52:23 by oboutarf          #+#    #+#             */
/*   Updated: 2023/01/09 22:30:55 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_mshell_env(t_mshell *mshell)
{
	t_env	*tmp;

	while (mshell->env->next)
	{
		free(mshell->env->envar);
		tmp = mshell->env;
		mshell->env = mshell->env->next;
		free(tmp);
	}
	free(mshell->env->envar);
	free(mshell->env);
}

void    terminate(t_mshell *mshell)
{
	free_mshell_env(mshell);
	free(mshell);
}

