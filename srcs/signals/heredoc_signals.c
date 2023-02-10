/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_signals.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 08:14:15 by oboutarf          #+#    #+#             */
/*   Updated: 2023/02/10 15:57:13 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	sigint_exit(t_mshell *mshell)
{
	if (g_exit == -42)
	{
		return (g_exit = 130, 1);
	}
	(void)mshell;
	return (0);
}

void	handle_sigint_hd(void)
{
	g_exit = -42;
	close(0);
}

void	sig_heredoc_handler(int signum)
{
	if (signum == SIGINT)
	{
		handle_sigint_hd();
	}
}

void	stop_signals_heredoc(void)
{
	signal(SIGINT, &sig_heredoc_handler);
	signal(SIGQUIT, SIG_IGN);
}
