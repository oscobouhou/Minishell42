/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compose_tkn.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 15:32:02 by oboutarf          #+#    #+#             */
/*   Updated: 2023/01/17 19:15:39 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
void what_token(int token)
{
	if (token == WORD)
		dprintf(2, "WORD");
	if (token == PIPE)
		dprintf(2, "PIPE");
	if (token == SQ_WORD)
		dprintf(2, "SQ_WORD");
	if (token == DQ_WORD)
		dprintf(2, "DQ_WORD");
	if (token == RDIR_R)
		dprintf(2, "RDIR_R");
	if (token == RDIR_L)
		dprintf(2, "RDIR_L");
	if (token == BUILTIN)
		dprintf(2, "BUILTIN");
	if (token == APPEND)
		dprintf(2, "APPEND");
	if (token == HRDOC)
		dprintf(2, "HRDOC");
	if (token == DLIM_HRDOC)
		dprintf(2, "DLIM_HRDOC");
	if (token == _FILE)
		dprintf(2, "_FILE");
	if (token == _CMD)
		dprintf(2, "_CMD");
	if (token == _ARG)
		dprintf(2, "_ARG");
}

void	print_tokens(t_mshell *mshell)
{
	mshell->tkn = mshell->head_tkn;
	while (mshell->tkn)
	{
		dprintf(2, "content: %s			---			type: ", mshell->tkn->tkn);
		what_token(mshell->tkn->type);
		dprintf(2, "\n");
		mshell->tkn = mshell->tkn->next;
	}
	dprintf(2, "=======================================\n");
	mshell->tkn = mshell->head_tkn;
}

int	compose_tkn(t_mshell *mshell)
{
	mshell->tkn = mshell->head_tkn;
	if (!review_tokens(mshell))
		return (0);
	if (!center_expand(mshell))
		return (0);
	print_tokens(mshell);
	return (1);
}
