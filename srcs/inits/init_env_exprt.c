/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env_exprt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 19:32:31 by oboutarf          #+#    #+#             */
/*   Updated: 2023/01/11 19:34:23 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		return (/* ft_(*lst)clear(start), */0);						// Don't forget free if function 'malloc' crashes
	(*lst)->value = malloc(sizeof(char) * (value_len));
	if (!(*lst)->value)
		return (/* ft_(*lst)clear(start), */0);						// Don't forget free if function 'malloc' crashes
	while (env[++j] != '=')
		(*lst)->envar[j] = env[j];
	i = -1;
	while (env[++j])
		(*lst)->value[++i] = env[j];
	return (1);
}

int	dup_env(t_env **lst, char **env, uint64_t *count)
{
	t_env	*start;
	int		i;

	i = 0;
	(*lst) = malloc(sizeof(t_env));
	if (!(*lst))
		return (0);													// Don't forget free if function 'malloc' crashes
	start = (*lst);
	while (env[i])
	{
		if (!obtain_env_content(lst, env[i]))
			return (0);												// Don't forget free if function 'malloc' crashes
		if (!env[i + 1])
			break ;
		(*lst)->next = malloc(sizeof(t_env));
		if (!(*lst)->next)
			return (/* ft_lstclear(start), */0);					// Don't forget free  if function 'malloc' crashes
		(*lst) = (*lst)->next;
		i++;
	}
	(*lst)->next = NULL;
	(*lst) = start;
	*count = i;
	return (1);
}
