/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 11:58:42 by oboutarf          #+#    #+#             */
/*   Updated: 2023/02/08 11:33:26 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	assembling_pwdir__cd(t_mshell *mshell, char *path, int i, int j)
{
	while (path[i])
	{
		mshell->built->cd_chdir[i] = path[i];
		i++;
	}
	mshell->built->cd_chdir[i] = '/';
	i += 1;
	while (mshell->built->cd_arg[j])
	{
		mshell->built->cd_chdir[i] = mshell->built->cd_arg[j];
		i++;
		j++;
	}
	mshell->built->cd_chdir[i] = '\0';
	return (1);
}

int	cd_join_pwd_to_directory(t_mshell *mshell, char *path)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (path[i])
		i++;
	i += 1;
	while (mshell->built->cd_arg[j])
		j++;
	mshell->built->cd_chdir = malloc(sizeof(char) * ((i + j) + 1));
	if (!mshell->built->cd_chdir)
		return (0);
	if (!i && !j)
		return (free(mshell->built->cd_chdir),
			mshell->built->cd_chdir = NULL, 1);
	i = 0;
	j = 0;
	assembling_pwdir__cd(mshell, path, i, j);
	return (1);
}

int	copy_cd_arg(t_mshell *mshell)
{
	int	i;

	i = 0;
	while (mshell->exec->start_exec->tkn[i])
		i++;
	mshell->built->cd_arg = malloc(sizeof(char) * (i + 1));
	if (!mshell->built->cd_arg)
		return (0);
	i = 0;
	while (mshell->exec->start_exec->tkn[i])
	{
		mshell->built->cd_arg[i] = mshell->exec->start_exec->tkn[i];
		i++;
	}
	mshell->built->cd_arg[i] = '\0';
	return (1);
}

int	cd_args_checker(t_mshell *mshell)
{
	int	arg;

	arg = 0;
	while (mshell->exec->start_exec)
	{
		if (mshell->exec->start_exec->type == _ARG)
		{
			if (!arg)
				copy_cd_arg(mshell);
			arg++;
		}
		if (arg > 1)
			return (0);
		mshell->exec->start_exec = mshell->exec->start_exec->next;
	}
	mshell->exec->start_exec = mshell->exec->start_exec_head;
	if (!arg)
		return (0);
	return (1);
}
