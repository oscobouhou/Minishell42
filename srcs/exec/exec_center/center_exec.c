/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   center_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 16:41:14 by oboutarf          #+#    #+#             */
/*   Updated: 2023/01/26 19:01:13 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_close(t_mshell *mshell)
{
	int	fd;

	fd = 0;
	while (mshell->exec->fd[fd])
	{
		close(mshell->exec->fd[fd]);
		fd++;
	}
	return (1);
}

int	join_cmd_for_access(t_mshell *mshell, int *i)
{
	char	*cmd_tmp;
	int	a;
	int j;

	a = ft_strlen(mshell->execve->paths[*i]);
	j = ft_strlen(mshell->exec->start_exec->tkn);
	cmd_tmp = malloc(sizeof(char) * (a + j + 1));
	if (!cmd_tmp)
		return (0);
	a = 0;
	j = 0;
	while (mshell->execve->paths[*i][a])
	{
		cmd_tmp[j] = mshell->execve->paths[*i][a];
		a++;
		j++;	
	}
	a = 0;
	while (mshell->exec->start_exec->tkn[a])
	{
		cmd_tmp[j] = mshell->exec->start_exec->tkn[a];
		a++;
		j++;	
	}
	cmd_tmp[j] = '\0';
	mshell->execve->cmd = cmd_tmp;
	return (1);
}

int	set_pos_to_cmd(t_mshell *mshell)
{
	while (mshell->exec->start_exec->type != _CMD)
		mshell->exec->start_exec = mshell->exec->start_exec->next;
	return (1);
}

int	find_access(t_mshell *mshell)
{
	int		i;
	int		a;

	i = 0;
	set_pos_to_cmd(mshell);
	while (mshell->execve->paths[i])
	{
		join_cmd_for_access(mshell, &i);
		a = access(mshell->execve->cmd, X_OK);
		if (!a)
			return (1);
		free(mshell->execve->cmd);
		mshell->execve->cmd = NULL;
		i++;
	}
	return (0);
}


int	copy_first_cmd_arg(t_mshell *mshell, int *i)
{
	int	i1;

	i1 = 0;
	mshell->execve->cmd_args[*i] = malloc(sizeof(char) * (ft_strlen(mshell->execve->cmd) + 1));
	if (!mshell->execve->cmd_args[*i])
		return (0);
	while (mshell->execve->cmd[i1])
	{
		mshell->execve->cmd_args[*i][i1] = mshell->execve->cmd[i1];
		i1++;
	}
	mshell->execve->cmd_args[*i][i1] = '\0';
	(*i)++;
	return (1);
}

int	copy_cmd_arg(t_mshell *mshell, int *i)
{
	int	i1;

	i1 = 0;
	mshell->execve->cmd_args[*i] = malloc(sizeof(char) * (ft_strlen(mshell->exec->start_exec->tkn) + 1));
	if (!mshell->execve->cmd_args[*i])
		return (0);
	while (mshell->exec->start_exec->tkn[i1])
	{
		mshell->execve->cmd_args[*i][i1] = mshell->exec->start_exec->tkn[i1];
		i1++;
	}
	mshell->execve->cmd_args[*i][i1] = '\0';
	(*i)++;
	return (1);
}

int	seek_cmd_args(t_mshell *mshell)
{
	int	i;
	
	i = 0;
	mshell->exec->start_exec = mshell->exec->start_exec_head;
	while (mshell->exec->start_exec)
	{
		if (mshell->exec->start_exec->type == _ARG)
			i++;
		mshell->exec->start_exec = mshell->exec->start_exec->next;
	}
	mshell->exec->start_exec = mshell->exec->start_exec_head;
	mshell->execve->cmd_args = malloc(sizeof(char *) * (i + 2));
	if (!mshell->execve->cmd_args)
		return (0);
	i = 0;
	copy_first_cmd_arg(mshell, &i);
	mshell->exec->start_exec = mshell->exec->start_exec_head;
	while (mshell->exec->start_exec)
	{
		if (mshell->exec->start_exec->type == _ARG)
			copy_cmd_arg(mshell, &i);
		mshell->exec->start_exec = mshell->exec->start_exec->next;
	}
	return (1);
}

int execmd(t_mshell *mshell, char **env)
{
	pid_t	pid;

	if (mshell->exec->next)
	{
		close(STDOUT_FILENO);
		pipe(mshell->pipe_fd);
		dup2(mshell->pipe_fd[0], STDOUT_FILENO);
		close(mshell->pipe_fd[1]);
	}
	if (!mshell->exec->next)
	{
		close(STDIN_FILENO);
		dup2(mshell->pipe_fd[1], STDIN_FILENO);
		close(mshell->pipe_fd[0]);
	}
	mshell->exec->start_exec = mshell->exec->start_exec_head;
	pid = fork();
	if (pid == -1)
		return (dprintf(2, "%s\n"," Couldn't manage to fork for exec !"));
	if (pid == 0)
	{
		if (find_access(mshell))
			dprintf(2, "\n --- ACCESS FOUND --- \n\n");
		mshell->exec->start_exec = mshell->exec->start_exec_head;
		seek_cmd_args(mshell);
		mshell->exec->start_exec = mshell->exec->start_exec_head;
		enable_redirections(mshell);
		mshell->exec->start_exec = mshell->exec->start_exec_head;
		execve(mshell->execve->cmd, mshell->execve->cmd_args, env);
	}
	waitpid(pid, NULL, 0);
	return (1);
}

int	open_pipes(t_mshell *mshell)
{
	while (mshell->exec)
	{
		if (pipe(mshell->exec->pipe_fd) == -1)
			return (0);
		if (!mshell->exec->next)
			break ;
		mshell->exec = mshell->exec->next;
	}
	mshell->exec = mshell->head_exec;
	return (1);
}

int center_exec(t_mshell *mshell, char **env)
{
    if (!init_exec(mshell))
		return (0);
	if (!build_commands_chains(mshell))
		return (0);
	// print_exec_chains(mshell);
	// mshell->exec = mshell->head_exec;
	// if (mshell->exec->next)
	// 	open_pipes(mshell);
	mshell->exec = mshell->head_exec;
	while (mshell->exec)
	{
		execmd(mshell, env);
		if (!mshell->exec->next)
			break ;
		mshell->exec = mshell->exec->next;
	}
    return (1);
}
