/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_expands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 13:12:54 by oboutarf          #+#    #+#             */
/*   Updated: 2023/01/15 16:36:39 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_end_var_expand(int read)
{
	if (read == SINGLE_QUOTE || read == DOUBLE_QUOTE)
		return (0);
	if (read == REDIR_R || read == REDIR_L)
		return (0);
	if (read == PIPE_LINE)
		return (0);
	if (read == EXPAND)
		return (0);
	if ((read >= 9 && read <= 13) || read == 32)
		return (0);
	return (1);
}

int	manage_expands(t_mshell *mshell, int *i)
{
	char	*expander;
	int 	strt;
	int		j;

	if (!mshell->tkn->tkn[*i + 1])
		return (0);
	strt = (*i + 1);
	while (mshell->tkn->tkn[++(*i)])
	{
		if (!check_end_var_expand(mshell->tkn->tkn[(*i)]))
			break ;
	}
	expander = malloc(sizeof(char) * ((*i - strt) + 1));
	j = -1;
	strt -= 1;
	while (++strt < (*i))
		expander[++j] = mshell->tkn->tkn[strt];
	*i -= 1;
	expander[++j] = '\0';
	if (!export_seeker(mshell, &expander))
		return (0);
	free(expander);
	return (1);
}
