/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_signals.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 08:14:15 by oboutarf          #+#    #+#             */
/*   Updated: 2023/02/10 08:27:53 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sigint_hd(void)
{
	g_exit = -42;
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
