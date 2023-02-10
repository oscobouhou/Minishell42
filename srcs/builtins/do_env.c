/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 20:51:08 by oboutarf          #+#    #+#             */
/*   Updated: 2023/02/10 13:46:08 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env(t_mshell *mshell)
{
	t_env	*env;

	env = mshell->env;
	while (env)
	{
		ft_putstr(env->envar);
		ft_putchar('=');
		if (env->value)
		{
			ft_putstr(env->value);
		}
		ft_putchar('\n');
		env = env->next;
	}
}

int	do_env(t_mshell *mshell)
{
	int		backup[2];

	backup[0] = -42;
	backup[1] = -42;
	if (mshell->built->builtin_p == -42)
	{
		bckup_stdin_out(backup);
		enable_redirections(mshell);
	}
	print_env(mshell);
	if (mshell->exec->no_redirs != -42)
		close_file_fd(mshell);
	if (mshell->built->builtin_p == 42)
	{
		if (mshell->exec->next)
			close_pipe_fds(mshell);
		terminate(mshell);
		exit(0);
	}
	re_establish_stdin_out(backup);
	g_exit = 0;
	return (1);
}
