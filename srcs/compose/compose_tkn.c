/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compose_tkn.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 15:32:02 by oboutarf          #+#    #+#             */
/*   Updated: 2023/01/16 13:16:14 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tokens(t_mshell *mshell)
{
	mshell->tkn = mshell->head_tkn;
	while (mshell->tkn->next)
	{
		dprintf(2, "content: %s	---	type: %d\n", mshell->tkn->tkn, mshell->tkn->type);
		mshell->tkn = mshell->tkn->next;
	}
	mshell->tkn = mshell->head_tkn;
}

int	compose_tkn(t_mshell *mshell)
{
	mshell->tkn = mshell->head_tkn;
	if (!tokenize_heredoc(mshell))
		return (0);
	if (!review_tokens(mshell))
		return (0);
	if (!center_expand(mshell))
		return (0);
	return (1);
}
