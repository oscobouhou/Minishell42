/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 20:51:03 by oboutarf          #+#    #+#             */
/*   Updated: 2023/01/29 19:02:07 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	re_establish_stdin_out(int *backup)
{
	dup2(backup[0], STDIN_FILENO);
	dup2(backup[1], STDOUT_FILENO);
	return (1);
}

int bckup_stdin_out(int *backup)
{
	backup[0] = dup(STDIN_FILENO);
	backup[1] = dup(STDOUT_FILENO);
	return (1);
}

int	cd_args_checker(t_mshell *mshell)
{
	int arg;

	arg = 0;
	while (mshell->exec->start_exec)
	{
		if (mshell->exec->start_exec->type == _ARG)
			arg++;
		if (arg > 1)
			return (0);
		mshell->exec->start_exec = mshell->exec->start_exec->next;
	}
	mshell->exec->start_exec = mshell->exec->start_exec_head;
	if (!arg)
		return (0);
	return (1);
}

int check_absolute(t_mshell *mshell)
{
	while (mshell->exec->start_exec != _ARG)
	{
		
	}
	return (1);
}

int do_cd(t_mshell *mshell)
{
    char	*path;
	int		backup[2];

	mshell->exec->start_exec = mshell->exec->start_exec_head;
	bckup_stdin_out(backup);
	enable_redirections(mshell);
	close_file_fd(mshell);
	path = NULL;
    path = getcwd(path, 0);
	if (!path)
		return (dprintf(2, "%s\n", strerror(errno)), 1);
	mshell->exec->start_exec = mshell->exec->start_exec_head;
	if (!cd_args_checker(mshell))
		return (dprintf(2, "minishell: cd: too many arguments\n"), 1);
	if (check_absolute(mshell))
	{
		
		return (1);
	}
	re_establish_stdin_out(backup);
	return (1);
}
