/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_expand.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 20:37:17 by oboutarf          #+#    #+#             */
/*   Updated: 2023/01/17 20:55:02 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	make_expand(t_mshell *mshell, char *expander, int len)
{
	char	*new_token;
	int 	temp_i;
	int		i;
	int		j;


	while (ft_strcmp(mshell->expt->exptvar, expander))
		mshell->expt = mshell->expt->next;
	new_token = malloc(sizeof(char) * ((ft_strlen(mshell->tkn->tkn) - len) + ft_strlen(mshell->expt->value)));
	if (!new_token)
		return (0);
	i = -1;
	while (mshell->tkn->tkn[++i] && mshell->tkn->tkn[i] != EXPAND)
		new_token[i] = mshell->tkn->tkn[i];
	i -= 1;
	j = 0;
	temp_i = (i + (ft_strlen(expander) + 1));
	while (mshell->expt->value[++j])
		new_token[++i] = mshell->expt->value[j];
	while (mshell->tkn->tkn[++temp_i] && mshell->tkn->tkn[i] != EXPAND)
		new_token[++i] = mshell->tkn->tkn[temp_i];
	new_token[++i] = '\0';
	free(mshell->tkn->tkn);
	mshell->tkn->tkn = new_token;
	(void)len;
	return (1);
}
