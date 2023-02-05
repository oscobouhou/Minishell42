/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 19:09:16 by oboutarf          #+#    #+#             */
/*   Updated: 2023/02/05 07:44:30 by oboutarf         ###   ########.fr       */
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
	mshell->tkn->pipe_fd_hrdoc[0] = -42;
	mshell->tkn->pipe_fd_hrdoc[1] = -42;
	mshell->tkn->next = NULL;
	mshell->head_tkn = mshell->tkn;
	return (1);
}
