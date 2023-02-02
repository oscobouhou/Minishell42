/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_execve.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 13:59:17 by oboutarf          #+#    #+#             */
/*   Updated: 2023/02/02 16:17:34 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_execve(t_mshell *mshell, char **env)
{
	mshell->execve = malloc(sizeof(t_execve));
	if (!mshell->execve)
		return (0);
	mshell->execve->cmd = NULL;
	mshell->execve->cmd_args = NULL;
	mshell->execve->paths = NULL;
	if (!*env)
		return (1);
	parse_paths(mshell);
	return (1);
}
