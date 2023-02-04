/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 00:50:18 by oboutarf          #+#    #+#             */
/*   Updated: 2023/02/03 21:11:46 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	remove_closing_quotes_dq(t_mshell *mshell, int n_tp)
{
	char	*quote_remover;
	int		i0;
	int		i1;

	i0 = 1;
	i1 = 0;
	quote_remover = malloc(sizeof(char) * ft_strlen(mshell->expd->types[n_tp]) + 1);
	while (mshell->expd->types[n_tp][i0] != DOUBLE_QUOTE)
	{
		quote_remover[i1] = mshell->expd->types[n_tp][i0];
		i1++;
		i0++;
	}
	quote_remover[i1] = '\0';
	free(mshell->expd->types[n_tp]);
	mshell->expd->types[n_tp] = quote_remover;
	return (1);
}
