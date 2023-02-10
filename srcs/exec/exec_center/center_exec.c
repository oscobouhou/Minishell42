/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   center_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 16:41:14 by oboutarf          #+#    #+#             */
/*   Updated: 2023/02/10 07:58:52 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit;

int	search_absolute(t_mshell *mshell)
{
	(void)mshell;
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

int	close_parent_process(t_mshell *mshell)
{
	close_heredocs(mshell);
	mshell->exec = mshell->head_exec;
	close_pipe_fds(mshell);
	mshell->exec = mshell->head_exec;
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
	close_parent_process(mshell);
	wait_pids(mshell);
	retrieve_signals();
	mshell->exec = mshell->head_exec;
	return (1);
}
