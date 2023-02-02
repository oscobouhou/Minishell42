/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 15:36:30 by oboutarf          #+#    #+#             */
/*   Updated: 2023/02/01 19:09:22 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int scan_builtin(t_mshell *mshell)
{
    if (mshell->exec->start_exec->type == -1)
        return (0);
    if (!set_pos_to_cmd(mshell))
        return (0);
    if (mshell->exec->next)
        return (0);
    if (!ft_strcmp(mshell->exec->start_exec->tkn, "cd"))
        return (do_cd(mshell), 1);
    else if (!ft_strcmp(mshell->exec->start_exec->tkn, "echo"))
        return (do_echo(mshell), 1);
    else if (!ft_strcmp(mshell->exec->start_exec->tkn, "exit"))
        return (do_exit(mshell), 1);
    else if (!ft_strcmp(mshell->exec->start_exec->tkn, "unset"))
        return (do_unset(mshell), 1);
    else if (!ft_strcmp(mshell->exec->start_exec->tkn, "export"))
        return (do_exprt(mshell), 1);
    else if (!ft_strcmp(mshell->exec->start_exec->tkn, "env"))
        return (do_env(mshell), 1);
    else if (!ft_strcmp(mshell->exec->start_exec->tkn, "pwd"))
        return (do_pwd(mshell), 1);
    return (0);
}
