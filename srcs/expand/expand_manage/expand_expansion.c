/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_expansion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 00:48:52 by oboutarf          #+#    #+#             */
/*   Updated: 2023/02/04 14:04:05 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	make_expansion(t_mshell *mshell, char *input)
{
	int	i;

	i = 0;
	if (mshell->expd->expander)
		free(mshell->expd->expander);
	mshell->expd->expander = malloc(sizeof(char) * (ft_strlen(input) + 1));
	if (!mshell->expd->expander)
		return (0);
	while (input[i])
	{
		mshell->expd->expander[i] = input[i];
		i++;
	}
	mshell->expd->expander[i] = '\0';
	return (1);	
}
