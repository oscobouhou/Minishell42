/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_hrdoc_delim.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:48:15 by oboutarf          #+#    #+#             */
/*   Updated: 2023/02/03 11:21:52 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	new_type = malloc(sizeof(char) * (i - j + 1));
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
		j++;
		i++;
	}
	new_type[j] = '\0';
	free(mshell->expd->types[n_tp]);
	mshell->expd->types[n_tp] = new_type;
	return (1);
}

int	center_hrdoc_delim_treatment(t_mshell *mshell, int *expander)
{
	int	n_tp;

	n_tp = 0;
	mshell->expd->n_types = find_types_len_expd(mshell);
	cut_types_expd(mshell);
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
	join_types_expanded(mshell);
	return (1);
}
