/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_control.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 23:39:15 by oboutarf          #+#    #+#             */
/*   Updated: 2023/02/09 14:14:30 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	wait_pids(t_mshell *mshell)
{
	int	status;

	while (mshell->exec)
	{
		waitpid(mshell->exec->pid, &status, 0);
		if (!mshell->exec->next)
			break ;
		mshell->exec = mshell->exec->next;
	}
	mshell->exit_status = WEXITSTATUS(status);
	if (glo_exit == 131)
		mshell->exit_status = glo_exit;
	if (glo_exit == 130)
	{
		// write(1, "\n", 1);
		// rl_replace_line("", 0);
		// rl_on_new_line();
		// rl_redisplay();
		mshell->exit_status = glo_exit;
	}
	// printf("WEXITSTATUS = %d\n", WEXITSTATUS(status));
	return (1);
}

int	start_cmd_pipeline(t_mshell *mshell)
{
	mshell->built->builtin_p = 42;
	popen_tube(mshell);
	mshell->exec->pid = fork();
	if (mshell->exec->pid == -1)
		return (dprintf(2, "\tfork: child failure\n"));
	return (1);
}

int	controler(t_mshell *mshell)
{
	pclose_tube(mshell);
	close_file_fd(mshell);
	if (!mshell->exec->next)
		return (0);
	return (1);
}

int	close_heredocs(t_mshell *mshell)
{
	t_heredoc	*head;

	head = mshell->hd_heredoc;
	while (mshell->heredoc)
	{
		if (mshell->heredoc->pipe_heredoc[0] != -42)
			close(mshell->heredoc->pipe_heredoc[0]);
		if (mshell->heredoc->pipe_heredoc[1] != -42)
			close(mshell->heredoc->pipe_heredoc[1]);
		mshell->heredoc = mshell->heredoc->next;
	}
	mshell->heredoc = head;
	return (1);
}

int	heredoc_controler(t_mshell *mshell)
{
	if (mshell->heredoc->pipe_heredoc[0] != -42)
		close(mshell->heredoc->pipe_heredoc[0]);
	return (1);
}
