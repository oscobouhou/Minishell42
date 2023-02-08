/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_manage_types.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 00:14:51 by oboutarf          #+#    #+#             */
/*   Updated: 2023/02/08 16:18:11 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	manage_expands_in_sq(t_mshell *mshell, int n_tp)
{
	char	*new_type;
	int		i;
	int		j;

	i = 1;
	j = 0;
	new_type = malloc(sizeof(char)
			* (ft_strlen(mshell->expd->types[n_tp]) - 2) + 1);
	if (!new_type)
		return (0);
	while (mshell->expd->types[n_tp][i] != SINGLE_QUOTE)
	{
		new_type[j] = mshell->expd->types[n_tp][i];
		j++;
		i++;
	}
	new_type[j] = '\0';
	free(mshell->expd->types[n_tp]);
	mshell->expd->types[n_tp] = new_type;
	return (1);
}

int	manage_expands_oq(t_mshell *mshell, int n_tp)
{
	int		i;

	i = 0;
	while (mshell->expd->types[n_tp][i])
	{
		if (mshell->expd->types[n_tp][i] == REDIR_L \
			&& mshell->expd->types[n_tp][i + 1] == REDIR_L)
		{
			skip_hexpander_hrdoc(mshell, n_tp, &i);
		}
		else if (mshell->expd->types[n_tp][i + 1] \
			&& mshell->expd->types[n_tp][i] == EXPAND \
			&& mshell->expd->types[n_tp][i + 1] != EXPAND)
		{
			check_update_string_with_expand(mshell, n_tp, &i);
		}
		if (i >= ft_strlen(mshell->expd->types[n_tp]))
			break ;
		else
			i++;
	}
	return (1);
}

int	sort_expander_in_dq(t_mshell *mshell, int n_tp, int *i)
{
	if (cut_expander(mshell, n_tp, *i) != -42)
		check_expander(mshell);
	treat_export_exit_status(mshell, n_tp, *i);
	if (mshell->expd->types[n_tp][*i + 1] == SINGLE_QUOTE \
		|| mshell->expd->types[n_tp][*i + 1] == DOUBLE_QUOTE)
	{
		get_all_content_from_string(mshell, n_tp);
		return (0);
	}
	update_type(mshell, i, n_tp);
	(*i)--;
	return (1);
}

int	manage_expands_in_dq(t_mshell *mshell, int n_tp)
{
	int	i;

	i = 1;
	if (mshell->expd->types[n_tp][i] == EXPAND \
		&& mshell->expd->types[n_tp][i + 1] == DOUBLE_QUOTE)
	{
		single_dollar_in_dq(mshell, n_tp);
		return (1);
	}
	while (mshell->expd->types[n_tp][i])
	{
		if (n_tp > 0)
			if (hrdoc_scannner(mshell, n_tp))
				break ;
		if (mshell->expd->types[n_tp][i] == EXPAND \
		&& mshell->expd->types[n_tp][i + 1] \
		&& mshell->expd->types[n_tp][i + 1] != EXPAND)
		{
			if (!sort_expander_in_dq(mshell, n_tp, &i))
				break ;
		}
		i++;
	}
	return (1);
}

int	manage_expands_in_types(t_mshell *mshell)
{
	int	n_tp;
	int	dcrm;

	n_tp = 0;
	dcrm = mshell->expd->n_types;
	while (dcrm-- > 0)
	{
		if (mshell->expd->types[n_tp][0] == SINGLE_QUOTE)
			manage_expands_in_sq(mshell, n_tp);
		else if (mshell->expd->types[n_tp][0] == DOUBLE_QUOTE)
			manage_expands_in_dq(mshell, n_tp);
		else if (mshell->expd->types[n_tp][0] != SINGLE_QUOTE \
			&& mshell->expd->types[n_tp][0] != DOUBLE_QUOTE)
			manage_expands_oq(mshell, n_tp);
		n_tp++;
	}
	return (1);
}
