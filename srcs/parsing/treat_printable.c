/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_printable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 15:39:06 by oboutarf          #+#    #+#             */
/*   Updated: 2023/02/10 14:31:33 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_printable_char(char print)
{
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
	while (mshell->rdline_outp[*i]
		&& check_printable_char(mshell->rdline_outp[*i]))
	{
		if (mshell->rdline_outp[*i] == SINGLE_QUOTE
			|| mshell->rdline_outp[*i] == DOUBLE_QUOTE)
			if (!search_next_quote(mshell, mshell->rdline_outp[*i], i))
				return (ft_putstr_fd(2, "minishell: unclosed quotes"), 0);
		++(*i);
	}
	mshell->tkn->type = WORD;
	if (!tokenizer(mshell, tmp_i, *i))
		return (0);
	return (1);
}
