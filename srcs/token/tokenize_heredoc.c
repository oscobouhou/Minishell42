/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 12:24:43 by oboutarf          #+#    #+#             */
/*   Updated: 2023/01/16 13:12:18 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int join_redirs(t_mshell *mshell)
{
	free(mshell->tkn->next);
	mshell->tkn->next = mshell->tkn->next->next;
	if (mshell->tkn->type == RDIR_R)
		mshell->tkn->type = HEREDOC_R;
	else
		mshell->tkn->type = HEREDOC_L;
	return (1);
}

int tokenize_heredoc(t_mshell *mshell)
{
	while (mshell->tkn->next)
	{
		if (mshell->tkn->type == RDIR_R || mshell->tkn->type == RDIR_L)
			if (mshell->tkn->type == mshell->tkn->next->type)
				if (!join_redirs(mshell))
					return (0);
		mshell->tkn = mshell->tkn->next;
	}
	return (1);
}
