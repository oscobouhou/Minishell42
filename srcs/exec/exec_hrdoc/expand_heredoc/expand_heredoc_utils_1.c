/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc_utils_1.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 18:05:29 by oboutarf          #+#    #+#             */
/*   Updated: 2023/02/08 19:14:39 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cutitintypes_heredoc(t_mshell *mshell, int *tmp_i, int *n_tp, int *i)
{
	int	j;

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

int	treat_len_out_quotes__hrdoc(t_mshell *mshell, int *i, int *cuts)
{
	if (mshell->tkn->tkn[*i] != DOUBLE_QUOTE && \
		mshell->tkn->tkn[*i] != SINGLE_QUOTE)
	{
		while (mshell->tkn->tkn[*i] && mshell->tkn->tkn[*i] \
			!= DOUBLE_QUOTE && mshell->tkn->tkn[*i] != SINGLE_QUOTE)
			(*i)++;
		(*cuts)++;
	}
	return (1);
}

int	treat_len_in_double_q__hrdoc(t_mshell *mshell, int *i, int *cuts)
{
	if (mshell->tkn->tkn[*i] == DOUBLE_QUOTE)
	{
		(*i)++;
		while (mshell->tkn->tkn[*i] && mshell->tkn->tkn[*i] != DOUBLE_QUOTE)
			(*i)++;
		(*cuts)++;
		(*i)++;
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
		treat_len_in_double_q__hrdoc(mshell, &i, &cuts);
		if (mshell->tkn->tkn[i] == SINGLE_QUOTE)
		{
			i += 1;
			while (mshell->tkn->tkn[i] && mshell->tkn->tkn[i] != SINGLE_QUOTE)
				i++;
			cuts++;
			i += 1;
		}
	}
	return (cuts);
}

int	init_cut_types_expander__hrdoc(t_mshell *mshell)
{
	mshell->expd->types = malloc(sizeof(char *) * (mshell->expd->n_types + 1));
	mshell->expd->types[mshell->expd->n_types] = NULL;
	if (!mshell->expd->types)
		return (0);
	return (1);
}
