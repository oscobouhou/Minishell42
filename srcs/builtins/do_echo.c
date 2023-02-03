/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 20:51:06 by oboutarf          #+#    #+#             */
/*   Updated: 2023/02/03 13:52:33 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_echo_args(t_mshell *mshell)
{
	int	i;

	i = 0;
	mshell->exec->start_exec = mshell->exec->start_exec_head;
	while (mshell->exec->start_exec)
	{
		if (mshell->exec->start_exec->type == _ARG)
			i++;
		mshell->exec->start_exec = mshell->exec->start_exec->next;
	}
	mshell->exec->start_exec = mshell->exec->start_exec_head;
	return (i);
}

int	copy_echo_arg(t_mshell *mshell, int *c)
{
	int	i;

	i = 0;
	while (mshell->exec->start_exec->tkn[i])
		i++;
	mshell->built->echo_arg[*c] = malloc(sizeof(char) * (i + 1));
	if (!mshell->built->echo_arg[*c])
		return (0);
	i = 0;
	while (mshell->exec->start_exec->tkn[i])
	{
		mshell->built->echo_arg[*c][i] = mshell->exec->start_exec->tkn[i];
		i++;
	}
	mshell->built->echo_arg[*c][i] = '\0';
	(*c)++;
	return (1);
}

int	verif_flags(t_mshell *mshell, int *flag)
{
	int	i;

	i = 1;
	if (!*flag)
		return (1);
	if (mshell->exec->start_exec->tkn[0] != '-')
		return (*flag = 0, 1);
	if (mshell->exec->start_exec->tkn[0] == '-'
		&& !mshell->exec->start_exec->tkn[1])
		return (*flag = 0, 1);
	while (mshell->exec->start_exec->tkn[i])
	{
		if (mshell->exec->start_exec->tkn[i] != 'n')
			return (*flag = 0, 1);
		i++;
	}
	return (mshell->built->echo_flag = 0, 1);
}

int	print_echo_args(t_mshell *mshell)
{
	int	i;

	i = 1;
	if (ft_strlen(mshell->built->echo_arg[0]) > 0)
	{
		ft_putstr(mshell->built->echo_arg[0]);
		free(mshell->built->echo_arg[0]);
	}
	if (mshell->built->echo_arg[0 + 1])
	{
		while (mshell->built->echo_arg[i])
		{
			ft_putchar(' ');
			ft_putstr(mshell->built->echo_arg[i]);
			if (mshell->built->echo_arg[i])
				free(mshell->built->echo_arg[i]);
			i++;
		}
		free(mshell->built->echo_arg);
		mshell->built->echo_arg = NULL;
		if (mshell->built->echo_flag == -42)
			ft_putchar('\n');
	}
	return (1);
}

int	scan_echo_args(t_mshell *mshell)
{
	int	prev_flag;
	int	c;

	c = 0;
	prev_flag = 1;
	while (mshell->exec->start_exec)
	{
		if (mshell->exec->start_exec->type == _ARG)
		{
			if (verif_flags(mshell, &prev_flag) && !prev_flag)
				copy_echo_arg(mshell, &c);
			else
			{
				mshell->built->echo_arg[c] = "";
				c++;
			}
		}
		mshell->exec->start_exec = mshell->exec->start_exec->next;
	}
	mshell->exec->start_exec = mshell->exec->start_exec_head;
	return (1);
}

void	builtin_fork_exit(t_mshell *mshell)
{
	if (mshell->built->builtin_p == 42)
	{
		exit(0);
	}
}

int	do_echo(t_mshell *mshell)
{
	int	backup[2];
	int	i;

	backup[0] = -42;
	backup[1] = -42;
	if (mshell->built->builtin_p == -42)
	{
		dprintf(2, "%d --- %d\n", backup[0], backup[1]);
		bckup_stdin_out(backup);
		dprintf(2, "%d --- %d\n", backup[0], backup[1]);
		enable_redirections(mshell);
	}
	i = count_echo_args(mshell);
	if (!i)
		return (dprintf(2, "\n"), 1);
	mshell->built->echo_arg = malloc(sizeof(char *) * (i + 1));
	if (!mshell->built->echo_arg)
		return (0);
	mshell->built->echo_arg[i] = NULL;
	scan_echo_args(mshell);
	print_echo_args(mshell);
	builtin_fork_exit(mshell);
	exit_builtin(mshell, backup);
	mshell->exit_status = 0;
	return (1);
}
