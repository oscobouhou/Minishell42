/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_cut.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 00:47:33 by oboutarf          #+#    #+#             */
/*   Updated: 2023/02/04 14:00:05 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cut_expander(t_mshell *mshell, int n_tp, int i)
{
	int	tmp_i;
	int	j;

	j = 0;
	i += 1;
	tmp_i = i;
	if (mshell->expd->expander)
		free(mshell->expd->expander);
	while (mshell->expd->types[n_tp][i] && mshell->expd->types[n_tp][i] != SINGLE_QUOTE
		&& mshell->expd->types[n_tp][i] != DOUBLE_QUOTE && mshell->expd->types[n_tp][i] != EXPAND
			&& mshell->expd->types[n_tp][i] != BACKSLSH)
		i++;
	mshell->expd->expander = malloc(sizeof(char) * ((i - tmp_i) + 1));
	if (!mshell->expd->expander)
		return (0);
	i = tmp_i;
	while (mshell->expd->types[n_tp][i] && mshell->expd->types[n_tp][i] != SINGLE_QUOTE
		&& mshell->expd->types[n_tp][i] != DOUBLE_QUOTE && mshell->expd->types[n_tp][i] != EXPAND
			&& mshell->expd->types[n_tp][i] != BACKSLSH)
	{
		mshell->expd->expander[j] = mshell->expd->types[n_tp][i];
		j++;
		i++;
	}
	mshell->expd->expander[j] = '\0';
	return (1);
}
