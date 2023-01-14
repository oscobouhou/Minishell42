/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 11:30:23 by oboutarf          #+#    #+#             */
/*   Updated: 2023/01/14 20:15:53 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	copy_env_content(t_env *dest, t_env *src)
{
	int	i;

	dest->envar = malloc(sizeof(char) * (ft_strlen(src->envar) + 1));
	if (!dest->envar)
		return (0);
	dest->value = malloc(sizeof(char) * (ft_strlen(src->value) + 1));
	if (!dest->value)
		return (0);
	i = -1;
	while (src->envar[++i])
		dest->envar[i] = src->envar[i];
	dest->envar[i] = '\0';
	i = -1;
	while (src->value[++i])
		dest->value[i] = src->value[i];
	dest->value[i] = '\0';
	return (1);
}

int	copy_env_sorter_content(t_expt *dest, t_env *src)
{
	int	i;

	dest->exptvar = malloc(sizeof(char) * (ft_strlen(src->envar) + 1));
	if (!dest->exptvar)
		return (0);
	dest->value = malloc(sizeof(char) * (ft_strlen(src->value) + 3));
	if (!dest->value)
		return (0);
	i = -1;
	while (src->envar[++i])
		dest->exptvar[i] = src->envar[i];
	dest->exptvar[i] = '\0';
	i = -1;
	while (src->value[++i])
		dest->value[i] = src->value[i];
	dest->value[i] = '\0';
	return (1);
}

int	copy_and_suppress_env_node(t_mshell *mshell, t_env *env_sorter,
	t_env *actualise)
{
	if (!copy_env_sorter_content(mshell->expt, env_sorter))
		return (0);
	if (!new_node_export(mshell))
		return (0);
	actualise->next = env_sorter->next;
	free(env_sorter->envar);
	free(env_sorter->value);
	free(env_sorter);
	return (1);
}

int	start_sort_export_process(t_mshell *mshell, t_env **env_sorter,
	t_env **head)
{
	*head = mshell->env;
	if (!init_env_sorter(mshell, env_sorter))
		return (0);
	if (!init_sort_export(mshell))
		return (0);
	mshell->env = *head;
	*head = *env_sorter;
	return (1);
}

int	sort_export(t_mshell *mshell)
{
	t_env	*env_sorter;
	t_env	*actualise;
	t_expt	*head_expt;
	t_env	*head;
	int		count;

	count = (mshell->envc - 1);
	if (!start_sort_export_process(mshell, &env_sorter, &head))
		return (0);
	head_expt = mshell->expt;
	while (count > 0)
	{
		if (search_lowest(env_sorter->envar, env_sorter))
		{
			copy_and_suppress_env_node(mshell, env_sorter, actualise);
			env_sorter = head;
			--count;
		}
		actualise = env_sorter;
		env_sorter = env_sorter->next;
	}
	free_actualise(actualise);
	mshell->expt = head_expt;
	return (mshell->expt = head_expt, 1);
}
