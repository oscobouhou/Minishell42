/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   center_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 16:41:14 by oboutarf          #+#    #+#             */
/*   Updated: 2023/01/28 00:41:58 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	manage_pipe(t_mshell *mshell, int *_pipe)
{
	if (*_pipe > 0)
	{
		dprintf(2, "%s listens to: %d  |%d  ---   %d|\n", mshell->exec->start_exec->tkn, mshell->exec->fd_p_listen, mshell->exec->fd_p[0], mshell->exec->fd_p[1]);
		dup2(mshell->exec->fd_p_listen, STDIN_FILENO);
		close(mshell->exec->fd_p[1]);
		// close(mshell->exec->fd_p[0]);
		// close(mshell->exec->fd_p_listen);
	}
	if (mshell->exec->fd == NULL && mshell->exec->next)
	{
		dprintf(2, "%s listens to: %d  |%d  ---   %d|\n", mshell->exec->start_exec->tkn, mshell->exec->fd_p_listen, mshell->exec->fd_p[0], mshell->exec->fd_p[1]);
		dup2(mshell->exec->fd_p[1], STDOUT_FILENO);
		close(mshell->exec->fd_p[0]);
		// close(mshell->exec->fd_p[1]);
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
	manage_pipe(mshell, _pipe);
	check = execve(mshell->execve->cmd, mshell->execve->cmd_args, env);
	if (check == -1)
		return (dprintf(2, "%s\n", strerror(errno)), exit(errno), 1);
	return (1);
}

int	wait_pids(t_mshell *mshell)
{
	while (mshell->exec)
	{
		waitpid(mshell->exec->pid, NULL, 0);
		mshell->exec = mshell->exec->next;
	}
	mshell->exec = mshell->head_exec;
	return (1);
}

int	open_pipes_fds(t_mshell *mshell)
{
	while (mshell->exec->next)
	{
		pipe(mshell->exec->fd_p);
		mshell->exec->next->fd_p_listen = mshell->exec->fd_p[0];
		mshell->exec = mshell->exec->next;
	}
	mshell->exec = mshell->head_exec;
	return (1);
}

int	close_pipes(t_mshell *mshell)
{
	while (mshell->exec)
	{
		close(mshell->exec->fd_p[0]);
		close(mshell->exec->fd_p[1]);
		close(mshell->exec->fd_p_listen);
		mshell->exec = mshell->exec->next;
	}
	mshell->exec = mshell->head_exec;
	return (1);
}

int center_exec(t_mshell *mshell, char **env)
{
	int 	_pipe;

	_pipe = 0;
    if (!init_exec(mshell))
		return (0);
	if (!build_commands_chains(mshell))
		return (0);
	mshell->exec = mshell->head_exec;
	if (mshell->exec->next)
		open_pipes_fds(mshell);
	mshell->exec = mshell->head_exec;
	while (mshell->exec)
	{
		mshell->exec->pid = fork();
		if (mshell->exec->pid == -1)
			return (dprintf(2, "%s\n"," Couldn't manage to fork for exec !"));
		else if (mshell->exec->pid == 0)
			execmd(mshell, env, &_pipe);
		ft_close(mshell);
		if (!mshell->exec->next)
			break ;
		close(mshell->exec->fd_p[1]);
		mshell->exec = mshell->exec->next;
		_pipe++;
	}
	mshell->exec = mshell->head_exec;
	wait_pids(mshell);
	mshell->exec = mshell->head_exec;
	close_pipes(mshell);
	return (1);
}
