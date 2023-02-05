/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   center_expand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 22:46:34 by oboutarf          #+#    #+#             */
/*   Updated: 2023/02/05 02:38:13 by oboutarf         ###   ########.fr       */
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
	while (mshell->expd->types[n_tp][i] && mshell->expd->types[n_tp][i] != EXPAND)
	{
		if (mshell->expd->types[n_tp][i] != EXPAND)
			return (i);
		i++;
	}
	return (i);
}

int	update_type(t_mshell *mshell, int *i, int n_tp)
{
	char 	*update;
	int 	ptr[3];
	int		d;

	d = untreat_dollar(mshell, *i, n_tp);
	if (d)
	{

		return (*i += d);
	}
	ptr[0] = ft_strlen(mshell->expd->types[n_tp]) - mshell->expd->old_expd_len + 1;
	if (!mshell->expd->expander)
	{
		update = malloc(sizeof(char) * (ptr[0] + 1));
		if (!update)
			return (0);
		ptr[0] = 0;
		while (ptr[0] < *i)
		{
			update[ptr[0]] = mshell->expd->types[n_tp][ptr[0]];
			ptr[0]++;
		}
		*i = ptr[0];
		ptr[1] = ptr[0];
		ptr[0] += mshell->expd->old_expd_len + 1;
		while (mshell->expd->types[n_tp][ptr[0]])
		{
			update[ptr[1]] = mshell->expd->types[n_tp][ptr[0]];
			ptr[0]++;
			ptr[1]++;
		}
		update[ptr[1]] = '\0';
		free(mshell->expd->types[n_tp]);
		mshell->expd->types[n_tp] = update;
	}
	else
	{
		ptr[0] += mshell->expd->new_expd_len;
		update = malloc(sizeof(char) * (ptr[0]) + 1);
		if (!update)
			return (0);
		ptr[0] = 0;
		while (ptr[0] < *i)
		{
			update[ptr[0]] = mshell->expd->types[n_tp][ptr[0]];
			ptr[0]++;
		}
		ptr[1] = 0;
		ptr[2] = ptr[0] + mshell->expd->old_expd_len + 1;
		while (mshell->expd->expander[ptr[1]])
		{
			update[ptr[0]] = mshell->expd->expander[ptr[1]];
			ptr[0]++;
			ptr[1]++;
		}
		free(mshell->expd->expander);
		*i = ptr[0];
		mshell->expd->expander = NULL;
		while (mshell->expd->types[n_tp][ptr[2]])
		{
			update[ptr[0]] = mshell->expd->types[n_tp][ptr[2]];
			ptr[0]++;
			ptr[2]++;
		}
		update[ptr[0]] = '\0';
		free(mshell->expd->types[n_tp]);
		mshell->expd->types[n_tp] = update;
	}
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