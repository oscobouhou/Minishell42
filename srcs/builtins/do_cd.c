/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 20:51:03 by oboutarf          #+#    #+#             */
/*   Updated: 2023/02/02 02:22:58 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	int arg;

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

int	join_pwd_to_directory(t_mshell *mshell, char *path)
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
		return (free(mshell->built->cd_chdir), mshell->built->cd_chdir = NULL, 1);
	i = 0;
	j = 0;
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

int absolute_path(t_mshell *mshell, int *backup)
{
	while (mshell->exec->start_exec->type != _ARG)
		mshell->exec->start_exec = mshell->exec->start_exec->next;
	if (mshell->exec->start_exec->tkn[0] == '/')
	{
		if (chdir(mshell->exec->start_exec->tkn) == -1)
			return (dprintf(2, "%s\n", strerror(errno)), exit_builtin(mshell, backup), 0);
		return (1);
	}
	mshell->exec->start_exec = mshell->exec->start_exec_head;
	return (0);
}

int do_cd(t_mshell *mshell)
{
    char	*path;
	int		backup[2];

	backup[0] = -42;
	backup[1] = -42;
	if (mshell->built->builtin_p == -42)
	{
		dprintf(2, "%s\n", "went_here_ENTER");
        bckup_stdin_out(backup);
		enable_redirections(mshell);
	}
	mshell->exec->start_exec = mshell->exec->start_exec_head;
	path = NULL;
    path = getcwd(path, 0);
	if (!path)
		return (dprintf(2, "%s\n", strerror(errno)), exit_builtin(mshell, backup), 1);
	mshell->exec->start_exec = mshell->exec->start_exec_head;
	if (!cd_args_checker(mshell))
		return (dprintf(2, "minishell: cd: too many arguments\n"), exit_builtin(mshell, backup), 1);
	if (absolute_path(mshell, backup))
		return (exit_builtin(mshell, backup), 1);
	join_pwd_to_directory(mshell, path);
	if (chdir(mshell->built->cd_chdir) == -1)
		return (dprintf(2, "%s\n", strerror(errno)), exit_builtin(mshell, backup), 0);
	if (mshell->built->builtin_p == -42)
	{
		dprintf(2, "%s\n", "went_here_EXIT");
		exit_builtin(mshell, backup);
	}
	return (1);
}
