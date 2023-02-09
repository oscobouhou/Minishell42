/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 20:51:10 by oboutarf          #+#    #+#             */
/*   Updated: 2023/02/09 18:00:53 by oboutarf         ###   ########.fr       */
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

int	exit_numeric_char(t_mshell *mshell)
{
	int	i;

	i = 0;
	while (mshell->exec->start_exec->next
		&& mshell->exec->start_exec->type != _ARG)
		mshell->exec->start_exec = mshell->exec->start_exec->next;
	while (mshell->exec->start_exec->tkn[i])
	{
		if (!(mshell->exec->start_exec->tkn[i] >= '0'
				&& mshell->exec->start_exec->tkn[i] <= '9'))
			return (0);
		i++;
	}
	mshell->exec->start_exec = mshell->exec->start_exec_head;
	return (1);
}

int	do_exit_too_many_arg(t_mshell *mshell)
{
	mshell->exec->start_exec = mshell->exec->start_exec_head;
	dprintf(2, "exit\nminishell: exit: too many arguments\n");
	if (mshell->built->builtin_p == 42)
	{
		terminate(mshell);
		exit(1);
	}
	mshell->exit_status = 1;
	return (1);
}

int	do_exit_numeric_error(t_mshell *mshell)
{
	mshell->exec->start_exec = mshell->exec->start_exec_head;
	dprintf(2, "exit\nminishell: exit: numeric argument required\n");
	if (mshell->built->builtin_p == 42)
	{
		terminate(mshell);
		exit(2);
	}
	mshell->exit_status = 2;
	return (1);
}

int	do_exit(t_mshell *mshell)
{
	int	arg;

	arg = count_number_args_exit(mshell);
	if (!arg)
	{
		dprintf(2, "exit\n");
		terminate(mshell);
		exit(0);
	}
	if (!exit_numeric_char(mshell))
		do_exit_numeric_error(mshell);
	if (arg > 1)
		do_exit_too_many_arg(mshell);
	while (mshell->exec->start_exec->type != _ARG)
		mshell->exec->start_exec = mshell->exec->start_exec->next;
	dprintf(2, "exit\n");
	arg = (ft_atoi(mshell->exec->start_exec->tkn) % 256);
	if (arg < 0)
		arg = 256 + arg;
	mshell->exit_status = arg;
	terminate(mshell);
	exit(arg);
	return (1);
}
