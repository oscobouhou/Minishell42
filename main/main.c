/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 17:00:00 by oboutarf          #+#    #+#             */
/*   Updated: 2023/01/09 23:05:36 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	char			*rdline_outp;
	t_mshell		*mshell;

	(void)ac;
	(void)av;
	mshell = NULL;
	manage_signals();
	mshell = init_struct(env);
	if (!mshell)
		return (write(1, "Couldn't init struct, process aborted\n", 39), 1);
	while (1)
	{
		rdline_outp = readline("dkermarf@e42r42p42:~/42/minishell$ ");
		if (!check_eof(rdline_outp))
			return (write(1, "exit\n", 5), terminate(mshell), 0);
		add_history(rdline_outp);
		parse_rdline_outp(rdline_outp);
		free(rdline_outp);
	}
	(void)env;
	return (0);
}
