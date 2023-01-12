/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_printable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 15:39:06 by oboutarf          #+#    #+#             */
/*   Updated: 2023/01/12 13:32:49 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_printable(char print)
{
	if (print == SINGLE_QUOTE || print == DOUBLE_QUOTE)
		return (0);
	if ((print >= 9 && print <= 13) || print == 32)
		return (0);
	if (print == REDIR_L || print == REDIR_R)
		return (0);
	if (print == EXPAND || print == HYPHEN)
		return (0);
	if (print == PIPE_LINE)
		return (0);
	return (1);
}

int	treat_printable(t_mshell *mshell, int *i)
{
	int	tmp_i;

	tmp_i = *i;
	while (mshell->rdline_outp[*i] && check_printable(mshell->rdline_outp[*i]))
		++(*i);
	mshell->tkn->type = 1;
	if (!tokenizer(mshell, tmp_i, *i))
		return (0);
	return (1);
}
