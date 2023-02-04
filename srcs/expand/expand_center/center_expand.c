/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   center_expand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 22:46:34 by oboutarf          #+#    #+#             */
/*   Updated: 2023/02/04 12:02:05 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_expd_for_update(t_mshell *mshell, int i0, int *i2, char **update)
{
	if (mshell->expd->expander)
	{
		while (mshell->expd->expander[i0])
		{
			(*update)[*i2] = mshell->expd->expander[i0];
			(*i2)++;
			i0++;
		}
	}
	return (1);
}

int	update_type(t_mshell *mshell, int *i, int n_tp)
{
	char 	*update;
	int		i0;
	int		i1;
	int		i2;

	i0 = 0;
	i1 = 0;
	i2 = 0;
	if (!mshell->expd->types[n_tp] && !mshell->expd->types[n_tp][*i])
		return (1);
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
	check_expd_for_update(mshell, i0, &i2, &update);
	if (!mshell->expd->types[n_tp][*i + i0 + mshell->expd->old_expd_len])
		i0 = 0;
	else
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
	return (1);
}

int	only_quote_str(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != SINGLE_QUOTE && str[i] != DOUBLE_QUOTE)
			return (0);
		i++;
	}
	return (1);
}

int	seek_expander(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == EXPAND)
			return (1);
		i++;
	}
	return (0);
}

int	center_expand(t_mshell *mshell)
{
	mshell->tkn = mshell->head_tkn;
	if (only_quote_str(mshell->rdline_outp))
		return (1);
	if (!seek_expander(mshell->rdline_outp))
		return (1);
	mshell->expd->n_types = find_types_len_expd(mshell);
	cut_types_expd(mshell);
	manage_expands_in_types(mshell);
	free(mshell->rdline_outp);
	mshell->rdline_outp = NULL;
	mshell->rdline_outp = join_types_expanded(mshell);
	if (!mshell->rdline_outp)
		return (0);
	return (1);
}

	// int	n_tp = 0;
	// while (mshell->expd->types[n_tp])
	// {
	// 	dprintf(2, "|%s|\n", mshell->expd->types[n_tp]);
	// 	n_tp++;
	// }