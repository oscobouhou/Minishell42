/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_env_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 11:24:34 by oboutarf          #+#    #+#             */
/*   Updated: 2023/02/08 11:28:26 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_default_export(t_mshell *mshell)
{
	t_expt	*head_expt;
	t_env	*head_env;

	head_env = mshell->env;
	mshell->expt = malloc(sizeof(t_expt));
	if (!mshell->expt)
		return (0);
	head_expt = mshell->expt;
	while (mshell->env)
	{
		fill_default_export(mshell);
		if (!mshell->env->next)
			break ;
		mshell->expt->next = malloc(sizeof(t_expt));
		if (!mshell->expt->next)
			return (0);
		mshell->expt = mshell->expt->next;
		mshell->env = mshell->env->next;
	}
	mshell->expt->next = NULL;
	mshell->env = head_env;
	mshell->expt = head_expt;
	return (1);
}

int	set_default_envars(t_mshell *mshell)
{
	char	pwd[1024];
	char	*pwd_var;
	char	*shlvl;
	t_env	*head;

	shlvl = "SHLVL";
	pwd_var = "PWD";
	head = mshell->env;
	getcwd(pwd, 1024);
	copy_pwd(mshell, pwd_var, pwd);
	mshell->env->next = malloc(sizeof(t_env));
	if (!mshell->env->next)
		return (0);
	mshell->env = mshell->env->next;
	copy_shlvl(mshell, shlvl);
	mshell->env->next = malloc(sizeof(t_env));
	if (!mshell->env->next)
		return (0);
	mshell->env = mshell->env->next;
	copy_underscore(mshell);
	mshell->env->next = NULL;
	mshell->env = head;
	return (1);
}

int	set_default_env(t_mshell *mshell)
{
	mshell->env = malloc(sizeof(t_env));
	if (!mshell->env)
		return (0);
	mshell->env->next = NULL;
	mshell->env->envar = NULL;
	mshell->env->value = NULL;
	set_default_envars(mshell);
	return (1);
}