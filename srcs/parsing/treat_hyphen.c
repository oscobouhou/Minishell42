/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_hyphen.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 15:58:01 by oboutarf          #+#    #+#             */
/*   Updated: 2023/01/12 13:37:09 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_after_hyphen(char print)
{
	if ((print >= 9 && print <= 13) || print == 32)
		return (0);
	if (print == REDIR_L || print == REDIR_R)
		return (0);
	if (print == PIPE_LINE)
		return (0);
	return (1);
}

int	treat_hyphen(t_mshell *mshell, int *i)
{
	int	tmp_i;

	tmp_i = *i;
	++(*i);
	while (mshell->rdline_outp[*i]
		&& check_after_hyphen(mshell->rdline_outp[*i]))
		++(*i);
	mshell->tkn->type = 8;
	if (!tokenizer(mshell, tmp_i, *i))
		return (0);
	return (1);
}
