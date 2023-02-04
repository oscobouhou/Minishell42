/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkermia <dkermia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 11:09:33 by dkermia           #+#    #+#             */
/*   Updated: 2023/02/03 11:14:50 by dkermia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

int	set_pos_to_cmd(t_mshell *mshell)
{
	if (mshell->exec->start_exec->type != -1)
	{
		while (mshell->exec->start_exec && \
		mshell->exec->start_exec->type != _CMD)
		{
			if (!mshell->exec->start_exec->next)
				return (mshell->exec->no_cmd = 42, \
				mshell->exec->start_exec = mshell->exec->start_exec_head, 0);
			mshell->exec->start_exec = mshell->exec->start_exec->next;
		}
	}
	return (1);
}

void	ft_putstr(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		ft_putchar(str[i]);
}


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
		env_tab[i] = ft_charcat(env->envar, '=');
		if (!env_tab[i])
			return (NULL);                                          //free previous in new function that takes i so it can free the already malloc lines
		env_tab[i] = ft_strjoin(env_tab[i], env->value, 1);
		if (!env_tab[i])
			return (NULL);                                          //free
		i++;
		env = env->next;
	}
	env = mshell->env;
	return (env_tab);
}
