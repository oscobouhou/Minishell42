/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   center_review.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 13:16:37 by oboutarf          #+#    #+#             */
/*   Updated: 2023/01/27 17:05:40 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int type_next_token(t_tkn *tkn, int type)
{
	if (tkn->tkn == NULL)
		return (syntax_error(), 0);
	else if (tkn->next->type == WORD)
	{
		tkn = tkn->next;
		tkn->type = type;
		return (1);
	}
	return (syntax_error(), 0);
}

int center_review(t_mshell *mshell)
{
	int	cmd_cnt;

	cmd_cnt = 0;
	mshell->tkn = mshell->head_tkn;
	while (mshell->tkn->next)
	{
		word_review(mshell, &cmd_cnt);
		if (!redirs_review(mshell))
			return (0);
		if (!hrdoc_review(mshell, &cmd_cnt))
			return (0);
		if (!pipe_review(mshell, &cmd_cnt))
			return (0);
		mshell->tkn = mshell->tkn->next;
		if (!mshell->tkn->next)
			mshell->tkn->type = -1;
	}
	mshell->tkn = mshell->head_tkn;
	return (1);
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