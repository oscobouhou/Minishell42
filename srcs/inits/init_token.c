/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 19:09:16 by oboutarf          #+#    #+#             */
/*   Updated: 2023/01/25 12:50:39 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_t_token(t_mshell *mshell)
{
	mshell->tkn = malloc(sizeof(t_tkn));
	if (!mshell->tkn)
		return (0);
	mshell->tkn->type = -1;
	mshell->tkn->tkn = NULL;
	mshell->tkn->next = NULL;
	mshell->head_tkn = mshell->tkn;
	return (1);
}
