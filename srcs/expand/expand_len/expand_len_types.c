/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_len_types.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 00:23:31 by oboutarf          #+#    #+#             */
/*   Updated: 2023/02/05 10:10:26 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	treat_len_out_quotes(t_mshell *mshell, int *i, int *cuts)
{
	if (mshell->rdline_outp[*i] != DOUBLE_QUOTE \
		&& mshell->rdline_outp[*i] != SINGLE_QUOTE)
	{
		while (mshell->rdline_outp[*i] && mshell->rdline_outp[*i] \
			!= DOUBLE_QUOTE && mshell->rdline_outp[*i] != SINGLE_QUOTE)
			(*i)++;
		(*cuts)++;
	}
	return (1);
}

void	single_n_double(t_mshell *mshell, int *i, int *cuts, int quote)
{
	if (mshell->rdline_outp[*i] == quote)
	{
		i += 1;
		while (mshell->rdline_outp[*i]
			&& mshell->rdline_outp[*i] != quote)
			i++;
		(*cuts)++;
		if (mshell->rdline_outp[*i + 1])
			i += 1;
	}
}

int	find_types_len_expd(t_mshell *mshell)
{
	int	cuts;
	int	i;

	i = 0;
	cuts = 0;
	while (mshell->rdline_outp[i])
	{
		treat_len_out_quotes(mshell, &i, &cuts);
		single_n_double(mshell, &i, &cuts, SINGLE_QUOTE);
		single_n_double(mshell, &i, &cuts, DOUBLE_QUOTE);
	}
	return (cuts);
}
