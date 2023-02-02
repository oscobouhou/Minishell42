/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 17:34:55 by oboutarf          #+#    #+#             */
/*   Updated: 2023/02/02 11:38:14 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	treat_redir_r(t_mshell *mshell, int tmp_i, int *i)
{
	++(*i);
	if (mshell->rdline_outp[*i] == REDIR_R)
	{
		++(*i);
		mshell->tkn->type = APPEND;
		if (!tokenizer(mshell, tmp_i, *i))
			return (0);
		return (1);
	}
	mshell->tkn->type = RDIR_R;
	return (1);
}

int	treat_redir(t_mshell *mshell, int *i)
{
	int	tmp_i;

	tmp_i = *i;
	if (mshell->rdline_outp[*i] == REDIR_R)
	{
		if (!treat_redir_r(mshell, tmp_i, i))
			return (0);
		if (!tokenizer(mshell, tmp_i, *i))
			return (0);
		return (1);
	}
	++(*i);
	if (mshell->rdline_outp[*i] == REDIR_L)
	{
		++(*i);
		mshell->tkn->type = HRDOC;
		if (!tokenizer(mshell, tmp_i, *i))
			return (0);
		return (1);
	}
	mshell->tkn->type = RDIR_L;
	if (!tokenizer(mshell, tmp_i, *i))
		return (0);
	return (1);
}
