/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 13:10:51 by oboutarf          #+#    #+#             */
/*   Updated: 2023/01/15 17:06:22 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_expand_in_token(t_mshell *mshell)
{
	int	i;

	while (mshell->tkn->next)
	{
		i = -1;
		if (mshell->tkn->type != SQ_WORD)
			while (mshell->tkn->tkn[++i])
				if (mshell->tkn->tkn[i] == EXPAND)
					if (!manage_expands(mshell, &i))
						break ;
		mshell->tkn = mshell->tkn->next;
	}
	mshell->tkn = mshell->head_tkn;
	return (1);
}
