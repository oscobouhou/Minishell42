/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_join_types.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 00:51:34 by oboutarf          #+#    #+#             */
/*   Updated: 2023/02/04 18:21:46 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	alloc_new_token_for_join(t_mshell *mshell, int *i0, int *n_tp, int *i1)
{
	int	dcrm;

	dcrm = mshell->expd->n_types;
	while (dcrm-- > 0)
	{
		*i0 = 0;
		while (mshell->expd->types[*n_tp][*i0])
			(*i0)++;
		*i1 += *i0;
		(*n_tp)++;
	}
	return (1);
}

char	*join_types_expanded(t_mshell *mshell)
{
	char	*new_token;
	int		n_tp;
	int		i0;
	int		i1;

	n_tp = 0;
	i1 = 0;
	alloc_new_token_for_join(mshell, &i0, &n_tp, &i1);
	n_tp = 0;
	new_token = malloc(sizeof(char) * (i1 + 1));
	if (!new_token)
		return (NULL);
	i1 = 0;
	while (mshell->expd->n_types-- > 0)
	{
		i0 = 0;
		while (mshell->expd->types[n_tp][i0])
		{
			new_token[i1] = mshell->expd->types[n_tp][i0];
			i0++;
			i1++;
		}
		free(mshell->expd->types[n_tp]);
		n_tp++;
	}
	if (mshell->expd->types[n_tp])
		free(mshell->expd->types[n_tp]);
	new_token[i1] = '\0';
	free(mshell->expd->types);
	mshell->expd->types = NULL;
	return (new_token);
}
