/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   center_expand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 22:46:34 by oboutarf          #+#    #+#             */
/*   Updated: 2023/01/17 20:46:47 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_expand(t_mshell*mshell)
{
	int	in_quote;
	int	i;

	i = -1;
	in_quote = 0;
	if (mshell->tkn->type == DLIM_HRDOC)
		return (0);
	while (mshell->tkn->tkn[++i])
	{
		if (mshell->tkn->tkn[i] == SINGLE_QUOTE)
			in_quote += 1;
		else if (mshell->tkn->tkn[i] == EXPAND && in_quote % 2 == 0)
		{
			if (!check_valid_expand(mshell, &i))
				return (0);
		}
	}
	return (0);
}

int	center_expand(t_mshell *mshell)
{
	mshell->tkn = mshell->head_tkn;
	while (mshell->tkn->next)
	{
		is_expand(mshell);
		mshell->tkn = mshell->tkn->next;
	}
	(void)mshell;
	return (1);
}
