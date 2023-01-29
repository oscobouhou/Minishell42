/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   center_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 16:41:14 by oboutarf          #+#    #+#             */
/*   Updated: 2023/01/29 02:54:31 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	close_pipe_fds(t_mshell *mshell)
{
	while (mshell->exec->next)
	{
		if (mshell->exec->fd_out != 1)
			close(mshell->exec->fd_out);
		if (mshell->exec->fd_in != 0)
			close(mshell->exec->fd_in);
		mshell->exec = mshell->exec->next;
	}
	mshell->exec = mshell->head_exec;
	return (1);
}

int	manage_pipe(t_mshell *mshell, int *_pipe)
{
	if (mshell->pipe_fd[0] != -42)
	{
		// first command //
		if (!*_pipe)
		{
			// dprintf(2, "first cmd: %s  --- fdin: %d    fdout: %d\n", mshell->exec->start_exec->tkn, mshell->exec->fd_in, mshell->exec->fd_out);
			dup2(mshell->exec->fd_out, STDOUT_FILENO);
			close(mshell->exec->fd_out);
		}
		// last command //
		else if (*_pipe && !mshell->exec->next)
		{
			// dprintf(2, "last cmd: %s  --- fdin: %d    fdout: %d\n", mshell->exec->start_exec->tkn, mshell->exec->fd_in, mshell->exec->fd_out);
			dup2(mshell->exec->fd_in, STDIN_FILENO);
			close(mshell->exec->fd_in);
		}
		// matchmaker command
		else
		{
			// dprintf(2, "matchmaker: %s  --- fdin: %d    fdout: %d\n", mshell->exec->start_exec->tkn, mshell->exec->fd_in, mshell->exec->fd_out);
			dup2(mshell->exec->fd_in, STDIN_FILENO);
			close(mshell->exec->fd_in);
			dup2(mshell->exec->fd_out, STDOUT_FILENO);
			close(mshell->exec->fd_out);
		}
	}
	return (1);
}

int	ft_close(t_mshell *mshell)
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

int	set_pos_to_cmd(t_mshell *mshell)
{
	while (mshell->exec->start_exec->type != _CMD)
		mshell->exec->start_exec = mshell->exec->start_exec->next;
	return (1);
}

int execmd(t_mshell *mshell, char **env, int *_pipe)
{
	int check;

	check = -42;
	mshell->exec->start_exec = mshell->exec->start_exec_head;
	find_access(mshell);
	mshell->exec->start_exec = mshell->exec->start_exec_head;
	seek_cmd_args(mshell);
	mshell->exec->start_exec = mshell->exec->start_exec_head;
	enable_redirections(mshell);
	mshell->exec->start_exec = mshell->exec->start_exec_head;
	//manage_pipe(mshell, _pipe);
	if (mshell->exec->fd_in != 0)
	{
		// dprintf(2, "out %s  ---   %d    $PID: %d\n", mshell->exec->start_exec->tkn, *_pipe, mshell->exec->pid);
		dup2(  mshell->exec->fd_in , STDIN_FILENO );
		close( mshell->exec->fd_in );
	}
	if (mshell->exec->fd_out != 1)
	{
		// dprintf(2, "out %s  ---   %d    $PID: %d\n", mshell->exec->start_exec->tkn, *_pipe, mshell->exec->pid);
		dup2(  mshell->exec->fd_out , STDOUT_FILENO );
		close( mshell->exec->fd_out );
	}
	if (mshell->exec->next) 
	{
		close( mshell->exec->next->fd_in );
	}
	check = execve(mshell->execve->cmd, mshell->execve->cmd_args, env);
	if (check == -1)
		return (dprintf(2, "%s\n", strerror(errno)), exit(errno), 1);
	(void)_pipe;
	return (1);
}

int center_exec(t_mshell *mshell, char **env)
{
		//		--- exec start ---		//
	int _pipe;

	_pipe = 0;
	mshell->pipe_fd[0] = -42;
    if (!init_exec(mshell))
		return (0);
	if (!build_commands_chains(mshell))
		return (0);
	mshell->exec = mshell->head_exec;
	while (mshell->exec)
	{
		// pipe opening for the child //
		if (mshell->exec->next)
		{
			if (pipe(mshell->pipe_fd) == -1)
				return (dprintf(2, "\tpipe: open failure\n"));
			mshell->exec->next->fd_in = mshell->pipe_fd[0];
			mshell->exec->fd_out = mshell->pipe_fd[1];
		}
			// fork child //
		mshell->exec->pid = fork();
		if (mshell->exec->pid == -1)
			return (dprintf(2, "\tfork: child %d failure\n", _pipe));
		// child executes command //
		if (mshell->exec->pid == 0)
			execmd(mshell, env, &_pipe);
	// Close pipe extremities in the parent //
		if (mshell->exec->fd_in != 0)
			close(mshell->exec->fd_in);
		if (mshell->exec->fd_out != 1)
			close(mshell->exec->fd_out);
			// Break loop to avoid segfualt
		if (!mshell->exec->next)
			break ;
		 // parent goes to next cmd //
		mshell->exec = mshell->exec->next;
		_pipe++;
	}
	// close all fd's opened for piping //
	mshell->exec = mshell->head_exec;
	close_pipe_fds(mshell);
//	after launching all childs parent waits their return //
	mshell->exec = mshell->head_exec;
	while (mshell->exec)
	{
		waitpid(mshell->exec->pid, NULL, 0);
		if (!mshell->exec->next)
			break ;
		mshell->exec = mshell->exec->next;
	}
	mshell->exec = mshell->head_exec;
		//		--- end exec ---		//
	return (1);
}
