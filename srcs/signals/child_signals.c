/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_signals.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 11:34:33 by oboutarf          #+#    #+#             */
/*   Updated: 2023/02/08 11:36:57 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sigquit(void)
{
	dprintf(2, "Quit (core dumped)\n");
}

void	sig_fork_handler(int signum)
{
	if (signum == SIGINT)
	{
		handle_sigint();
	}
	if (signum == SIGQUIT)
	{
		handle_sigquit();
	}
}