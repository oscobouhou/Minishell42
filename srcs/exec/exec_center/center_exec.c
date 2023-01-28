/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   center_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 16:41:14 by oboutarf          #+#    #+#             */
/*   Updated: 2023/01/28 06:27:27 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	close_pipes_forking(t_mshell *mshell)
{
	int	i;

	i = 0;
	mshell->exec = mshell->head_exec;
	if (mshell->pipe_fd)
	{
		while (mshell->exec->next)
		{
			// close(mshell->pipe_fd[i][0]);
			// close(mshell->pipe_fd[i][1]);
			mshell->exec = mshell->exec->next;
			i++;
		}
	}
	mshell->exec = mshell->head_exec;
	return (1);
}

int	manage_pipe(t_mshell *mshell, int *_pipe)
{
	if (mshell->pipe_fd)
	{
		if (!*_pipe)
		{
			// close(mshell->pipe_fd[*_pipe][0]);
			dup2(mshell->pipe_fd[*_pipe][1], STDOUT_FILENO);
			close(mshell->pipe_fd[*_pipe][1]);
			close(mshell->pipe_fd[*_pipe][0]);
		}
		else if (*_pipe && !mshell->exec->next)
		{
			// close(mshell->pipe_fd[*_pipe - 1][1]);
			dup2(mshell->pipe_fd[*_pipe - 1][0], STDIN_FILENO);
			close(mshell->pipe_fd[*_pipe - 1][0]);
			close(mshell->pipe_fd[*_pipe - 1][1]);
		}
		else
		{
			close(mshell->pipe_fd[*_pipe - 1][1]);
			dup2(mshell->pipe_fd[*_pipe - 1][0], STDIN_FILENO);
			close(mshell->pipe_fd[*_pipe - 1][0]);
			close(mshell->pipe_fd[*_pipe][0]);
			dup2(mshell->pipe_fd[*_pipe][1], STDOUT_FILENO);
			// close(mshell->pipe_fd[*_pipe][1]);
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
	manage_pipe(mshell, _pipe);
	// mshell->exec->start_exec = mshell->exec->start_exec_head;
	// close_pipes_forking(mshell);
	check = execve(mshell->execve->cmd, mshell->execve->cmd_args, env);
	if (check == -1)
		return (dprintf(2, "%s\n", strerror(errno)), exit(errno), 1);
	return (1);
}

int	wait_pids(t_mshell *mshell)
{
	// while (mshell->exec->next)
	// {
	// 	waitpid(mshell->exec->pid, NULL, 0);
	// 	if (mshell->exec->next)
	// 		break ;
	// 	mshell->exec = mshell->exec->next;
	// }
	// mshell->exec = mshell->head_exec;
	(void)mshell;
	return (1);
}

int	open_pipes_fds(t_mshell *mshell){
	int	i;
	int p;

	i = 0;
	while (mshell->exec->next)
	{
		mshell->exec = mshell->exec->next;
		i++;
	}
	mshell->pipe_fd = malloc(sizeof(int *) * (i + 1));
	if (!mshell->pipe_fd)
		return (dprintf(2, "\tmalloc: failure"), 0);
	i = 0;
	mshell->exec = mshell->head_exec;
	while (mshell->exec->next)
	{
		mshell->pipe_fd[i] = malloc(sizeof(int) * 2);
		if (!mshell->pipe_fd[i])
			return (dprintf(2, "\tmalloc: failure"), 0);
		mshell->pipe_fd[i][0] = -42;
		mshell->pipe_fd[i][1] = -42;
		p = pipe(mshell->pipe_fd[i]);
		if (p == -1)
			return (dprintf(2, "\tpipe: creation failure\n"));
		mshell->exec = mshell->exec->next;
		i++;
	}
	mshell->exec = mshell->head_exec;
	return (1);
}

int	close_pipes(t_mshell *mshell)
{
	int	i;
	
	i = 0;
	mshell->exec = mshell->head_exec;
	while (mshell->exec->next)
	{
		close(mshell->pipe_fd[i][0]);
		close(mshell->pipe_fd[i][1]);
		free(mshell->pipe_fd[i]);
		mshell->exec = mshell->exec->next;
		i++;
	}
	free(mshell->pipe_fd);
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
	else
		mshell->pipe_fd = NULL; 
	mshell->exec = mshell->head_exec;
	while (mshell->exec)
	{
		mshell->exec->pid = fork();
		if (mshell->exec->pid == -1)
			return (dprintf(2, "\tfork: failed for child %d\n", _pipe + 1));
		if (mshell->exec->pid == 0)
			execmd(mshell, env, &_pipe);
		if (!mshell->exec->next)
			break ;
		mshell->exec = mshell->exec->next;
		_pipe++;
	}
	waitpid(mshell->exec->pid, NULL, 0);
	mshell->exec = mshell->head_exec;
	// wait_pids(mshell);
	mshell->exec = mshell->head_exec;
	close_pipes(mshell);
	mshell->exec = mshell->head_exec;
	return (1);

}
