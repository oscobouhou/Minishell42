/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   center_expand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 22:46:34 by oboutarf          #+#    #+#             */
/*   Updated: 2023/01/25 03:31:08 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	update_type(t_mshell *mshell, int *i, int n_tp)
{
	char 	*update;
	int		i0;
	int		i1;
	int		i2;

	i0 = 0;
	i1 = 0;
	i2 = 0;
	while (i1 != (*i + mshell->expd->new_expd_len))
		i1++;
	while (mshell->expd->types[n_tp][i2 + *i + mshell->expd->old_expd_len])
		i2++;
	update = malloc(sizeof(char) + (i1 + i2));
	if (!update)
		return (0);
	i2 = 0;
	while (i2 < *i)
	{
		update[i2] = mshell->expd->types[n_tp][i2];
		i2++;
	}
	if (mshell->expd->expander)
	{
		while (mshell->expd->expander[i0])
		{
			update[i2] = mshell->expd->expander[i0];
			i0++;
			i2++;
		}
	}
	i0 = 1;
	while (mshell->expd->types[n_tp][*i + i0 + mshell->expd->old_expd_len])
	{
		update[i2] = mshell->expd->types[n_tp][*i + i0 + mshell->expd->old_expd_len];
		i2++;
		i0++;
	}
	update[i2] = '\0';
	free(mshell->expd->types[n_tp]);
	mshell->expd->types[n_tp] = update;
	*i += mshell->expd->new_expd_len;
	// if (mshell->expd->types[n_tp][*i + 1] == DOUBLE_QUOTE)
	// 	*i += 1;
	return (1);
}

int	center_expand(t_mshell *mshell)
{
	mshell->tkn = mshell->head_tkn;
	while (mshell->tkn->next)
	{
		if (mshell->tkn->type == _CMD || mshell->tkn->type == _ARG || mshell->tkn->type == _FILE)
		{
			mshell->expd->n_types = find_types_len_expd(mshell);
			cut_types_expd(mshell);
			manage_expands_in_types(mshell);
			join_types_expanded(mshell);
		}
		mshell->tkn = mshell->tkn->next;
	}
	return (1);
}
