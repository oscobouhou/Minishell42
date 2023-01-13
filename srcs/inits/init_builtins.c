/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 20:07:10 by oboutarf          #+#    #+#             */
/*   Updated: 2023/01/13 20:48:09 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_builtins(t_mshell *mshell)
{
	mshell->built[CD] = do_cd;
	mshell->built[PWD] = do_pwd;
	mshell->built[ENV] = do_env;
	mshell->built[ECHO] = do_echo;
	mshell->built[EXIT] = do_exit;
	mshell->built[UNSET] = do_unset;
	mshell->built[EXPORT] = do_export;
	return (1);
}