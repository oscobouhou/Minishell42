/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   suppress_expand.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 20:38:14 by oboutarf          #+#    #+#             */
/*   Updated: 2023/01/18 22:31:22 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	suppress_expand(t_mshell *mshell, int start, int len)
{
	char	*new_token;
	int		i;
	int		j;
	int		r;

	new_token = malloc(sizeof(char) * ((ft_strlen(mshell->tkn->tkn) - len) + 1));
	if (!new_token)
		return (0);
	i = -1;
	r = -1;
	j = ((start + len) - 1);
	while (mshell->tkn->tkn[++r] && mshell->tkn->tkn[r] != EXPAND)
		new_token[++i] = mshell->tkn->tkn[r];
	while (mshell->tkn->tkn[++j])
		new_token[++i] = mshell->tkn->tkn[j];
	new_token[++i] = '\0';
	free(mshell->tkn->tkn);
	mshell->tkn->tkn = new_token;
	return (1);
}
