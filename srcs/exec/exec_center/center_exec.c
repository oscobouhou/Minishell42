/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   center_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 16:41:14 by oboutarf          #+#    #+#             */
/*   Updated: 2023/02/01 03:46:52 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_process(int err, char *tkn, t_mshell *mshell)
{
	perror(tkn);
	close_file_fd(mshell);
	terminate(mshell);
	if (err == ENOENT)
		exit(127);
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

int	wait_pids(t_mshell *mshell)
{
	int status;

	while (mshell->exec)
	{
		waitpid(mshell->exec->pid, &status, 0);
		if (!mshell->exec->next)
			break ;
		mshell->exec = mshell->exec->next;
	}
	mshell->exit_status = WEXITSTATUS(status);
	return (1);
}

int execmd(t_mshell *mshell, char **env)
{
	find_access(mshell);
	seek_cmd_args(mshell);
	mshell->exec->start_exec = mshell->exec->start_exec_head;
	handle_tube(mshell);
	if (!enable_redirections(mshell))
		return (exit(0), 0);
	mshell->exec->start_exec = mshell->exec->start_exec_head;
	set_pos_to_cmd(mshell);
	scan_builtin(mshell);
	if (!ft_strlen(mshell->exec->start_exec->tkn))
		return (exit(0), 0);
	execve(mshell->execve->cmd, mshell->execve->cmd_args, env);
	exit_process(errno, mshell->execve->cmd_args[0], mshell);
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

int center_exec(t_mshell *mshell, char **env)
{
	int	backup[2];

	mshell->pipe_fd[0] = -42;
    if (!init_exec(mshell))
		return (0);
	if (!build_commands_chains(mshell))
		return (0);
	mshell->exec = mshell->head_exec;
	if (!mshell->exec->next && scan_builtin(mshell))
		return (1);
	if (!mshell->exec->next && mshell->exec && mshell->exec->no_cmd == 42)
		return (no_cmd_no_pipe(mshell, backup), 1);
	mshell->exec->start_exec = mshell->exec->start_exec;
	mshell->exec = mshell->head_exec;
	while (mshell->exec)
	{
		mshell->built->builtin_p = 42;
		popen_tube(mshell);
		mshell->exec->pid = fork();
		if (mshell->exec->pid == -1)
			return (dprintf(2, "\tfork: child failure\n"));
		if (mshell->exec->pid == 0)
			execmd(mshell, env);
		pclose_tube(mshell);
		close_file_fd(mshell);
		if (!mshell->exec->next)
			break ;
		mshell->exec->no_cmd = -42;
		mshell->exec = mshell->exec->next;
	}
	mshell->exec = mshell->head_exec;
	close_pipe_fds(mshell);
	mshell->exec = mshell->head_exec;
	wait_pids(mshell);
	mshell->exec = mshell->head_exec;
	return (1);
}
