/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 19:52:23 by oboutarf          #+#    #+#             */
/*   Updated: 2023/01/14 19:04:38 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tokens(t_mshell *mshell)
{
	t_tkn	*tmp;

	mshell->tkn = mshell->head_tkn;
	while (mshell->tkn)
	{
		free(mshell->tkn->tkn);
		tmp = mshell->tkn;
		mshell->tkn = mshell->tkn->next;
		free(tmp);
	}
}

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

void	free_exprt(t_mshell *mshell)
{
	t_expt	*tmp;

	while (mshell->expt)
	{
		free(mshell->expt->exptvar);
		free(mshell->expt->value);
		tmp = mshell->expt;
		mshell->expt = mshell->expt->next;
		free(tmp);
	}
}

void	terminate(t_mshell *mshell)
{
	free_t_env(mshell);
	free_exprt(mshell);
	free_tokens(mshell);
	free(mshell);
}
