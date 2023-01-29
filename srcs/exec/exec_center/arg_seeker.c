/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_seeker.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 13:02:44 by oboutarf          #+#    #+#             */
/*   Updated: 2023/01/29 02:52:16 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	mshell->execve->cmd_args[i + 1] = NULL;
	i = 0;
	copy_first_cmd_arg(mshell, &i);
	mshell->exec->start_exec = mshell->exec->start_exec_head;
	while (mshell->exec->start_exec)
	{
		if (mshell->exec->start_exec->type == _ARG)
		{
			copy_cmd_arg(mshell, &i);
		}
		mshell->exec->start_exec = mshell->exec->start_exec->next;
	}
	 i = 0;
    while (mshell->execve->cmd_args[i])
    {
        i++;
    }
	return (1);
}