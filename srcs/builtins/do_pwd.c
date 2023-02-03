/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 20:51:14 by oboutarf          #+#    #+#             */
/*   Updated: 2023/02/03 06:05:44 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	do_pwd(t_mshell *mshell)
{
	char	path[1024];

	if (!getcwd(path, 1024))
	{
		mshell->exit_status = 1;
		return (0);
	}
	ft_putstr(path);
	ft_putchar('\n');
	mshell->exit_status = 0;
	return (1);
}
