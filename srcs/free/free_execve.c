/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_execve.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 12:36:56 by oboutarf          #+#    #+#             */
/*   Updated: 2023/02/08 12:38:40 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	free_cmd_args_execve(t_mshell *mshell)
{
	int	n;

	n = 0;
	while (mshell->execve->cmd_args[n])
	{
		free(mshell->execve->cmd_args[n]);
		n++;
	}
	free(mshell->execve->cmd_args);
	return (1);
}

int	free_paths_execve(t_mshell *mshell)
{
	int	n;

	n = 0;
	while (mshell->execve->paths[n])
	{
		free(mshell->execve->paths[n]);
		n++;
	}
	free(mshell->execve->paths);
	return (1);
}

int	free_execve(t_mshell *mshell)
{
	if (mshell->execve->cmd)
		free(mshell->execve->cmd);
	if (mshell->execve->paths)
		free_paths_execve(mshell);
	if (mshell->execve->cmd_args)
		free_cmd_args_execve(mshell);
	free(mshell->execve);
	return (1);
}
