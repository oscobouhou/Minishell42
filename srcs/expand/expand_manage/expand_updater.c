/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_updater.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 12:55:09 by oboutarf          #+#    #+#             */
/*   Updated: 2023/02/08 16:12:18 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	update_type_no_expand(t_mshell *mshell, int *ptr, int n_tp, char **update)
{
	(*update) = malloc(sizeof(char) * (ptr[0] + 1));
	if (!(*update))
		return (0);
	ptr[0] = 0;
	while (ptr[0] < ptr[2])
	{
		(*update)[ptr[0]] = mshell->expd->types[n_tp][ptr[0]];
		ptr[0]++;
	}
	ptr[2] = ptr[0];
	ptr[1] = ptr[0];
	ptr[0] += mshell->expd->old_expd_len + 1;
	while (mshell->expd->types[n_tp][ptr[0]])
	{
		(*update)[ptr[1]] = mshell->expd->types[n_tp][ptr[0]];
		ptr[0]++;
		ptr[1]++;
	}
	(*update)[ptr[1]] = '\0';
	free(mshell->expd->types[n_tp]);
	mshell->expd->types[n_tp] = (*update);
	return (1);
}

int	close_string_after_expand_update(t_mshell *mshell, \
	int *ptr, char **update, int n_tp)
{
	while (mshell->expd->types[n_tp][ptr[2]])
	{
		(*update)[ptr[0]] = mshell->expd->types[n_tp][ptr[2]];
		ptr[0]++;
		ptr[2]++;
	}
	(*update)[ptr[0]] = '\0';
	free(mshell->expd->types[n_tp]);
	mshell->expd->types[n_tp] = (*update);
	return (1);
}

int	update_type_expanded(t_mshell *mshell, int *ptr, int n_tp, char **update)
{
	ptr[0] += mshell->expd->new_expd_len;
	(*update) = malloc(sizeof(char) * (ptr[0]) + 1);
	if (!(*update))
		return (0);
	ptr[0] = 0;
	while (ptr[0] < ptr[3])
	{
		(*update)[ptr[0]] = mshell->expd->types[n_tp][ptr[0]];
		ptr[0]++;
	}
	ptr[1] = 0;
	ptr[2] = ptr[0] + mshell->expd->old_expd_len + 1;
	while (mshell->expd->expander[ptr[1]])
	{
		(*update)[ptr[0]] = mshell->expd->expander[ptr[1]];
		ptr[0]++;
		ptr[1]++;
	}
	free(mshell->expd->expander);
	ptr[3] = ptr[0];
	mshell->expd->expander = NULL;
	close_string_after_expand_update(mshell, ptr, update, n_tp);
	return (ptr[3]);
}

int	update_type(t_mshell *mshell, int *i, int n_tp)
{
	char	*update;
	int		ptr[4];

	ptr[0] = ft_strlen(mshell->expd->types[n_tp]) \
		- mshell->expd->old_expd_len + 1;
	if (!mshell->expd->expander)
	{
		ptr[2] = *i;
		update_type_no_expand(mshell, ptr, n_tp, &update);
	}
	else
	{
		ptr[3] = *i;
		*i = update_type_expanded(mshell, ptr, n_tp, &update);
	}
	return (1);
}
