/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 16:46:21 by oboutarf          #+#    #+#             */
/*   Updated: 2023/01/11 01:10:53 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	extract_quote(t_mshell *mshell, int start, int len)
{
	(void)mshell;
	(void)start;
	(void)len;
	return (0);
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

int	treat_quotes(t_mshell *mshell)
{
	int	tmp_q;
	int	q;

	q = -1;
    while (mshell->rdline_outp[++q])
	{
		if (mshell->rdline_outp[q] == SINGLE_QUOTE)
		{
			tmp_q = q;
			if (!search_next_quote(mshell, SINGLE_QUOTE, &q))
				return (dprintf(2, "error\n"), 0);											// syntax error - process errno
			if (!extract_quote(mshell, tmp_q, q))
				return (0);
		}
		else if (mshell->rdline_outp[q] == DOUBLE_QUOTE)
		{
			if (!search_next_quote(mshell, DOUBLE_QUOTE, &q))
				return (dprintf(2, "error\n"), 0); 												// syntax error - process errno
		}
	}
    return (0);
}
