/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 20:51:10 by oboutarf          #+#    #+#             */
/*   Updated: 2023/02/10 14:08:05 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_number_args_exit(t_mshell *mshell)
{
	int	arg;

	arg = 0;
	mshell->exec->start_exec = mshell->exec->start_exec_head;
	while (mshell->exec->start_exec)
	{
		if (mshell->exec->start_exec->type == _ARG)
			arg++;
		if (!mshell->exec->start_exec->next)
			break ;
		mshell->exec->start_exec = mshell->exec->start_exec->next;
	}
	mshell->exec->start_exec = mshell->exec->start_exec_head;
	return (arg);
}

int	do_exit(t_mshell *mshell)
{
	int	arg;

	arg = count_number_args_exit(mshell);
	if (!arg)
	{
		ft_putstr_fd(2, "exit\n");
		terminate(mshell);
		exit(0);
	}
	if (exit_types(mshell, arg))
		return (1);
	while (mshell->exec->start_exec->type != _ARG)
		mshell->exec->start_exec = mshell->exec->start_exec->next;
	arg = (ft_atoi(mshell->exec->start_exec->tkn) % 256);
	ft_putstr_fd(2, "exit\n");
	if (arg < 0)
		arg = 256 + arg;
	g_exit = arg;
	terminate(mshell);
	exit(arg);
	return (1);
}
