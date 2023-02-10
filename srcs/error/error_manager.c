/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 16:18:22 by oboutarf          #+#    #+#             */
/*   Updated: 2023/02/10 14:27:18 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	error_manager(char *process, char *tkn, char *error)
{
	ft_putstr("minishell: ");
	ft_putstr(process);
	if (tkn)
	{
		ft_putstr(": `");
		ft_putstr(tkn);
		ft_putstr("': ");
	}
	else
		ft_putstr(": ");
	ft_putstr(error);
	ft_putchar('\n');
	return (1);
}

void	cmd_err_message(char *cmd)
{
	if (!ft_strlen(cmd))
		ft_putstr_fd(2, "minishell: : command not found\n");
	else
	{
		ft_putstr_fd(2, "minishell: ");
		ft_putstr_fd(2, cmd);
		ft_putstr_fd(2, ": command not found\n");
	}
}

int	open_error(t_mshell *mshell)
{
	ft_putstr_fd(2, "minishell: ");
	ft_putstr_fd(2, mshell->exec->start_exec->next->tkn);
	ft_putstr_fd(2, ": ");
	ft_putstr_fd(2, strerror(errno));
	ft_putstr_fd(2, "\n");
	return (1);
}
