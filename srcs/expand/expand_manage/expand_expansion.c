/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_expansion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 00:48:52 by oboutarf          #+#    #+#             */
/*   Updated: 2023/02/03 18:24:43 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	make_expansion(t_mshell *mshell, char *input)
{
	int	i;

	i = 0;
	mshell->expd->expander = malloc(sizeof(char) * (ft_strlen(input) + 1));
	if (!mshell->expd->expander)
		return (0);
	while (input[i])
	{
		dprintf(2, "||:%s\n", mshell->rdline_outp);
		mshell->expd->expander[i] = input[i];
		i++;
	}
	mshell->expd->expander[i] = '\0';
	return (1);	
}
