/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_in_hrdoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 12:22:43 by oboutarf          #+#    #+#             */
/*   Updated: 2023/01/18 21:57:21 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	make_new_delim_hrdoc(t_mshell *mshell, int len)
{
	char	*new_delim;
	int		qut[2];
	int		j;
	int		i;

	i = -1;
	j = -1;
	qut[0] = 0;
	qut[1] = 0;
	new_delim = malloc(sizeof(char) * len);
	if (!new_delim)
		return (0);
	while (mshell->tkn->tkn[++i])
	{
		if (mshell->tkn->tkn[i] == SINGLE_QUOTE)
			qut[0]++;
		if (mshell->tkn->tkn[i] == DOUBLE_QUOTE)
			qut[1]++;
		if (mshell->tkn->tkn[i] == EXPAND && qut[0] % 2 == 0 && qut[1] % 2 == 0
			&& ((mshell->tkn->tkn[i + 1] == SINGLE_QUOTE) || (mshell->tkn->tkn[i + 1] == DOUBLE_QUOTE)))
			++i;
		new_delim[++j] = mshell->tkn->tkn[i];
	}
	new_delim[++j] = '\0';
	free(mshell->tkn->tkn);
	mshell->tkn->tkn = new_delim;
	return (1);		
}

int	treat_expd_hrdoc(t_mshell *mshell)
{
	int		qut[2];
	int		cnt;
	int		i;

	i = -1;
	cnt = 0;
	qut[0] = 0;
	qut[1] = 0;
	while (mshell->tkn->tkn[++i])
	{
		if (mshell->tkn->tkn[i] == SINGLE_QUOTE)
			qut[0]++;
		if (mshell->tkn->tkn[i] == DOUBLE_QUOTE)
			qut[1]++;
		if (mshell->tkn->tkn[i] == EXPAND && qut[0] % 2 == 0 && qut[1] % 2 == 0
			&& ((mshell->tkn->tkn[i + 1] == SINGLE_QUOTE) || (mshell->tkn->tkn[i + 1] == DOUBLE_QUOTE)))
			++i;
		cnt++;
	}
	if (!make_new_delim_hrdoc(mshell, cnt + 1))
		return (0);
	return (1);
}