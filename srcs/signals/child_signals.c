/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_signals.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 11:34:33 by oboutarf          #+#    #+#             */
/*   Updated: 2023/02/10 14:32:20 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sigint_fork(void)
{
	write(1, "\n", 1);
	g_exit = 130;
}

void	handle_sigquit(void)
{
	ft_putstr_fd(2, "Quit (core dumped)\n");
	g_exit = 131;
}

void	retrieve_signals(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &sig_handler);
}

void	sig_fork_handler(int signum)
{
	if (signum == SIGINT)
	{
		handle_sigint_fork();
	}
	if (signum == SIGQUIT)
	{
		handle_sigquit();
	}
}
