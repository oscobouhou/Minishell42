/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 20:51:18 by oboutarf          #+#    #+#             */
/*   Updated: 2023/02/03 01:17:13 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_current_unset_arg(char *arg)
{
	int i;
	
	i = 0;
	if (!arg)
		return (0);
	if (!ft_isalpha(*arg) || *arg == '_')
		return (0);
	while (ft_isalnum(arg[i]) || arg[i] == '_')
		i++;
	if (arg[i] == '\0')
		return (2);
	if (arg[i] == '+' && arg[i + 1] == '=')
		return (1);
	if (arg[i] == '=')
		return (1);
	return (0);
}

void remove_env(char *to_rm, t_mshell *mshell)
{
	t_env *env;
	t_env *prev;

	prev = NULL;
	env = mshell->env;
	while (env->next && env->envar && ft_strcmp(env->envar, to_rm) != 0)
	{
		prev = env;
		env = env->next;
	}
	if (!env && !env->envar)
		return ;
	prev->next = env->next;
	free(env->envar);
	free(env->value);
}

void remove_expt(char *to_rm, t_mshell *mshell)
{
	t_expt *export;
	t_expt *prev;

	prev = NULL;
	export = mshell->expt;
	while (export->next && export->exptvar && ft_strcmp(export->exptvar, to_rm) != 0)
	{
		prev = export;
		export = export->next;
	}
	if (!export && !export->exptvar)
		return ;
	prev->next = export->next;
	free(export->exptvar);
	if (export->value)
		free(export->value);
}

int do_unset(t_mshell *mshell)
{
	t_tkn *args;

	if (mshell->exec->start_exec->next == NULL)
		return (1);
	args = mshell->exec->start_exec->next;
	while (args != NULL && args->tkn != NULL)
	{
		if (!check_current_unset_arg(args->tkn))
		{
			ft_putstr("minishell: export: '");
			ft_putstr(args->tkn);
			ft_putstr("': not a valid identifier\n");
		}
		remove_env(args->tkn, mshell);
		remove_expt(args->tkn, mshell);
		args = args->next;
	}
	(void)mshell;
	return (1);
}
