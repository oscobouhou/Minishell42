/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_hrdoc_delim.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:48:15 by oboutarf          #+#    #+#             */
/*   Updated: 2023/02/08 19:13:15 by oboutarf         ###   ########.fr       */
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

void	write_heredoc_delim_oq(t_mshell *mshell, int n_tp, char **new_type)
{
	int	j;
	int	i;

	j = 0;
	i = 0;
	while (mshell->expd->types[n_tp][i])
	{
		if (mshell->expd->types[n_tp][i] == EXPAND)
			if (mshell->expd->types[n_tp + 1]
				&& (mshell->expd->types[n_tp + 1][0] == SINGLE_QUOTE
				|| mshell->expd->types[n_tp + 1][0] == DOUBLE_QUOTE))
				i++;
		(*new_type)[j] = mshell->expd->types[n_tp][i];
		if (i >= ft_strlen(mshell->expd->types[n_tp]))
			break ;
		j++;
		i++;
	}
	(*new_type)[j] = '\0';
	free(mshell->expd->types[n_tp]);
	mshell->expd->types[n_tp] = (*new_type);
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
	write_heredoc_delim_oq(mshell, n_tp, &new_type);
	return (1);
}

int	center_hrdoc_delim_treatment(t_mshell *mshell, int *expander)
{
	char	*dlim;
	int		n_tp;

	n_tp = 0;
	dprintf(2, "%s\n", mshell->tkn->tkn);
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
	dprintf(2, "%s\n", dlim);
	free(mshell->tkn->tkn);
	mshell->tkn->tkn = NULL;
	mshell->tkn->tkn = dlim;
	return (1);
}
