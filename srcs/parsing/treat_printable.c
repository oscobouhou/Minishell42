/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_printable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 15:39:06 by oboutarf          #+#    #+#             */
/*   Updated: 2023/01/16 19:51:22 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_printable_char(char print)
{
	// if (print == SINGLE_QUOTE || print == DOUBLE_QUOTE)
		// return (0);
	if ((print >= 9 && print <= 13) || print == 32)
		return (0);
	if (print == REDIR_L || print == REDIR_R)
		return (0);
	if (print == PIPE_LINE)
		return (0);
	return (1);
}

int	treat_printable(t_mshell *mshell, int *i)
{
	int	tmp_i;

	tmp_i = *i;
	while (mshell->rdline_outp[*i] && check_printable_char(mshell->rdline_outp[*i]))
	{
		if (mshell->rdline_outp[*i]  == SINGLE_QUOTE || mshell->rdline_outp[*i]  == DOUBLE_QUOTE)
			if (!search_next_quote(mshell, mshell->rdline_outp[*i], i))
				return (dprintf(2, "errrrrorrrrr !"), 0);
		++(*i);
	}
	mshell->tkn->type = WORD;
	if (!tokenizer(mshell, tmp_i, *i))
		return (0);
	return (1);
}

// dprintf(2, "%s\n", (char *)&mshell->rdline_outp[*i]);
	// if (mshell->rdline_outp[*i] == SINGLE_QUOTE || mshell->rdline_outp[*i] == DOUBLE_QUOTE)
	// {
	// 	++(*i);
	// 	while (mshell->rdline_outp[*i] && check_printable_char(mshell->rdline_outp[*i]))
	// 		++(*i);
	// 	++(*i);
	// }