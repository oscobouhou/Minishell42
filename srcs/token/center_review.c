/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   center_review.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 13:16:37 by oboutarf          #+#    #+#             */
/*   Updated: 2023/02/02 23:38:58 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	type_next_token(t_tkn *tkn, int type)
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

int	center_review(t_mshell *mshell)
{
	int		cmd_cnt;
	t_tkn 	*tmp;

	tmp = NULL;
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
		tmp = mshell->tkn;
		mshell->tkn = mshell->tkn->next;
		if (!mshell->tkn->next)
		{
			free(mshell->tkn);
			mshell->tkn = NULL;
			tmp->next = NULL;
			break;
		}
	}
	mshell->tkn = mshell->head_tkn;
	return (1);
}
