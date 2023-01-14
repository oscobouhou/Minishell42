/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compose_tkn.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 15:32:02 by oboutarf          #+#    #+#             */
/*   Updated: 2023/01/14 23:51:23 by oboutarf         ###   ########.fr       */
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
	dprintf(2, "%d \n", mshell->tkn->type);
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
	dprintf(2, "|%s|\n", expander);
	free(expander);
	return (1);
}

int	check_expand_in_token(t_mshell *mshell)
{
	int	i;

	while (mshell->tkn->next)
	{
		i = -1;
		if (mshell->tkn->type != SQ_WORD)
			while (mshell->tkn->tkn[++i])
				if (mshell->tkn->tkn[i] == EXPAND)
					if (!manage_expands(mshell, &i))
						break ;
		mshell->tkn = mshell->tkn->next;
	}
	return (1);
}

int	compose_tkn(t_mshell *mshell)
{
	mshell->tkn = mshell->head_tkn;
	if (!check_expand_in_token(mshell))
		return (0);
	return (1);
}
