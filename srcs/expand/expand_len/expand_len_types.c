/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_len_types.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 00:23:31 by oboutarf          #+#    #+#             */
/*   Updated: 2023/01/21 00:27:49 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_types_len_expd(t_mshell *mshell)
{
	int	cuts;
	int	i;
	
	i = 0;
	cuts = 0;
	while (mshell->tkn->tkn[i])
	{
		if (mshell->tkn->tkn[i] != DOUBLE_QUOTE && mshell->tkn->tkn[i] != SINGLE_QUOTE)
		{
			while (mshell->tkn->tkn[i] && mshell->tkn->tkn[i] != DOUBLE_QUOTE && mshell->tkn->tkn[i] != SINGLE_QUOTE)
				i++;
			cuts++;
		}
		if (mshell->tkn->tkn[i] == DOUBLE_QUOTE)
		{
			i += 1;
			while (mshell->tkn->tkn[i] && mshell->tkn->tkn[i] != DOUBLE_QUOTE)
				i++;
			cuts++;
			i += 1;
		}
		if (mshell->tkn->tkn[i] == SINGLE_QUOTE)
		{
			i += 1;
			while (mshell->tkn->tkn[i] && mshell->tkn->tkn[i] != SINGLE_QUOTE)
				i++;
			cuts++;
			i += 1;
		}
	}
	return (cuts);
}