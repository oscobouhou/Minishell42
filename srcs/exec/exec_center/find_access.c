/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_access.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 13:04:06 by oboutarf          #+#    #+#             */
/*   Updated: 2023/02/03 00:30:03 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int rewind_cmd(t_mshell *mshell)
{
	int	i;

	i = 0;
	while (mshell->exec->start_exec->tkn[i])
		i++;
	mshell->execve->cmd = malloc(sizeof(char) * (i + 1));
	if (!mshell->execve->cmd)
		return (0);
	i = 0;
	while (mshell->exec->start_exec->tkn[i])
	{
		mshell->execve->cmd[i] = mshell->exec->start_exec->tkn[i];
		i++;
	}
	mshell->execve->cmd[i] = '\0';
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

int	find_access(t_mshell *mshell)
{
	int		i;
	int		a;

	i = 0;
	if (mshell->exec->no_cmd == 42 || mshell->exec->start_exec->type != _CMD)
		return (1);
	set_pos_to_cmd(mshell);
	while (mshell->execve->paths[i])
	{
		join_cmd_for_access(mshell, &i);
		a = access(mshell->execve->cmd, X_OK | F_OK);
		if (!a)
			return (mshell->exec->start_exec = mshell->exec->start_exec_head, 1);
		free(mshell->execve->cmd);
		mshell->execve->cmd = NULL;
		i++;
	}
	rewind_cmd(mshell);
	mshell->exec->start_exec = mshell->exec->start_exec_head;
	return (0);
}
