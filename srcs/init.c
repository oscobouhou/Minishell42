/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 19:52:04 by oboutarf          #+#    #+#             */
/*   Updated: 2023/01/09 22:53:44 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	obtain_envar_content(t_mshell *mshell, char **env, int i)
{
	int	envar_len;
	int	j;

	j = -1;
	envar_len = ft_strlen(env[i]);
	mshell->env->envar = malloc(sizeof(char) * (envar_len + 1));
	if (!mshell->env->envar)
		return (0);
	while (env[i][++j])
		mshell->env->envar[j] = env[i][j];
	return (1);
}

int	dup_env(t_mshell *mshell, char **env)
{
	t_env	*start;
	int		i;

	i = 0;
	mshell->env = malloc(sizeof(t_env));
	start = mshell->env;
	if (!mshell->env)
		return (0);
	while (env[i])
	{
		if (!obtain_envar_content(mshell, env, i))
			return (0);
		if (!env[i + 1])
			break ;
		mshell->env->next = malloc(sizeof(t_env));
		if (!mshell->env->next)
			return (0);
		mshell->env = mshell->env->next;
		i++;
	}
	mshell->env->next = NULL;
	mshell->env = start;
	return (1);
}

t_mshell	*init_struct(char **env)
{
	t_mshell	*mshell;

	mshell = malloc(sizeof(t_mshell));
	if (!mshell)
		return (NULL);
	if (!dup_env(mshell, env))
		return (NULL);
	return (mshell);
}