/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_cut_types.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 00:45:27 by oboutarf          #+#    #+#             */
/*   Updated: 2023/02/05 22:08:28 by oboutarf         ###   ########.fr       */
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

int	treat_single_quote_expand_cut(t_mshell *mshell, \
	int *i, int *tmp_i, int *n_tp)
{
	if (mshell->rdline_outp[*i] == SINGLE_QUOTE)
	{
		*tmp_i = *i;
		*i += 1;
		while (mshell->rdline_outp[*i] \
			&& mshell->rdline_outp[*i] != SINGLE_QUOTE)
			(*i)++;
		*i += 1;
		mshell->expd->types[*n_tp] = malloc(sizeof(char) * (*i - *tmp_i) + 2);
		if (!mshell->expd->types[*n_tp])
			return (0);
		cutitintypes(mshell, tmp_i, n_tp, i);
	}
	return (1);
}

int	treat_double_quote_expand_cut(t_mshell *mshell, int *i, \
	int *tmp_i, int *n_tp)
{
	if (mshell->rdline_outp[*i] == DOUBLE_QUOTE)
	{
		*tmp_i = *i;
		*i += 1;
		while (mshell->rdline_outp[*i] \
			&& mshell->rdline_outp[*i] != DOUBLE_QUOTE)
			(*i)++;
		*i += 1;
		mshell->expd->types[*n_tp] = malloc(sizeof(char) * (*i - *tmp_i) + 1);
		if (!mshell->expd->types[*n_tp])
			return (0);
		cutitintypes(mshell, tmp_i, n_tp, i);
	}
	return (1);
}

int	treat_out_quote_expand_cut(t_mshell *mshell, int *i, int *tmp_i, int *n_tp)
{
	int	j;

	j = 0;
	*tmp_i = *i;
	while (mshell->rdline_outp[*i] && mshell->rdline_outp[*i] != DOUBLE_QUOTE \
		&& mshell->rdline_outp[*i] != SINGLE_QUOTE)
		(*i)++;
	mshell->expd->types[*n_tp] = malloc(sizeof(char) * (*i - *tmp_i) + 1);
	if (!mshell->expd->types[*n_tp])
		return (0);
	while (*tmp_i < *i)
	{
		mshell->expd->types[*n_tp][j] = mshell->rdline_outp[*tmp_i];
		(*tmp_i)++;
		j++;
	}
	mshell->expd->types[*n_tp][j] = '\0';
	(*n_tp)++;
	return (1);
}

int	cut_types_expd(t_mshell *mshell)
{
	int	tmp_i;
	int	n_tp;
	int	i;

	i = 0;
	n_tp = 0;
	tmp_i = 0;
	init_cut_types_expander(mshell);
	while (mshell->rdline_outp[i])
	{
		if (mshell->rdline_outp[i] != SINGLE_QUOTE \
			&& mshell->rdline_outp[i] != DOUBLE_QUOTE)
			treat_out_quote_expand_cut(mshell, &tmp_i, &i, &n_tp);
		if (mshell->rdline_outp[i] == DOUBLE_QUOTE)
			treat_double_quote_expand_cut(mshell, &tmp_i, &i, &n_tp);
		if (mshell->rdline_outp[i] == SINGLE_QUOTE)
			treat_single_quote_expand_cut(mshell, &tmp_i, &i, &n_tp);
	}
	return (1);
}
