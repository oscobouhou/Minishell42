/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 20:51:08 by oboutarf          #+#    #+#             */
/*   Updated: 2023/02/02 01:24:21 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env(t_mshell *mshell)
{
	t_env	*env;

	env = mshell->env;
	while(env)
	{
		ft_putstr(env->envar);
		ft_putchar('=');
        if (env->value)
    		{ft_putstr(env->value);}
		ft_putchar('\n');
		env = env->next;
	}
}

int do_env(t_mshell *mshell)
{
    print_env(mshell);
    return (1);
}
