/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkermia <dkermia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 11:20:55 by dkermia           #+#    #+#             */
/*   Updated: 2023/02/05 03:52:47 by dkermia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*create_env_node(char *var)
{
	t_env	*new_node;

	new_node = malloc(sizeof(*new_node));
	if (!new_node)
		return (NULL);
	new_node->envar = ft_strdup(var);
	new_node->value = NULL;
	new_node->next = NULL;
	return (new_node);
}

void	append_to_env(t_env **head, t_env *new_node)
{
	t_env	*last;

	if (!head)
		return ;
	if (*head)
	{
		last = *head;
		while (last->next)
			last = last->next;
		last->next = new_node;
	}
	else
		*head = new_node;
}

int	add_new_envar(char **to_add, t_mshell *mshell)
{
	t_env		*new_node;

	new_node = create_env_node(to_add[0]);
	new_node->value = ft_strdup(to_add[1]);
	if (!new_node->value)
		return (0);
	if (!new_node)
		return (0);
	append_to_env(&mshell->env, new_node);
	return (1);
}

int	manage_env(char **to_export, t_mshell *mshell)
{
	int		plus_index;
	t_env	*environment;

	environment = mshell->env;
	plus_index = 0;
	if (ft_strchr(to_export[0], '+') != NULL)
	{
		plus_index = ft_strlen(to_export[0]) - 1;
		to_export[0][plus_index] = '\0';
	}
	while (environment && ft_strcmp(environment->envar, to_export[0]) != 0)
		environment = environment->next;
	if (environment && plus_index == 0)
		return (environment->value = to_export[1], 1);
	if (environment && plus_index)
	{
		environment->value = ft_strjoin(environment->value, to_export[1], 1);
		if (!environment->value)
			return (0);
	}
	if (!environment)
		if (add_new_envar(to_export, mshell) == 0)
			return (0);
	return (1);
}
