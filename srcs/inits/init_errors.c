/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 16:33:10 by oboutarf          #+#    #+#             */
/*   Updated: 2023/01/15 16:39:54 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int init_t_err(t_mshell *mshell)
{
    mshell->error = malloc(sizeof(t_err));
    if (!mshell->error)
        return (0);
    return (1);
    
}