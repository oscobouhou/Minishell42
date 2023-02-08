/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_review.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 14:00:19 by oboutarf          #+#    #+#             */
/*   Updated: 2023/02/08 15:39:55 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	review_nxt_after_pipe(t_mshell *mshell, int *cmd_cnt)
{
	*cmd_cnt = 0;
	make_new_heredoc(mshell);
	if (mshell->tkn->next->type == WORD)
	{
		*cmd_cnt += 1;
		mshell->tkn->next->type = _CMD;
	}
	return (1);
}

int	pipe_review(t_mshell *mshell, int *cmd_cnt)
{
	if (mshell->tkn->type == PIPE)
	{
		if (mshell->tkn->next->tkn == NULL)
			return (syntax_error(NULL), 0);
		if (mshell->tkn == mshell->head_tkn)
			return (syntax_error(mshell->tkn->tkn), 0);
		if (mshell->tkn->next->type == PIPE)
			return (syntax_error(mshell->tkn->tkn), 0);
		if (mshell->tkn->next->type == RDIR_L \
		|| mshell->tkn->next->type == RDIR_R \
		|| mshell->tkn->next->type == APPEND)
		{
			mshell->tkn = mshell->tkn->next;
			if (!type_next_token(mshell->tkn, _FILE))
				return (0);
			mshell->tkn = mshell->tkn->next;
		}
		review_nxt_after_pipe(mshell, cmd_cnt);
	}
	return (1);
}
