/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_len_types.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 00:23:31 by oboutarf          #+#    #+#             */
/*   Updated: 2023/02/03 18:42:16 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_types_len_expd(t_mshell *mshell)
{
	int	cuts;
	int	i;
	
	i = 0;
	cuts = 0;
	while (mshell->rdline_outp[i])
	{
		if (mshell->rdline_outp[i] != DOUBLE_QUOTE && mshell->rdline_outp[i] != SINGLE_QUOTE)
		{
			while (mshell->rdline_outp[i] && mshell->rdline_outp[i] != DOUBLE_QUOTE && mshell->rdline_outp[i] != SINGLE_QUOTE)
				i++;
			cuts++;
		}
		if (mshell->rdline_outp[i] == DOUBLE_QUOTE)
		{
			i += 1;
			while (mshell->rdline_outp[i] && mshell->rdline_outp[i] != DOUBLE_QUOTE)
				i++;
			cuts++;
			i += 1;
		}
		if (mshell->rdline_outp[i] == SINGLE_QUOTE)
		{
			i += 1;
			while (mshell->rdline_outp[i] && mshell->rdline_outp[i] != SINGLE_QUOTE)
				i++;
			cuts++;
			i += 1;
		}
	}
	return (cuts);
}