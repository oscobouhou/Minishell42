/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 23:42:50 by oboutarf          #+#    #+#             */
/*   Updated: 2023/02/08 23:57:37 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_process(int err, char *tkn, t_mshell *mshell)
{
	perror(tkn);
	if (mshell->exec->no_redirs != -42)
		close_file_fd(mshell);
	terminate(mshell);
	if (err == ENOENT)
	{
		exit(127);
	}
	exit (1);
}

int	close_file_fd(t_mshell *mshell)
{
	if (mshell->exec->fd)
	{
		while (mshell->exec->n_fd > 0)
		{
			close(mshell->exec->fd[mshell->exec->n_fd - 1]);
			mshell->exec->n_fd--;
		}
	}
	return (1);
}

int	no_cmd_no_pipe(t_mshell *mshell, int *backup)
{
	bckup_stdin_out(backup);
	enable_redirections(mshell);
	close_file_fd(mshell);
	re_establish_stdin_out(backup);
	close(backup[0]);
	close(backup[1]);
	return (1);
}

int	unforked(t_mshell *mshell, int *backup)
{
	if (!mshell->exec->next && scan_builtin(mshell))
		return (0);
	if (!mshell->exec->next && mshell->exec && mshell->exec->no_cmd == 42)
		return (no_cmd_no_pipe(mshell, backup), 0);
	return (1);
}

int	start_exec(t_mshell *mshell, int *backup)
{
	backup[0] = -42;
	backup[1] = -42;
	mshell->pipe_fd[0] = -42;
	mshell->built->builtin_p = -42;
	if (!init_exec(mshell))
		return (0);
	if (!build_commands_chains(mshell))
		return (0);
	return (1);
}
