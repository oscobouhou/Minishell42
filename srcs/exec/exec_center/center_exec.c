/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   center_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 16:41:14 by oboutarf          #+#    #+#             */
/*   Updated: 2023/02/08 11:10:44 by oboutarf         ###   ########.fr       */
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

int	wait_pids(t_mshell *mshell)
{
	int	status;

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

void	command_child_execve(t_mshell *mshell)
{
	if (mshell->exec->no_cmd == -42 && mshell->execve->cmd)
	{
		if (mshell->exec->start_exec->tkn[0] == '/')
			if (access(mshell->exec->start_exec->tkn, X_OK | F_OK))
				execve(mshell->exec->start_exec->tkn, mshell->execve->cmd_args,
					mshell->exec_env);
		execve(mshell->execve->cmd, mshell->execve->cmd_args, mshell->exec_env);
		exit_process(errno, mshell->tkn->tkn, mshell);
	}
}

int	execmd(t_mshell *mshell, char **env)
{
	signal(SIGINT, &sig_fork_handler);
	set_pos_to_cmd(mshell);
	if (mshell->no_env != -42)
	{
		find_access(mshell);
		seek_cmd_args(mshell);
	}
	mshell->exec->start_exec = mshell->exec->start_exec_head;
	handle_tube(mshell);
	if (!enable_redirections(mshell))
		return (terminate(mshell), exit(1), 0);
	mshell->exec->start_exec = mshell->exec->start_exec_head;
	scan_builtin(mshell);
	command_child_execve(mshell);
	if (mshell->exec->no_redirs != -42)
		close_file_fd(mshell);
	if (mshell->exec->next)
		close_pipe_fds(mshell);
	terminate(mshell);
	exit(0);
	(void)env;
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

void	retrieve_signals(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &sig_handler);
}

int	start_cmd_pipeline(t_mshell *mshell)
{
	mshell->built->builtin_p = 42;
	popen_tube(mshell);
	mshell->exec->pid = fork();
	if (mshell->exec->pid == -1)
		return (dprintf(2, "\tfork: child failure\n"));
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

int	controler(t_mshell *mshell)
{
	pclose_tube(mshell);
	close_file_fd(mshell);
	if (!mshell->exec->next)
		return (0);
	return (1);
}

int	close_heredocs(t_mshell *mshell)
{
	t_heredoc	*head;

	head = mshell->hd_heredoc;
	while (mshell->heredoc)
	{
		if (mshell->heredoc->pipe_heredoc[0] != -42)
			close(mshell->heredoc->pipe_heredoc[0]);
		if (mshell->heredoc->pipe_heredoc[1] != -42)
			close(mshell->heredoc->pipe_heredoc[1]);
		mshell->heredoc = mshell->heredoc->next;
	}
	mshell->heredoc = head;
	return (1);
}

int	heredoc_controler(t_mshell *mshell)
{
	if (mshell->heredoc->pipe_heredoc[0] != -42)
		close(mshell->heredoc->pipe_heredoc[0]);
	return (1);
}

int	center_exec(t_mshell *mshell, char **env)
{
	int	backup[2];

	if (!start_exec(mshell, backup))
		return (0);
	mshell->exec = mshell->head_exec;
	if (!unforked(mshell, backup))
		return (1);
	stop_signals();
	while (mshell->exec)
	{
		start_cmd_pipeline(mshell);
		if (mshell->exec->pid == 0)
			execmd(mshell, env);
		if (!controler(mshell))
			break ;
		heredoc_controler(mshell);
		mshell->exec = mshell->exec->next;
		mshell->heredoc = mshell->heredoc->next;
		mshell->exec->no_cmd = -42;
	}
	close_heredocs(mshell);
	mshell->exec = mshell->head_exec;
	close_pipe_fds(mshell);
	mshell->exec = mshell->head_exec;
	wait_pids(mshell);
	retrieve_signals();
	mshell->exec = mshell->head_exec;
	return (1);
}
