/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_manage_types.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oscobou <oscobou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 00:14:51 by oboutarf          #+#    #+#             */
/*   Updated: 2023/01/23 15:01:15 by oscobou          ###   ########.fr       */
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
	new_type = malloc(sizeof(char) * (ft_strlen(mshell->expd->types[n_tp]) - 2) + 1);
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
		if (mshell->expd->types[n_tp][i] == EXPAND)
		{
			cut_expander(mshell, n_tp, i);
			check_expander(mshell);
			if (!mshell->expd->types[n_tp][i + 1] && !mshell->expd->types[n_tp + 1])
			{
				mshell->expd->old_expd_len = 1;
				mshell->expd->new_expd_len = 1;
				mshell->expd->expander = "$";
			}
			update_type(mshell, &i, n_tp);
			i -= 1;
		}
		i++;
	}
	return (1);
}


int	get_all_content_from_string(t_mshell *mshell, int n_tp)
{
	char 	*new_type;
	int		i;

	i = ft_strlen(mshell->expd->types[n_tp]);
	new_type = malloc(sizeof(char) * (i + 1));
	if (!new_type)
		return (0);
	i = 0;
	while (mshell->expd->types[n_tp][i])
	{
		new_type[i] = mshell->expd->types[n_tp][i];
		i++;	
	}
	new_type[i] = '\0';
	free(mshell->expd->types[n_tp]);
	mshell->expd->types[n_tp] = new_type;
	return (1);
}

int	manage_expands_in_dq(t_mshell *mshell, int n_tp)
{
	int	i;

	i = 1;
	if (mshell->expd->types[n_tp][i] == EXPAND && mshell->expd->types[n_tp][i + 1] == DOUBLE_QUOTE)
	{
		free(mshell->expd->types[n_tp]);
		mshell->expd->types[n_tp] = "$\0";
		return (1);
	}
	while (mshell->expd->types[n_tp][i])
	{
		if (mshell->expd->types[n_tp][i] == EXPAND)
		{
			cut_expander(mshell, n_tp, i);
			check_expander(mshell);
			if (mshell->expd->types[n_tp][i + 1] == SINGLE_QUOTE || mshell->expd->types[n_tp][i + 1] == DOUBLE_QUOTE)
			{
				get_all_content_from_string(mshell, n_tp);
				break ;
			}
			update_type(mshell, &i, n_tp);
			i -= 1;
		}
		i++;
	}
	dprintf(2, "%s\n", mshell->expd->types[n_tp]);
	remove_closing_quotes_dq(mshell, n_tp);
	return (1);
}

int	manage_expands_in_types(t_mshell *mshell)
{
	int	n_tp;

	n_tp = 0;
	while (mshell->expd->types[n_tp])
	{
		if (mshell->expd->types[n_tp][0] == SINGLE_QUOTE)
			manage_expands_in_sq(mshell, n_tp);
		else if (mshell->expd->types[n_tp][0] == DOUBLE_QUOTE)
			manage_expands_in_dq(mshell, n_tp);
		else if (mshell->expd->types[n_tp][0] != SINGLE_QUOTE && mshell->expd->types[n_tp][0] != DOUBLE_QUOTE)
			manage_expands_oq(mshell, n_tp);
		n_tp++;
	}
	return (1);
}
