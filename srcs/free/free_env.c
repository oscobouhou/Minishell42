/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 23:43:16 by oboutarf          #+#    #+#             */
/*   Updated: 2023/01/14 23:43:58 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_t_env(t_mshell *mshell)
{
	t_env	*tmp;

	while (mshell->env)
	{
		free(mshell->env->envar);
		free(mshell->env->value);
		tmp = mshell->env;
		mshell->env = mshell->env->next;
		free(tmp);
	}
}

void	free_env_sorter(t_env *env_sorter)
{
	t_env	*tmp;

	while (env_sorter->next)
	{
		free(env_sorter->envar);
		free(env_sorter->value);
		tmp = env_sorter;
		env_sorter = env_sorter->next;
		free(tmp);
	}
	free(env_sorter);
}
