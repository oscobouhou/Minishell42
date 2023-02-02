/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 17:34:55 by oboutarf          #+#    #+#             */
/*   Updated: 2023/02/02 20:56:30 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redir_tokenizer_in(t_mshell *mshell, int *i, int tmp_i)
{
	++(*i);
	mshell->tkn->type = HRDOC;
	if (!tokenizer(mshell, tmp_i, *i))
		return (0);
	return (1);
}

int	redir_tokenizer_out(t_mshell *mshell, int *i, int tmp_i)
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
	if (!tokenizer(mshell, tmp_i, *i))
		return (0);
	return (1);
}

int	treat_redir(t_mshell *mshell, int *i)
{
	int	tmp_i;

	tmp_i = *i;
	if (mshell->rdline_outp[*i] == REDIR_R)
	{
		if (!redir_tokenizer_out(mshell, i, tmp_i))
			return (0);
		return (1);
	}
	++(*i);
	if (mshell->rdline_outp[*i] == REDIR_L)
	{
		if (!redir_tokenizer_in(mshell, i, tmp_i))
			return (0);
		return (1);
	}
	mshell->tkn->type = RDIR_L;
	if (!tokenizer(mshell, tmp_i, *i))
		return (0);
	return (1);
}




/* int	treat_redir(t_mshell *mshell, int *i)
{
	int	tmp_i;

	tmp_i = *i;
	if (mshell->rdline_outp[*i] == REDIR_R)
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
 */

// int	treat_redir(t_mshell *mshell, int *i)
// {
// 	int	tmp_i;

// 	tmp_i = *i;
// 	if (mshell->rdline_outp[*i] == REDIR_R)
// 	{
// 		++(*i);
// 		if (mshell->rdline_outp[*i] == REDIR_R)
// 		{	
// 			++(*i);
// 			mshell->tkn->type = APPEND;
// 			if (!tokenizer(mshell, tmp_i, *i))
// 				return (0);
// 			return (1);
// 		}
// 		mshell->tkn->type = RDIR_R;
// 		if (!tokenizer(mshell, tmp_i, *i))
// 			return (0);
// 		return (1);
// 	}
// 	++(*i);
// 	if (mshell->rdline_outp[*i] == REDIR_L)
// 	{
// 		++(*i);
// 		mshell->tkn->type = HRDOC;
// 		if (!tokenizer(mshell, tmp_i, *i))
// 			return (0);
// 		return (1);
// 	}
// 	mshell->tkn->type = RDIR_L;
// 	if (!tokenizer(mshell, tmp_i, *i))
// 		return (0);
// 	return (1);
// }
