/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   review_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 13:16:37 by oboutarf          #+#    #+#             */
/*   Updated: 2023/01/16 20:33:08 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int review_tokens(t_mshell *mshell)
{
    (void)mshell;
    return (1);
}

/*
    if (mshell->tkn->type == WORD)
		assign_command_args(mshell);
	if (mshell->tkn->type == REDIR || mshell->tkn->type == APPEND)
	{
		if (mshell->tkn->next == NULL)
			syntax_error
		else if (mshell->tkn->next == REDIR)
			syntax_error
		else if (mshell->tkn->next->type == HRDOC || mshell->tkn->next->type == APPEND)
			syntax error
		else if (mshell->tkn->next->type == PIPE)
			syntax_error
		else if (mshell->tkn->next->type == WORD)
		{
			mshell->tkn = mshell->tkn->next
			mshell->tkn->type = FILE
		}
	}
	if (mshell->tkn->type == HRDOC)
	{
		if (mshell->tkn->next == NULL)
			syntax_error
		else if (mshell->tkn->next->type == WORD)
		{
			mshell->tkn = mshell->tkn->next;
			mshell->tkn->type = DLIM_HRDOC;
		}
	}
    if (mshell->tkn->type == PIPE)
	{
		if (mshell->tkn == mshell->head_tkn)
			syntax_error
		else if (mshell->tkn->next->type == PIPE)
			syntax_error
	}
	mshell->tkn = mshell->tkn->next
	
*/

/*

FUNCS: 
assign_command_args(mshell)-> while (mshell->tkn->type == WORD)

*/