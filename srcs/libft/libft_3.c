/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 11:09:33 by dkermia           #+#    #+#             */
/*   Updated: 2023/02/08 11:21:10 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] && s2[i])
		i++;
	return (s1[i] - s2[i]);
}

int	env_len(t_mshell *mshell)
{
	t_env	*env;
	int		i;

	if (!mshell->env)
		return (0);
	i = 0;
	env = mshell->env;
	while (env->next)
	{
		env = env->next;
		i++;
	}
	return (i + 1);
}

void	free_tab(char **tab, int i)
{
	while (i >= 0)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

char	*create_envar_with_value(t_env *env)
{
	char	*env_tab;

	env_tab = ft_charcat(env->envar, '=');
	if (!env_tab)
		return (NULL);
	env_tab = ft_strjoin(env_tab, env->value, 1);
	if (!env_tab)
		return (NULL);
	return (env_tab);
}

char	**copy_env_in_tab(t_mshell *mshell)
{
	t_env	*env;
	char	**env_tab;
	int		i;

	i = env_len(mshell);
	if (!i)
		return (0);
	env_tab = malloc(sizeof(char *) * (i + 1));
	env_tab[i] = NULL;
	if (!env_tab)
		return (NULL);
	env = mshell->env;
	i = 0;
	while (env)
	{
		env_tab[i] = create_envar_with_value(env);
		if (!env_tab[i])
			return (free_tab(env_tab, i), NULL);
		i++;
		env = env->next;
	}
	env = mshell->env;
	return (env_tab);
}
