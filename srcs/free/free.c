/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 19:52:23 by oboutarf          #+#    #+#             */
/*   Updated: 2023/02/02 11:47:46 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	free_built_echo_tab(t_mshell *mshell)
{
	int	n;

	n = 0;
	while (mshell->built->echo_arg[n])
	{
		free(mshell->built->echo_arg[n]);
		n++;
	}
	free(mshell->built->echo_arg);
	return (1);
}

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

int	free_expd(t_mshell *mshell)
{
	if (mshell->expd->expander)
		free(mshell->expd->expander);
	if (mshell->expd->update_tkn)
		free(mshell->expd->update_tkn);
	free(mshell->expd);
	return (1);
}

int	free_built(t_mshell *mshell)
{
	if (mshell->built->cd_arg)
		free(mshell->built->cd_arg);
	if (mshell->built->cd_chdir)
		free(mshell->built->cd_chdir);
	if (mshell->built->echo_arg)
		free_built_echo_tab(mshell);
	free(mshell->built);
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

int	free_exec(t_mshell *mshell)
{
	t_exec	*_tmp;
	t_tkn	*tmp;

	mshell->exec = mshell->head_exec;
	while (mshell->exec)
	{
		mshell->exec->start_exec = mshell->exec->start_exec_head;
		while (mshell->exec->start_exec)
		{
			free(mshell->exec->start_exec->tkn);
			tmp = mshell->exec->start_exec;
			mshell->exec->start_exec = mshell->exec->start_exec->next;
			free(tmp);
		}
		_tmp = mshell->exec;
		free(mshell->exec->fd);
		mshell->exec = mshell->exec->next;
		free(_tmp);
	}
	return (1);
}

void	terminate(t_mshell *mshell)
{
	if (mshell->env)
		free_t_env(mshell);
	if (mshell->expt)
		free_exprt(mshell);
	if (mshell->built)
		free_built(mshell);
	if (mshell->expd)
		free_expd(mshell);
	if (mshell->execve)
		free_execve(mshell);
	if (mshell->exec)
		free_exec(mshell);
	free(mshell->rdline_outp);
	free(mshell);
}
