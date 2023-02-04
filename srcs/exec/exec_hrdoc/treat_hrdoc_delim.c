/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_hrdoc_delim.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:48:15 by oboutarf          #+#    #+#             */
/*   Updated: 2023/02/04 16:52:21 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	treat_len_out_quotes__hrdoc(t_mshell *mshell, int *i, int *cuts)
{
	if (mshell->tkn->tkn[*i] != DOUBLE_QUOTE && mshell->tkn->tkn[*i] != SINGLE_QUOTE)
	{
		while (mshell->tkn->tkn[*i] && mshell->tkn->tkn[*i] != DOUBLE_QUOTE && mshell->tkn->tkn[*i] != SINGLE_QUOTE)
			(*i)++;
		(*cuts)++;
	}
	return (1);
}

int	find_types_len_expd__hrdoc(t_mshell *mshell)
{
	int	cuts;
	int	i;
	
	i = 0;
	cuts = 0;
	while (mshell->tkn->tkn[i])
	{
		treat_len_out_quotes__hrdoc(mshell, &i, &cuts);
		if (mshell->tkn->tkn[i] == DOUBLE_QUOTE)
		{
			i += 1;
			while (mshell->tkn->tkn[i] && mshell->tkn->tkn[i] != DOUBLE_QUOTE)
				i++;
			cuts++;
			i += 1;
		}
		if (mshell->tkn->tkn[i] == SINGLE_QUOTE)
		{
			i += 1;
			while (mshell->tkn->tkn[i] && mshell->tkn->tkn[i] != SINGLE_QUOTE)
				i++;
			cuts++;
			if (mshell->tkn->tkn[i + 1])
				i += 1;
		}
	}
	return (cuts);
}


int init_cut_types_expander__hrdoc(t_mshell *mshell)
{
	mshell->expd->types = malloc(sizeof(char *) * (mshell->expd->n_types + 1));
	mshell->expd->types[mshell->expd->n_types] = NULL;
	if (!mshell->expd->types)
		return (0);
	return (1);
}

int	treat_single_quote_expand_cut__hrdoc(t_mshell *mshell, int *i, int *tmp_i, int *n_tp)
{
	int	j;

	j = 0;
	if (mshell->tkn->tkn[*i] == SINGLE_QUOTE)
	{
		*tmp_i = *i - 1;
		*i += 1;
		while (mshell->tkn->tkn[*i] && mshell->tkn->tkn[*i] != SINGLE_QUOTE)
		{
			(*i)++;
		}
		*i += 1;
		mshell->expd->types[*n_tp] = malloc(sizeof(char) * (*i - *tmp_i) + 2);
		if (!mshell->expd->types[*n_tp])
			return (0);
		j = 0;
		while (*tmp_i <= (*i - 1))
		{
			mshell->expd->types[*n_tp][j] = mshell->tkn->tkn[*tmp_i];
			(*tmp_i)++;
			j++;
		}
		mshell->expd->types[*n_tp][j] = '\0';
		(*n_tp)++;
	}
	return (1);
}

int treat_double_quote_expand_cut__hrdoc(t_mshell *mshell, int *i, int *tmp_i, int *n_tp)
{
	int j;

	j = 0;
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
		j = 0;
		while (*tmp_i <= (*i - 1))
		{
			mshell->expd->types[*n_tp][j] = mshell->tkn->tkn[*tmp_i];
			(*tmp_i)++;
			j++;
		}
		mshell->expd->types[*n_tp][j] = '\0';
		(*n_tp)++;
	}
	return (1);
}

int treat_out_quote_expand_cut__hrdoc(t_mshell *mshell, int *i, int *tmp_i, int *n_tp)
{
	int	j;

	j = 0;
	*tmp_i = *i;
	while (mshell->tkn->tkn[*i] && mshell->tkn->tkn[*i] != DOUBLE_QUOTE && mshell->tkn->tkn[*i] != SINGLE_QUOTE)
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


int	manage_hrdoc_delim_in_q(t_mshell *mshell, int n_tp)
{
	char	*new_type;
	int		i;
	int		j;

	i = 1;
	while (mshell->expd->types[n_tp][i + 1])
		i++;
	new_type = malloc(sizeof(char) * (i + 1));
	i = 1;
	j = 0;
	while (mshell->expd->types[n_tp][i + 1])
	{
		new_type[j] = mshell->expd->types[n_tp][i];
		i++;
		j++;
	}
	new_type[j] = '\0';
	free(mshell->expd->types[n_tp]);
	mshell->expd->types[n_tp] = new_type;
	return (1);
}

int	manage_hrdoc_delim_oq(t_mshell *mshell, int n_tp)
{
	char	*new_type;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (mshell->expd->types[n_tp][i])
	{
		if (mshell->expd->types[n_tp][i] == EXPAND)
			if (mshell->expd->types[n_tp + 1]
				&& (mshell->expd->types[n_tp + 1][0] == SINGLE_QUOTE
				|| mshell->expd->types[n_tp + 1][0] == DOUBLE_QUOTE))
				j++;
		i++;
	}
	new_type = malloc(sizeof(char) * (i - j + 2));
	if (!new_type)
		return (0);
	i = 0;
	j = 0;
	while (mshell->expd->types[n_tp][i])
	{
		if (mshell->expd->types[n_tp][i] == EXPAND)
			if (mshell->expd->types[n_tp + 1]
				&& (mshell->expd->types[n_tp + 1][0] == SINGLE_QUOTE
				|| mshell->expd->types[n_tp + 1][0] == DOUBLE_QUOTE))
				i++;
		new_type[j] = mshell->expd->types[n_tp][i];
		if (i >= ft_strlen(mshell->expd->types[n_tp]))
			break ;
		j++;
		i++;
	}
	new_type[j] = '\0';
	free(mshell->expd->types[n_tp]);
	mshell->expd->types[n_tp] = new_type;
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
		if (mshell->tkn->tkn[i] != SINGLE_QUOTE && mshell->tkn->tkn[i] != DOUBLE_QUOTE)
			treat_out_quote_expand_cut__hrdoc(mshell, &tmp_i, &i, &n_tp);
		if (mshell->tkn->tkn[i] == SINGLE_QUOTE)
			treat_single_quote_expand_cut__hrdoc(mshell, &tmp_i, &i, &n_tp);
		if (mshell->tkn->tkn[i] == DOUBLE_QUOTE)
			treat_double_quote_expand_cut__hrdoc(mshell, &tmp_i, &i, &n_tp);
	}
	return (1);
}

int tablen(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return (-42);
	while (tab[i])
		i++;
	return (i);
}

int	center_hrdoc_delim_treatment(t_mshell *mshell, int *expander)
{
	char	*dlim;
	int		n_tp;

	n_tp = 0;
	mshell->expd->n_types = find_types_len_expd__hrdoc(mshell);
	cut_types_expd__hrdoc(mshell);
	while (mshell->expd->types[n_tp])
	{
		if (mshell->expd->types[n_tp][0] == DOUBLE_QUOTE
			|| mshell->expd->types[n_tp][0] == SINGLE_QUOTE)
		{
			manage_hrdoc_delim_in_q(mshell, n_tp);
			*expander = 42;
		}
		else
			manage_hrdoc_delim_oq(mshell, n_tp);
		n_tp++;
	}
	dlim = join_types_expanded(mshell);
	free(mshell->tkn->tkn);
	mshell->tkn->tkn = NULL;
	mshell->tkn->tkn = dlim;
	return (1);
}
