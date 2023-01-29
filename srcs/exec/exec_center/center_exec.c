/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   center_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 16:41:14 by oboutarf          #+#    #+#             */
/*   Updated: 2023/01/29 23:33:20 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	close_file_fd(t_mshell *mshell)
{
	int	fd;

	fd = 0;
	if (mshell->exec->fd)
	{
		while (mshell->exec->fd[fd])
		{
			close(mshell->exec->fd[fd]);
			fd++;
		}
	}
	return (1);
}

int	wait_pids(t_mshell *mshell)
{
	while (mshell->exec)
	{
		waitpid(mshell->exec->pid, NULL, 0);
		if (!mshell->exec->next)
			break ;
		mshell->exec = mshell->exec->next;
	}
	return (1);
}

int execmd(t_mshell *mshell, char **env)
{
	int check;

	check = -42;
	mshell->exec->start_exec = mshell->exec->start_exec_head;
	find_access(mshell);
	mshell->exec->start_exec = mshell->exec->start_exec_head;
	seek_cmd_args(mshell);
	mshell->exec->start_exec = mshell->exec->start_exec_head;
	handle_tube(mshell);
	mshell->exec->start_exec = mshell->exec->start_exec_head;
	enable_redirections(mshell);
	if (mshell->exec->no_cmd == -42)
		return (close_file_fd(mshell), exit(1), 1);
	check = execve(mshell->execve->cmd, mshell->execve->cmd_args, env);
	if (check == -1)
		return (dprintf(2, "%s\n", strerror(errno)), exit(errno), 1);
	return (1);
}

/* int	no_cmd_to_exec(t_mshell *mshell)
{
	
} */

int center_exec(t_mshell *mshell, char **env)
{
	mshell->pipe_fd[0] = -42;
    if (!init_exec(mshell))
		return (0);
	if (!build_commands_chains(mshell))
		return (0);
	mshell->exec = mshell->head_exec;
	if (!mshell->exec->next && scan_builtin(mshell))
		return (1);
	if (!mshell->exec->next && mshell->exec && mshell->exec->no_cmd == -42)
	{
		enable_redirections(mshell);
		close_file_fd(mshell);
		return (1);
	}
	mshell->exec->start_exec = mshell->exec->start_exec;
	mshell->exec = mshell->head_exec;
	while (mshell->exec)
	{
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
		mshell->exec = mshell->exec->next;
	}
	mshell->exec = mshell->head_exec;
	close_pipe_fds(mshell);
	mshell->exec = mshell->head_exec;
	wait_pids(mshell);
	mshell->exec = mshell->head_exec;
	return (1);
}
