/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 17:00:00 by oboutarf          #+#    #+#             */
/*   Updated: 2023/02/02 11:23:58 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	new_command_line(t_mshell *mshell)
{
	if (mshell->built)
		free_built(mshell);
	if (mshell->expd)
		free_expd(mshell);
	if (mshell->execve)
		free_execve(mshell);
	if (mshell->exec)
		free_exec(mshell);
	free(mshell->rdline_outp);
	return (1);
}

int	init_process_utils(t_mshell *mshell)
{
	if (!init_built(mshell))
		return (0);
	if (!init_expansion(mshell))
		return (0);
	if (!init_execve(mshell))
		return (0);
	return (1);
}

int	main(int ac, char **av, char **env)
{
	t_mshell		*mshell;

	(void)ac;
	(void)av;
	mshell = NULL;
	manage_signals();
	mshell = init_mshell(env);
	if (!mshell)
		return (write(2, "couldn't init struct, process aborted\n", 39), 1);
	while (1)
	{
		init_process_utils(mshell);
		mshell->rdline_outp = readline("dkermarf@e42r42p42:~/42/minishell$ ");
		if (!check_eof(mshell->rdline_outp))
			return (write(2, "exit\n", 5), terminate(mshell), 0);
		add_history(mshell->rdline_outp);
		if (!init_t_token(mshell))
			return (0);
		if (ft_strlen(mshell->rdline_outp))
			if (!compose_and_launch_command(mshell, env))
				dprintf(2, "minishell: launch cmd error'\n");
		new_command_line(mshell);
	}
	return (0);
}
