/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 19:32:31 by oboutarf          #+#    #+#             */
/*   Updated: 2023/01/21 13:40:11 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_env_sorter(t_mshell *mshell, t_env **env_sorter)
{
	t_env	*head;

	(*env_sorter) = malloc(sizeof(t_env));
	if (!(*env_sorter))
		return (0);
	head = (*env_sorter);
	(*env_sorter)->next = NULL;
	(*env_sorter)->value = NULL;
	(*env_sorter)->envar = NULL;
	while (mshell->env->next)
	{
		if (!copy_env_content((*env_sorter), mshell->env))
			return (0);						
		(*env_sorter)->next = malloc(sizeof(t_env));
		if (!(*env_sorter)->next)
			return (0);										// lst_clear{head}
		mshell->env = mshell->env->next;
		(*env_sorter) = (*env_sorter)->next;
	}
	(*env_sorter)->next = NULL;
	(*env_sorter) = head;
	return (1);
}

int	obtain_env_content(t_env **lst, char *env)
{
	int	envar_len;
	int	value_len;
	int	j;
	int	i;

	j = -1;
	value_len = ft_strlen(env);
	envar_len = ft_strequal_sign(env);
	value_len -= envar_len;
	(*lst)->envar = malloc(sizeof(char) * (envar_len + 1));
	if (!(*lst)->envar)
		return (0);
	(*lst)->value = malloc(sizeof(char) * (value_len) + 1);
	if (!(*lst)->value)
		return (0);									// free envar
	while (env[++j] != '=')
		(*lst)->envar[j] = env[j];
	(*lst)->envar[j] = '\0';
	i = -1;
	while (env[++j])
		(*lst)->value[++i] = env[j];
	(*lst)->value[++i] = '\0';
	return (1);
}

int	dup_env(t_env **lst, char **env, uint64_t *count)
{
	t_env	*start;
	int		i;

	i = 0;
	(*lst) = malloc(sizeof(t_env));
	if (!(*lst))
		return (0);
	start = (*lst);
	while (env[i])
	{
		if (!obtain_env_content(lst, env[i]))
			return (0);                				// lst_clear
		if (!env[i + 1])
			break ;
		(*lst)->next = malloc(sizeof(t_env));
		if (!(*lst)->next)
			return (0);								// lst_clear{start}
		(*lst) = (*lst)->next;
		i++;
	}
	(*lst)->next = NULL;
	(*lst) = start;
	*count = i;
	return (1);
}
