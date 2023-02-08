/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_env_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 11:26:40 by oboutarf          #+#    #+#             */
/*   Updated: 2023/02/08 11:28:14 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	fill_default_export(t_mshell *mshell)
{
	mshell->expt->exptvar = ft_strdup(mshell->env->envar);
	if (!mshell->expt->exptvar)
		return (0);
	mshell->expt->value = ft_strdup(mshell->env->value);
	if (!mshell->expt->value)
		return (0);
	return (1);
}

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
