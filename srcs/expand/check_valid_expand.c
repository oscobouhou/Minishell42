/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valid_expand.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 20:44:09 by oboutarf          #+#    #+#             */
/*   Updated: 2023/01/18 22:32:35 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_valid_expand(t_mshell *mshell, int *i)
{
	char	*expander;
	int		tmp_i[2];
	int		j;

	if (!mshell->tkn->tkn[*i + 1])
		return (1);
	tmp_i[0] = *i;
	while (mshell->tkn->tkn[++(*i)] && mshell->tkn->tkn[*i] != EXPAND)
	{
		if (mshell->tkn->tkn[*i] == SINGLE_QUOTE || mshell->tkn->tkn[*i] == DOUBLE_QUOTE)
			break ;
	}
	expander = malloc(sizeof(char) * ((*i) - tmp_i[0]) + 1);
	if (!expander)
		return (0);
	tmp_i[1] = *i;
	*i = tmp_i[0];
	j = -1;
	while (++(*i) < tmp_i[1])
		expander[++j] = mshell->tkn->tkn[*i];
	expander[++j] = '\0';
	dprintf(2, "%s\n", expander);
	if (!search_expand_in_export(mshell, expander))
		return (*i = tmp_i[0], free(expander), suppress_expand(mshell, tmp_i[0], ((tmp_i[1] - tmp_i[0]))), 1);
	make_expand(mshell, expander, ((tmp_i[1] - tmp_i[0])));
	free(expander);
	return (1);
}