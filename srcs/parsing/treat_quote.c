/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 16:46:21 by oboutarf          #+#    #+#             */
/*   Updated: 2023/01/12 17:29:25 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	search_next_quote(t_mshell *mshell, char quote, int *q)
{
	if (!mshell->rdline_outp[*q + 1])
		return (0);
	while (mshell->rdline_outp[++(*q)])
		if (mshell->rdline_outp[*q] == quote)
			return (1);
	return (0);
}

int	treat_quote(t_mshell *mshell, int *i)
{
	int	tmp_i;

	if (mshell->rdline_outp[*i] == SINGLE_QUOTE)
	{
		tmp_i = *i;
		if (!search_next_quote(mshell, SINGLE_QUOTE, i))
			return (dprintf(2, "error\n"), 0);
		++(*i);
		mshell->tkn->type = 2;
		if (!tokenizer(mshell, tmp_i, *i))
			return (0);
		return (1);
	}
	else if (mshell->rdline_outp[*i] == DOUBLE_QUOTE)
	{
		tmp_i = *i;
		if (!search_next_quote(mshell, DOUBLE_QUOTE, i))
			return (dprintf(2, "error\n"), 0);
		++(*i);
		mshell->tkn->type = 3;
		if (!tokenizer(mshell, tmp_i, *i))
			return (0);
		return (1);
	}
	return (0);
}
