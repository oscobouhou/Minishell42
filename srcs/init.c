/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 19:52:04 by oboutarf          #+#    #+#             */
/*   Updated: 2023/01/09 22:29:54 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	obtain_envar_content(t_mshell *mshell, char **env, int i)
{
	int	envar_len;
	int	j;

	j = -1;
	envar_len = ft_strlen(env[i]);
	mshell->env->envar = malloc(sizeof(char) * (envar_len + 1));
	if (!mshell->env->envar)
		return ;
	while (env[i][++j])
		mshell->env->envar[j] = env[i][j];
}

void	dup_env(t_mshell *mshell, char **env)
{
	t_env	*start;
	int		i;

	i = 0;
	mshell->env = malloc(sizeof(t_env));
	start = mshell->env;
	if (!mshell->env)
		return ;
	while (env[i])
	{
		obtain_envar_content(mshell, env, i);
		if (!env[i + 1])
			break ;
		mshell->env->next = malloc(sizeof(t_env));
		mshell->env = mshell->env->next;
		i++;
	}
	mshell->env->next = NULL;
	mshell->env = start;
}

t_mshell	*init_struct(char **env)
{
	t_mshell	*mshell;

	mshell = malloc(sizeof(t_mshell));
	if (!mshell)
		return (NULL);
	dup_env(mshell, env);
	return (mshell);
}