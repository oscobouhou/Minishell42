/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 12:47:49 by oboutarf          #+#    #+#             */
/*   Updated: 2023/02/08 12:48:21 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	skip_hexpander_hrdoc(t_mshell *mshell, int n_tp, int *i)
{
	int	tmp_i;

	(*i)++;
	(*i)++;
	while (mshell->expd->types[n_tp][*i] \
	&& ((mshell->expd->types[n_tp][*i] >= 9 \
	&& mshell->expd->types[n_tp][*i] <= 13) \
	|| (mshell->expd->types[n_tp][*i] == 32)))
		(*i)++;
	tmp_i = 0;
	while (mshell->expd->types[n_tp][*i] && \
		check_printable_char(mshell->expd->types[n_tp][*i]))
		(*i)++;
	return (*i - tmp_i);
}

int	treat_export_exit_status(t_mshell *mshell, int n_tp, int i)
{
	if (mshell->expd->types[n_tp][i + 1] == '?')
	{
		if (mshell->expd->expander)
		{
			free(mshell->expd->expander);
			mshell->expd->expander = NULL;
		}
		mshell->expd->expander = ft_itoa(mshell->exit_status);
		mshell->expd->old_expd_len = 1;
		mshell->expd->new_expd_len = ft_strlen(mshell->expd->expander);
	}
	return (1);
}

int	check_update_string_with_expand(t_mshell *mshell, int n_tp, int *i)
{
	if (mshell->expd->types[n_tp][*i + 1] \
		&& mshell->expd->types[n_tp][*i + 1] != '?')
	{
		if (cut_expander(mshell, n_tp, *i) != -42)
			check_expander(mshell);
		update_type(mshell, i, n_tp);
		(*i)--;
	}
	else
	{
		treat_export_exit_status(mshell, n_tp, *i);
		update_type(mshell, i, n_tp);
		if (mshell->expd->expander)
		{
			free(mshell->expd->expander);
			mshell->expd->expander = NULL;
		}
		(*i)--;
	}
	return (1);
}
