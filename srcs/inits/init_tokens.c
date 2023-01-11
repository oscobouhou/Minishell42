/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 15:00:31 by oboutarf          #+#    #+#             */
/*   Updated: 2023/01/10 16:37:34 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tkn    *init_tokens(t_mshell *mshell)
{
    t_tkn   *tkn;

    tkn = malloc(sizeof(t_tkn));
    if (!tkn)
        return (NULL);
    tkn->tkn = NULL;
    return (tkn);
    (void)mshell;
}