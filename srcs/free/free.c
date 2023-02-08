/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 19:52:23 by oboutarf          #+#    #+#             */
/*   Updated: 2023/02/08 12:40:29 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	free_heredoc(t_mshell *mshell)
{
	t_heredoc	*tmp;

	mshell->heredoc = mshell->hd_heredoc;
	tmp = mshell->heredoc;
	while (mshell->heredoc)
	{
		tmp = mshell->heredoc;
		mshell->heredoc = mshell->heredoc->next;
		free(tmp);
	}
	return (1);
}

int	free_expd(t_mshell *mshell)
{
	if (mshell->expd->update_tkn)
		free(mshell->expd->update_tkn);
	free(mshell->expd);
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

int	free_tab_exec_env(t_mshell *mshell)
{
	int	i;

	i = 0;
	while (mshell->exec_env[i])
	{
		free(mshell->exec_env[i]);
		i++;
	}
	free(mshell->exec_env);
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
	if (mshell->exec_env)
		free_tab_exec_env(mshell);
	if (mshell->heredoc)
		free_heredoc(mshell);
	free(mshell->rdline_outp);
	free(mshell);
}
