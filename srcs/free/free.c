/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 19:52:23 by oboutarf          #+#    #+#             */
/*   Updated: 2023/01/12 13:44:56 by oboutarf         ###   ########.fr       */
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

void	free_exprt(t_mshell *mshell)
{
	t_env	*tmp;

	while (mshell->exprt)
	{
		free(mshell->exprt->envar);
		free(mshell->exprt->value);
		tmp = mshell->exprt;
		mshell->exprt = mshell->exprt->next;
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
