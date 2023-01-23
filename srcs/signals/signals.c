/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oscobou <oscobou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 17:58:33 by oboutarf          #+#    #+#             */
/*   Updated: 2023/01/23 14:00:01 by oscobou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_eof(char *rdline_outp)
{
	if (rdline_outp == NULL)
		return (0);
	return (1);
}

void	handle_sigint(void)
{
	// write(1, "\n", 1);
	// rl_replace_line("", 0);
	// rl_on_new_line();
	// rl_redisplay();
}

void	sig_handler(int signum)
{
	if (signum == SIGINT)
		handle_sigint();
}

void	manage_signals(void)
{
	signal(SIGINT, &sig_handler);
	signal(SIGQUIT, SIG_IGN);
}
