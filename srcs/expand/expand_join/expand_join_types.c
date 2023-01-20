/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_join_types.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 00:51:34 by oboutarf          #+#    #+#             */
/*   Updated: 2023/01/21 00:56:50 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int join_types_expanded(t_mshell *mshell)
{
	char	*new_token;
	int		n_tp;
	int		i0;
	int		i1;

	n_tp = 0;
	i1 = 0;
	while (mshell->expd->types[n_tp])
	{
		i0 = 0;
		while (mshell->expd->types[n_tp][i0])
			i0++;
		i1 += i0;
		n_tp++;
	}
	n_tp = 0;
	new_token = malloc(sizeof(char) * (i1 + 1));
	if (!new_token)
		return (0);
	i1 = 0;
	while (mshell->expd->types[n_tp])
	{
		i0 = 0;
		while (mshell->expd->types[n_tp][i0])
		{
			new_token[i1] = mshell->expd->types[n_tp][i0];
			i0++;
			i1++;
		}
		n_tp++;
	}
	new_token[i1] = '\0';
	free(mshell->tkn->tkn);
	mshell->tkn->tkn = new_token;
	return (1);
}