/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_exprt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 20:51:12 by oboutarf          #+#    #+#             */
/*   Updated: 2023/02/10 13:37:18 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_arg_tab(t_mshell *mshell)
{
	int	i;

	i = 0;
	mshell->exec->start_exec = mshell->exec->start_exec->next;
	while (mshell->exec->start_exec)
	{
		mshell->exec->start_exec = mshell->exec->start_exec->next;
		i++;
	}
	mshell->built->export_arg = malloc(sizeof(char *) * (i + 1));
	if (!mshell->built->export_arg)
		return (0);
	mshell->built->export_args_len = i;
	mshell->exec->start_exec = mshell->exec->start_exec_head;
	return (1);
}

int	cut_args_in_tab(t_mshell *mshell)
{
	int	i;

	i = 0;
	mshell->exec->start_exec = mshell->exec->start_exec->next;
	while (mshell->exec->start_exec)
	{
		mshell->built->export_arg[i] = new_str(mshell->exec->start_exec->tkn);
		mshell->exec->start_exec = mshell->exec->start_exec->next;
		i++;
	}
	mshell->built->export_arg[i] = NULL;
	mshell->exec->start_exec = mshell->exec->start_exec_head;
	return (1);
}

int	cut_expt_var(t_mshell *mshell, char *to_expt, int i)
{
	mshell->built->export_var = malloc(sizeof(char) * (i + 1));
	if (!mshell->built->export_var)
		return (0);
	i = 0;
	while (to_expt[i] && to_expt[i] != '=')
	{
		mshell->built->export_var[i] = to_expt[i];
		i++;
	}
	mshell->built->export_var[i] = '\0';
	return (1);
}

int	cut_expt_value(t_mshell *mshell, char *to_expt, int i)
{
	int	i1;

	i1 = i;
	while (to_expt[i])
		i++;
	mshell->built->export_value = malloc(sizeof(char) * (i - i1 + 1));
	if (!mshell->built->export_value)
		return (0);
	i = 0;
	while (to_expt[i1])
	{
		mshell->built->export_value[i] = to_expt[i1];
		i1++;
		i++;
	}
	mshell->built->export_value[i] = '\0';
	return (1);
}

int	do_exprt(t_mshell *mshell)
{
	if (!mshell->exec->start_exec->next)
		declare_export(mshell);
	set_arg_tab(mshell);
	cut_args_in_tab(mshell);
	fill_environement(mshell);
	return (1);
}
