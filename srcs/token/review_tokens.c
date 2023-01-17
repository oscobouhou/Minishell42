/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   review_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 13:16:37 by oboutarf          #+#    #+#             */
/*   Updated: 2023/01/17 13:01:23 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void syntax_error(void)
{
	dprintf(2, "errpr\n");
}

int type_next_token(t_tkn *tkn, int type) // old assign_command_args(t_mshell *mshell);
{
	if (tkn->tkn == NULL)
		return (0);
	else if (tkn->next->type == WORD)
	{
		tkn = tkn->next;
		tkn->type = type;
		return (1);
	}
	return (0);
}

int review_tokens(t_mshell *mshell)
{
	mshell->tkn = mshell->head_tkn;
	while (mshell->tkn)
	{
// ================================================================== //
	    if (mshell->tkn->type == WORD)
		{
			if (mshell->tkn == mshell->head_tkn)
				mshell->tkn->type = _CMD;
			else
				mshell->tkn->type = _ARG;
		}
// ================================================================== //
		
		if (mshell->tkn->type == RDIR_L \
		|| mshell->tkn->type == RDIR_R \
		|| mshell->tkn->type == APPEND)
			if (!type_next_token(mshell->tkn, _FILE))
				return (syntax_error(), 0);
// ================================================================== //
		if (mshell->tkn->type == HRDOC)
			if (!type_next_token(mshell->tkn, DLIM_HRDOC))
				return (syntax_error(), 0);
// ================================================================== //
		if (mshell->tkn->type == PIPE)
		{
			dprintf(2, "%d\n", mshell->tkn->type);
			if (mshell->tkn->next->tkn == NULL)
				return (syntax_error(), 0);
			if (mshell->tkn == mshell->head_tkn)
				return (syntax_error(), 0);
			if (mshell->tkn->next->type == RDIR_L \
			|| mshell->tkn->next->type == RDIR_R \
			|| mshell->tkn->next->type == APPEND)
			{
				mshell->tkn = mshell->tkn->next;
				if (!type_next_token(mshell->tkn, _FILE))
					return (syntax_error(), 0);
				mshell->tkn = mshell->tkn->next;
			}
			if (mshell->tkn->next->type == WORD)
				mshell->tkn->next->type = _CMD;
			printf("\nputeputepipe\n");
		}
// ================================================================== //
		mshell->tkn = mshell->tkn->next;
	}
	mshell->tkn = mshell->head_tkn;
	return (1);
// ========================== END_FUNC ============================== //
}

/*
REDIR	FILE	%WORD	WORD		PIPE	WORD		WORD
<		lol		cat		salut		|		echo		"oohyeah$ARG"man


    mshell->tkn = mshell->head_tkn;
while (mshell->tkn->next)
{
    if (mshell->tkn->type == WORD)
		assign_command_args(mshell);

	if (mshell->tkn->type == REDIR_L || mshell->tkn->type == REDIR_R  || mshell->tkn->type == APPEND)
	{
		if (mshell->tkn->next == NULL)
			return (syntax_error(), 0);
		else if (mshell->tkn->next->type == mshell->tkn->type)
			return (syntax_error(), 0);
		else if (mshell->tkn->next->type == HRDOC || mshell->tkn->next->type == APPEND)
			return (syntax_error(), 0);
		else if (mshell->tkn->next->type == PIPE)
			return (syntax_error(), 0);
		else if (mshell->tkn->next->type == WORD)
		{
			mshell->tkn = mshell->tkn->next;
			mshell->tkn->type = _FILE;
			if (mshell->tkn->next == NULL)
				return (1);
			mshell->tkn = mshell->tkn->next;
		}
	}

	if (mshell->tkn->type == HRDOC)
	{
		if (mshell->tkn->next == NULL)
			return (syntax_error(), 0);
		else if (mshell->tkn->next->type == WORD)
		{
			mshell->tkn = mshell->tkn->next;
			mshell->tkn->type = DLIM_HRDOC;
			if (mshell->tkn->next == NULL)
				return (1);
			mshell->tkn = mshell->tkn->next;
		}
		else
			return (syntax_error(), 0);
	}

    if (mshell->tkn->type == PIPE)
	{
		if (mshell->tkn->next == NULL)
			return (syntax_error(), 0);
		if (mshell->tkn == mshell->head_tkn)
			return (syntax_error(), 0);
		else if (mshell->tkn->next->type == PIPE)
			return (syntax_error(), 0);
		else if (mshell->tkn->next->type == WORD)
		{
			mshell->tkn = mshell->tkn->next;
			mshell->tkn->type = _CMD;
			if (mshell->tkn->next == NULL)
				return (1);
			mshell->tkn = mshell->tkn->next;
		}
		else
			return (syntax_error(), 0);
	}
	mshell->tkn = mshell->tkn->next;
}




*/

/*

FUNCS: 
assign_command_args(mshell)-> while (mshell->tkn->type == WORD)

*/