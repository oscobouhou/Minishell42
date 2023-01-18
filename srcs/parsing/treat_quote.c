/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 16:46:21 by oboutarf          #+#    #+#             */
/*   Updated: 2023/01/18 16:29:20 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* void	quote_remover(t_mshell *mshell)
{
	char	quote;
	int		mask;
	int		i;

	i = 0;
	mask = 0;
	quote = 0;
	while (mshell->tkn->tkn[i])
	{
		if (mshell->tkn->tkn[i] == SINGLE_QUOTE || mshell->tkn->tkn[i] == DOUBLE_QUOTE)
			quote = mshell->tkn->tkn[i];
		while (mshell->tkn->tkn[i])
	}
} */

int	remove_quotes(t_mshell *mshell)
{
	while (mshell->tkn)
	{
		// quote_remover();
		// mask = 0;
		// quote = 0;
		mshell->tkn = mshell->tkn->next;
	}	
	return (1);
}

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


	tmp_i = *i;
	if (!search_next_quote(mshell, mshell->rdline_outp[*i], i))
		return (dprintf(2, "error\n"), 0);
	++(*i);
	
	
	while (mshell->rdline_outp[*i] && check_printable_char(mshell->rdline_outp[*i]))
	{
		if (mshell->rdline_outp[*i]  == SINGLE_QUOTE || mshell->rdline_outp[*i]  == DOUBLE_QUOTE)
			if (!search_next_quote(mshell, mshell->rdline_outp[*i], i))
				return (dprintf(2, "error !"), 0);
		++(*i);
	}
	
	mshell->tkn->type = WORD;
	if (!tokenizer(mshell, tmp_i, *i))
		return (0);
	return (1);
}
