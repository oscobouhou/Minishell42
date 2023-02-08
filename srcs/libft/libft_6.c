/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_6.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 11:20:18 by oboutarf          #+#    #+#             */
/*   Updated: 2023/02/08 11:22:03 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

int	set_pos_to_cmd(t_mshell *mshell)
{
	if (mshell->exec->start_exec->type != -1)
	{
		while (mshell->exec->start_exec && \
		mshell->exec->start_exec->type != _CMD)
		{
			if (!mshell->exec->start_exec->next)
				return (mshell->exec->no_cmd = 42, \
				mshell->exec->start_exec = mshell->exec->start_exec_head, 0);
			mshell->exec->start_exec = mshell->exec->start_exec->next;
		}
	}
	return (1);
}

void	ft_putstr(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		ft_putchar(str[i]);
}
