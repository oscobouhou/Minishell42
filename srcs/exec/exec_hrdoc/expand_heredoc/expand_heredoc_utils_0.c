/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc_utils_0.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 17:59:19 by oboutarf          #+#    #+#             */
/*   Updated: 2023/02/08 19:13:55 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	treat_single_quote_expand_cut__hrdoc(t_mshell *mshell, \
	int *i, int *tmp_i, int *n_tp)
{
	if (mshell->tkn->tkn[*i] == SINGLE_QUOTE)
	{
		*tmp_i = *i;
		*i += 1;
		while (mshell->tkn->tkn[*i] && mshell->tkn->tkn[*i] != SINGLE_QUOTE)
		{
			(*i)++;
		}
		*i += 1;
		mshell->expd->types[*n_tp] = malloc(sizeof(char) * (*i - *tmp_i) + 2);
		if (!mshell->expd->types[*n_tp])
			return (0);
		cutitintypes_heredoc(mshell, tmp_i, n_tp, i);
	}
	return (1);
}

int	treat_double_quote_expand_cut__hrdoc(t_mshell *mshell, int *i, \
	int *tmp_i, int *n_tp)
{
	if (mshell->tkn->tkn[*i] == DOUBLE_QUOTE)
	{
		*tmp_i = *i;
		*i += 1;
		while (mshell->tkn->tkn[*i] && mshell->tkn->tkn[*i] != DOUBLE_QUOTE)
			(*i)++;
		*i += 1;
		mshell->expd->types[*n_tp] = malloc(sizeof(char) * (*i - *tmp_i) + 1);
		if (!mshell->expd->types[*n_tp])
			return (0);
		cutitintypes_heredoc(mshell, tmp_i, n_tp, i);
	}
	return (1);
}

int	treat_out_quote_expand_cut__hrdoc(t_mshell *mshell, int *i,
	int *tmp_i, int *n_tp)
{
	int	j;

	j = 0;
	*tmp_i = *i;
	while (mshell->tkn->tkn[*i] && mshell->tkn->tkn[*i] != DOUBLE_QUOTE \
		&& mshell->tkn->tkn[*i] != SINGLE_QUOTE)
		(*i)++;
	mshell->expd->types[*n_tp] = malloc(sizeof(char) * (*i - *tmp_i) + 1);
	if (!mshell->expd->types[*n_tp])
		return (0);
	while (*tmp_i < *i)
	{
		mshell->expd->types[*n_tp][j] = mshell->tkn->tkn[*tmp_i];
		(*tmp_i)++;
		j++;
	}
	mshell->expd->types[*n_tp][j] = '\0';
	(*n_tp)++;
	return (1);
}

int	cut_types_expd__hrdoc(t_mshell *mshell)
{
	int	tmp_i;
	int	n_tp;
	int	i;

	i = 0;
	n_tp = 0;
	tmp_i = 0;
	init_cut_types_expander__hrdoc(mshell);
	while (mshell->tkn->tkn[i])
	{
		if (mshell->tkn->tkn[i] != SINGLE_QUOTE \
			&& mshell->tkn->tkn[i] != DOUBLE_QUOTE)
			treat_out_quote_expand_cut__hrdoc(mshell, &tmp_i, &i, &n_tp);
		if (mshell->tkn->tkn[i] == SINGLE_QUOTE)
			treat_single_quote_expand_cut__hrdoc(mshell, &tmp_i, &i, &n_tp);
		if (mshell->tkn->tkn[i] == DOUBLE_QUOTE)
			treat_double_quote_expand_cut__hrdoc(mshell, &tmp_i, &i, &n_tp);
	}
	return (1);
}
