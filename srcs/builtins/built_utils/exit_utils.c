/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 14:07:42 by oboutarf          #+#    #+#             */
/*   Updated: 2023/02/10 14:18:57 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	ft_putstr_fd(2, "exit\nminishell: exit: too many arguments\n");
	if (mshell->built->builtin_p == 42)
	{
		terminate(mshell);
		exit(1);
	}
	g_exit = 1;
	return (1);
}

int	do_exit_numeric_error(t_mshell *mshell)
{
	mshell->exec->start_exec = mshell->exec->start_exec_head;
	ft_putstr_fd(2, "exit\nminishell: exit: numeric argument required\n");
	terminate(mshell);
	exit(2);
	return (1);
}

int	exit_types(t_mshell *mshell, int arg)
{
	if (!exit_numeric_char(mshell))
	{
		do_exit_numeric_error(mshell);
		return (1);
	}
	if (arg > 1)
	{
		do_exit_too_many_arg(mshell);
		return (1);
	}
	return (0);
}
