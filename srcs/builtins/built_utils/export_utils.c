/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 10:41:03 by oboutarf          #+#    #+#             */
/*   Updated: 2023/02/10 16:34:21 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	replace_export_value(t_mshell *mshell)
{
	t_expt	*head;

	head = mshell->expt;
	while (mshell->expt->next)
	{
		if (!ft_strcmp(mshell->expt->exptvar, mshell->built->export_var))
		{
			free(mshell->expt->value);
			mshell->expt->value = NULL;
			mshell->expt->value = new_str(mshell->built->export_value);
			mshell->expt = head;
			return (1);
		}
		mshell->expt = mshell->expt->next;
	}
	mshell->expt = head;
	return (0);
}

int	replace_env_value(t_mshell *mshell)
{
	t_env	*head;

	head = mshell->env;
	while (mshell->env->next)
	{
		if (!ft_strcmp(mshell->env->envar, mshell->built->export_var))
		{
			free(mshell->env->value);
			mshell->env->value = NULL;
			mshell->env->value = new_str(mshell->built->export_value);
			mshell->env = head;
			return (1);
		}
		mshell->env = mshell->env->next;
	}
	mshell->env = head;
	return (0);
}

int	export_new_var_value_export(t_mshell *mshell)
{
	t_expt	*new_node;

	new_node = malloc(sizeof(t_expt));
	new_node->exptvar = new_str(mshell->built->export_var);
	new_node->value = new_str(mshell->built->export_value);
	new_node->next = mshell->expt;
	mshell->head_expt = new_node;
	mshell->expt = mshell->head_expt;
	return (1);
}

int	export_new_var_value_env(t_mshell *mshell)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	new_node->envar = new_str(mshell->built->export_var);
	new_node->value = new_str(mshell->built->export_value);
	new_node->next = mshell->env;
	mshell->head_env = new_node;
	mshell->env = mshell->head_env;
	return (1);
}

int	create_new_var_export(t_mshell *mshell)
{
	t_expt	*new_node;

	new_node = malloc(sizeof(t_expt));
	if (!new_node)
		return (0);
	new_node->exptvar = new_str(mshell->built->export_var);
	new_node->value = NULL;
	new_node->next = mshell->expt;
	mshell->head_expt = new_node;
	mshell->expt = mshell->head_expt;
	return (1);
}
