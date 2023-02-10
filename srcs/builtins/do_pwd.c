/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 20:51:14 by oboutarf          #+#    #+#             */
/*   Updated: 2023/02/10 13:48:30 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	do_pwd(t_mshell *mshell)
{
	char	path[1024];

	if (!getcwd(path, 1024))
	{
		g_exit = 1;
		return (0);
	}
	ft_putstr(path);
	ft_putchar('\n');
	g_exit = 0;
	(void)mshell;
	return (1);
}
