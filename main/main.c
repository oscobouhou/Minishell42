/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 17:00:00 by oboutarf          #+#    #+#             */
/*   Updated: 2023/01/21 23:33:24 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



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
		mshell->rdline_outp = readline("dkermarf@e42r42p42:~/42/minishell$ ");
		if (!check_eof(mshell->rdline_outp))
			return (write(2, "exit\n", 5), terminate(mshell), 0);
		add_history(mshell->rdline_outp);
		if (!init_t_token(mshell))
			return (0);
		parse_output(mshell);
		compose_tkn(mshell);
		center_exec(mshell);
		free(mshell->rdline_outp);
		// free_tokens(mshell);
	}
	return (0);
}
