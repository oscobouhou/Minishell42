/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 20:51:03 by oboutarf          #+#    #+#             */
/*   Updated: 2023/02/09 00:02:49 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	absolute_path(t_mshell *mshell)
{
	while (mshell->exec->start_exec->type != _ARG)
		mshell->exec->start_exec = mshell->exec->start_exec->next;
	if (mshell->exec->start_exec->tkn[0] == '/')
	{
		if (chdir(mshell->exec->start_exec->tkn) == -1)
			return (0);
		return (1);
	}
	mshell->exec->start_exec = mshell->exec->start_exec_head;
	return (0);
}

int	cd_tilde(t_mshell *mshell)
{
	t_env	*head;
	char	*tmp;

	head = mshell->env;
	if (!mshell->exec->start_exec->next)
	{
		tmp = catch_enval(mshell, "HOME");
		if (chdir(tmp) == -1)
			return (0);
		mshell->env = head;
		change_enval(mshell, "PWD", tmp);
		mshell->env = head;
		return (1);
	}
	return (0);
}

int	cd_home(t_mshell *mshell)
{
	if (cd_tilde(mshell))
		return (1);
	if (mshell->exec->start_exec->next && !mshell->exec->start_exec->next->next)
		if (!ft_strcmp(mshell->exec->start_exec->next->tkn, "~"))
			return (cd_tilde(mshell), 1);
	return (0);
}

int	do_cd(t_mshell *mshell)
{
	char	*path;
	int		backup[2];

	unforked_builtin_redir_treat(mshell, backup);
	mshell->exec->start_exec = mshell->exec->start_exec_head;
	path = NULL;
	path = getcwd(path, 0);
	if (!path)
		return (error_manager("cd", path, strerror(errno)),
			exit_builtin(mshell, backup, 1), 1);
	change_enval(mshell, "OLDPWD", path);
	mshell->exec->start_exec = mshell->exec->start_exec_head;
	if (special_cd(mshell, path, backup))
		return (1);
	if (chdir(mshell->built->cd_chdir) == -1)
		return (error_manager("cd", mshell->built->cd_chdir, strerror(errno)), \
			free(path), exit_builtin(mshell, backup, 1), 0);
	free(path);
	path = getcwd(path, 0);
	change_enval(mshell, "PWD", path);
	free(path);
	path = NULL;
	exit_builtin(mshell, backup, 0);
	return (1);
}
