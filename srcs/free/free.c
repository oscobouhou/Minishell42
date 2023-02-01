/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 19:52:23 by oboutarf          #+#    #+#             */
/*   Updated: 2023/01/31 22:10:11 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int free_built_echo_tab(t_mshell *mshell)
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

int free_cmd_args_execve(t_mshell *mshell)
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

int free_paths_execve(t_mshell *mshell)
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

int free_built(t_mshell *mshell)
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
	(void)mshell;
	return (1);
}


void	terminate(t_mshell *mshell)
{
	free_t_env(mshell);
	free_exprt(mshell);
	free_built(mshell);
	free_expd(mshell);
	free_execve(mshell);
	free_exec(mshell);
	free(mshell);
}
