/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   center_expand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 22:46:34 by oboutarf          #+#    #+#             */
/*   Updated: 2023/02/08 12:55:57 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_expd_for_update(t_mshell *mshell, int i0, int *i2, \
	char **update)
{
	if (mshell->expd->expander)
	{
		while (mshell->expd->expander[i0])
		{
			(*update)[*i2] = mshell->expd->expander[i0];
			(*i2)++;
			i0++;
		}
		(*update)[*i2] = '\0';
		if (mshell->expd->expander)
		{
			free(mshell->expd->expander);
			mshell->expd->expander = NULL;
		}
	}
	return (1);
}

int	untreat_dollar(t_mshell *mshell, int i, int n_tp)
{
	while (mshell->expd->types[n_tp][i] \
		&& mshell->expd->types[n_tp][i] != EXPAND)
	{
		if (mshell->expd->types[n_tp][i] != EXPAND)
			return (i);
		i++;
	}
	return (i);
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
