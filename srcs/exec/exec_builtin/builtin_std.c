/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_std.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 19:07:41 by oboutarf          #+#    #+#             */
/*   Updated: 2023/02/07 12:35:07 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unforked_builtin_redir_treat(t_mshell *mshell, int *backup)
{
	backup[0] = -42;
	backup[1] = -42;
	if (mshell->built->builtin_p == -42)
	{
		bckup_stdin_out(backup);
		enable_redirections(mshell);
	}
	return (1);
}

int	re_establish_stdin_out(int *backup)
{
	dup2(backup[0], STDIN_FILENO);
	dup2(backup[1], STDOUT_FILENO);
	close(backup[0]);
	close(backup[1]);
	return (1);
}

int	bckup_stdin_out(int *backup)
{
	backup[0] = dup(STDIN_FILENO);
	backup[1] = dup(STDOUT_FILENO);
	return (1);
}

int	exit_builtin(t_mshell *mshell, int *backup, int exit_code)
{
	if (mshell->built->builtin_p == 42)
	{
		terminate(mshell);
		exit(exit_code);
	}
	close_file_fd(mshell);
	re_establish_stdin_out(backup);
	mshell->exit_status = exit_code;
	return (1);
}
