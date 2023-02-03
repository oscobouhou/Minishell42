/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mshell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 19:52:04 by oboutarf          #+#    #+#             */
/*   Updated: 2023/02/03 08:24:30 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	copy_underscore(t_mshell *mshell)
{
	char	*underscore;
	int		i;

	i = 0;
	underscore = "/usr/bin/env";
	mshell->env->envar = malloc(sizeof(char) * 2);
	if (!mshell->env->envar)
		return (0);
	mshell->env->value = malloc(sizeof(char) * (ft_strlen(underscore) + 1));
	if (!mshell->env->value)
		return (0);
	mshell->env->envar[0] = '_';
	mshell->env->envar[1] = '\0';
	while (underscore[i])
	{
		mshell->env->value[i] = underscore[i];
		i++;
	}
	mshell->env->value[i] = '\0';
	return (1);
}

int	copy_pwd(t_mshell *mshell, char *pwd_var, char *pwd)
{
	int	i;

	i = 0;
	mshell->env->envar = malloc(sizeof(char) * ((ft_strlen(pwd_var) + 1)));
	if (!mshell->env->envar)
		return (0);
	mshell->env->value = malloc(sizeof(char) * (ft_strlen(pwd) + 1));
	if (!mshell->env->value)
		return (0);
	while (pwd_var[i])
	{
		mshell->env->envar[i] = pwd_var[i];
		i++;
	}
	mshell->env->envar[i] = '\0';
	i = 0;
	while (pwd[i])
	{
		mshell->env->value[i] = pwd[i];
		i++;
	}
	mshell->env->value[i] = '\0';
	return (1);
}

int	copy_shlvl(t_mshell *mshell, char *shlvl)
{
	int	i;

	mshell->env->envar = malloc(sizeof(char) * (ft_strlen(shlvl) + 1));
	if (!mshell->env->envar)
		return (0);
	mshell->env->value = malloc(sizeof(char) * (1 + 1));
	if (!mshell->env->value)
		return (0);
	i = 0;
	while (shlvl[i])
	{
		mshell->env->envar[i] = shlvl[i];
		i++;
	}
	mshell->env->envar[i] = '\0';
	mshell->env->value[0] = '1';
	mshell->env->value[1] = '\0';
	return (1);
}

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
		mshell->expt->exptvar = ft_strdup(mshell->env->envar);
		if (!mshell->expt->exptvar)
			return (0);
		mshell->expt->value = ft_strdup(mshell->env->value);
		if (!mshell->expt->value)
			return (0);
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

int	begin_command(t_mshell *mshell, char **env)
{
	if (*env)
	{
		if (!dup_env(&mshell->env, env, &mshell->envc))
			return (0);
		if (!sort_export(mshell))
			return (0);
		mshell->exec_env = copy_env_in_tab(mshell);
		if (!mshell->exec_env)
			return (0);
	}
	else
	{
		set_default_env(mshell);
		set_default_export(mshell);
		mshell->exec_env = copy_env_in_tab(mshell);
		if (!mshell->exec_env)
			return (0);
	}
	return (1);
}

t_mshell	*init_mshell(char **env)
{
	t_mshell	*mshell;

	mshell = malloc(sizeof(t_mshell));
	if (!mshell)
		return (NULL);
	mshell->env = NULL;
	mshell->tkn = NULL;
	mshell->expt = NULL;
	mshell->expd = NULL;
	mshell->exec = NULL;
	mshell->execve = NULL;
	mshell->no_env = 420;
	mshell->empty_cmd = 0;
	mshell->exit_status = 0;
	mshell->exec_env = NULL;
	mshell->pipe_fd[0] = -42;
	mshell->pipe_fd[1] = -42;
	mshell->old_expd__hrdoc = -42;
	if (!begin_command(mshell, env))
		return (NULL);
	return (mshell);
}
