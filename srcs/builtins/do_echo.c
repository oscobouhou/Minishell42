/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 20:51:06 by oboutarf          #+#    #+#             */
/*   Updated: 2023/02/08 11:23:30 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo_printer(char *to_print, t_mshell *mshell)
{
	if (write(mshell->exec->fd_out, to_print, ft_strlen(to_print)) == -1)
	{
		write(2, WRITE_ERR, 60);
		return (0);
	}
	return (1);
}

int	print_echo_args(t_mshell *mshell)
{
	int	i;

	i = 0;
	while (mshell->built->echo_args_len-- > 0)
	{
		if (mshell->built->echo_arg[i])
		{
			if (!echo_printer(mshell->built->echo_arg[i], mshell))
				return (0);
			if (mshell->built->echo_arg[i + 1])
				ft_putchar(' ');
			free(mshell->built->echo_arg[i]);
		}
		i++;
	}
	free(mshell->built->echo_arg);
	mshell->built->echo_arg = NULL;
	if (mshell->built->echo_flag == -42)
		ft_putchar('\n');
	return (1);
}

int	do_echo(t_mshell *mshell)
{
	int	backup[2];
	int	i;

	unforked_builtin_redir_treat(mshell, backup);
	i = count_echo_args(mshell);
	if (!i)
	{
		write(mshell->exec->fd_out, "\n", 1);
		exit_builtin(mshell, backup, 0);
		return (1);
	}
	mshell->built->echo_arg = malloc(sizeof(char *) * (i + 1));
	if (!mshell->built->echo_arg)
		return (0);
	mshell->built->echo_arg[i] = NULL;
	scan_echo_args(mshell);
	close_file_fd(mshell);
	if (!print_echo_args(mshell))
		return (exit_builtin(mshell, backup, 1));
	exit_builtin(mshell, backup, 0);
	return (1);
}
