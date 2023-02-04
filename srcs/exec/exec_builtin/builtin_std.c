/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_std.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 19:07:41 by oboutarf          #+#    #+#             */
/*   Updated: 2023/02/04 13:03:22 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	re_establish_stdin_out(int *backup)
{
	dup2(backup[0], STDIN_FILENO);
	dup2(backup[1], STDOUT_FILENO);
	close(backup[0]);
	close(backup[1]);
	return (1);
}

int	bckup_stdin_out(int *backup)
{
	backup[0] = dup(STDIN_FILENO);
	backup[1] = dup(STDOUT_FILENO);
	return (1);
}

int	exit_builtin(t_mshell *mshell, int *backup)
{
	close_file_fd(mshell);
	re_establish_stdin_out(backup);
	return (1);
}
