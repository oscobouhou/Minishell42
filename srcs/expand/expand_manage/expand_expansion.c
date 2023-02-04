/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_expansion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 00:48:52 by oboutarf          #+#    #+#             */
/*   Updated: 2023/02/04 18:48:23 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	make_expansion(t_mshell *mshell, char *input)
{
	int	len;
	int	i;

	i = 0;
	len = ft_strlen(input);
	if (mshell->expd->expander)
		free(mshell->expd->expander);
	if (!len)
		return (0);
	mshell->expd->expander = malloc(sizeof(char) * (len + 1));
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
