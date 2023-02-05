/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_cut.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 00:47:33 by oboutarf          #+#    #+#             */
/*   Updated: 2023/02/05 07:53:34 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	write_expander_after_cut(t_mshell *mshell, int tmp_i, int n_tp, int i)
{
	int	j;

	j = 0;
	i = tmp_i;
	while (mshell->expd->types[n_tp][i] \
		&& mshell->expd->types[n_tp][i] != SINGLE_QUOTE \
		&& mshell->expd->types[n_tp][i] != DOUBLE_QUOTE \
		&& mshell->expd->types[n_tp][i] != EXPAND \
			&& mshell->expd->types[n_tp][i] != BACKSLSH)
	{
		mshell->expd->expander[j] = mshell->expd->types[n_tp][i];
		j++;
		i++;
	}
	mshell->expd->expander[j] = '\0';
}

int	cut_expander(t_mshell *mshell, int n_tp, int i)
{
	int	tmp_i;

	i += 1;
	tmp_i = i;
	while (mshell->expd->types[n_tp][i] \
		&& mshell->expd->types[n_tp][i] != SINGLE_QUOTE \
		&& mshell->expd->types[n_tp][i] != DOUBLE_QUOTE \
		&& mshell->expd->types[n_tp][i] != EXPAND \
			&& mshell->expd->types[n_tp][i] != BACKSLSH)
		i++;
	if (i == tmp_i)
		return (-42);
	mshell->expd->expander = malloc(sizeof(char) * ((i - tmp_i) + 1));
	if (!mshell->expd->expander)
		return (0);
	write_expander_after_cut(mshell, tmp_i, n_tp, i);
	return (1);
}
