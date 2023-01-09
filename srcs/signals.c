/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 17:58:33 by oboutarf          #+#    #+#             */
/*   Updated: 2023/01/09 19:34:36 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_eof(char *rdline_outp)
{
	if (rdline_outp == NULL)
		return (0);
	return (1);
}

void    handle_sigint()
{
    write(1, "\n", 1);
    rl_replace_line("", 0);
    rl_on_new_line();
    rl_redisplay();
}

void	sig_handler(int signum)
{
	if (signum == SIGINT)
	{
		handle_sigint();
	}
}
// write(1, (char *)'\n', 1);

void	manage_signals(void)
{
	signal(SIGINT, &sig_handler);
	signal(SIGQUIT, SIG_IGN);
}