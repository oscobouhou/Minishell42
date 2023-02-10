/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 13:35:38 by oboutarf          #+#    #+#             */
/*   Updated: 2023/02/10 16:33:05 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_existing(t_mshell *mshell)
{
	t_expt	*head;

	head = mshell->expt;
	while (mshell->expt->next)
	{
		if (!ft_strcmp(mshell->expt->exptvar, mshell->built->export_var))
		{
			mshell->expt = head;
			return (1);
		}
		mshell->expt = mshell->expt->next;
	}
	mshell->expt = head;
	return (0);
}

int	check_export_assignement(t_mshell *mshell, char *to_expt)
{
	int	i;

	i = 0;
	while (to_expt[i])
	{
		if (to_expt[i] == '=')
		{
			if (to_expt[i + 1])
				cut_expt_value(mshell, to_expt, i + 1);
			return (cut_expt_var(mshell, to_expt, i), 1);
		}
		i++;
	}
	return (cut_expt_var(mshell, to_expt, i), 0);
}

int	non_alpha(char *export)
{
	int	i;

	i = 0;
	while (export[i])
	{
		if (export[i] >= '0' && export[i] <= '9')
			return (0);
		i++;
	}
	return (1);
}

int	treat_export_arg(t_mshell *mshell, int i)
{
	if (check_export_assignement(mshell, mshell->built->export_arg[i]))
	{
		if (!non_alpha(mshell->built->export_var))
			if (export_numeric_error(mshell))
				return (1);
		if (check_existing(mshell))
		{
			replace_export_value(mshell);
			replace_env_value(mshell);
			return (1);
		}
		else
		{
			export_new_var_value_export(mshell);
			export_new_var_value_env(mshell);
			return (1);
		}
	}
	if (!non_alpha(mshell->built->export_var))
		if (export_numeric_error(mshell))
			return (1);
	if (!check_existing(mshell))
		create_new_var_export(mshell);
	return (1);
}

int	fill_environement(t_mshell *mshell)
{
	int	i;

	i = 0;
	while (mshell->built->export_arg[i])
	{
		if (!treat_export_arg(mshell, i))
			export_numeric_error(mshell);
		if (mshell->built->export_var)
			free(mshell->built->export_var);
		mshell->built->export_var = NULL;
		if (mshell->built->export_value)
			free(mshell->built->export_value);
		mshell->built->export_value = NULL;
		i++;
	}
	return (1);
}
