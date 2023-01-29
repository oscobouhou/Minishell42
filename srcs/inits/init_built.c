/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_built.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 20:43:51 by oboutarf          #+#    #+#             */
/*   Updated: 2023/01/29 22:34:04 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int init_built(t_mshell *mshell)
{
    mshell->built = malloc(sizeof(t_built));
    if (!mshell->built)
        return (0);
    mshell->built->cd_arg = NULL;
    mshell->built->cd_chdir = NULL;
    return (1);
}
