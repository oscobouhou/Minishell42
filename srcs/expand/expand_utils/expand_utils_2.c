/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 13:38:51 by oboutarf          #+#    #+#             */
/*   Updated: 2023/02/08 13:41:11 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_cut_types_expander(t_mshell *mshell)
{
	mshell->expd->types = malloc(sizeof(char *) * (mshell->expd->n_types + 1));
	mshell->expd->types[mshell->expd->n_types] = NULL;
	if (!mshell->expd->types)
		return (0);
	return (1);
}

void	cutitintypes(t_mshell *mshell, int *tmp_i, int *n_tp, int *i)
{
	int	j;

	j = 0;
	while (*tmp_i <= (*i - 1))
	{
		mshell->expd->types[*n_tp][j] = mshell->rdline_outp[*tmp_i];
		(*tmp_i)++;
		j++;
	}
	mshell->expd->types[*n_tp][j] = '\0';
	(*n_tp)++;
}
