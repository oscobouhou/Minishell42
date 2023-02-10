/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 10:41:03 by oboutarf          #+#    #+#             */
/*   Updated: 2023/02/10 11:04:25 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int replace_export_value(t_mshell *mshell)
{
	(void)mshell;
	return (1);
}

int replace_env_value(t_mshell *mshell)
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
int export_new_var_value_export(t_mshell *mshell)
{
	(void)mshell;
	return (1);
}

int export_new_var_value_env(t_mshell *mshell)
{
	(void)mshell;
	return (1);
}

int create_new_var_export(t_mshell *mshell)
{
	(void)mshell;
	return (1);
}
