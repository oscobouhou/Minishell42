/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   center_expand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 22:46:34 by oboutarf          #+#    #+#             */
/*   Updated: 2023/01/19 03:13:53 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	expansion_of_expander_out_qut(t_mshell *mshell, int *i)
{
	(void)mshell;
	(void)*i;
	return (1);	
}

int	expansion_of_expander_in_s_qut(t_mshell *mshell, int *i)
{
	(void)mshell;
	(void)*i;
	return (1);	
}

int	expansion_of_expander_in_d_qut(t_mshell *mshell, int *i)
{
	(void)mshell;
	(void)*i;
	return (1);	
}

int	expand_checker(t_mshell *mshell)
{
	int		qut[2];
	int     i[2];

	i[1] = 0;
	i[0] = -1;
	qut[0] = 0;
	qut[1] = 0;
	while (mshell->tkn->tkn[++i[0]])
	{
		if (mshell->tkn->tkn[i[0]] == SINGLE_QUOTE)
			qut[0] += 1;
		if (mshell->tkn->tkn[i[0]] == DOUBLE_QUOTE)
			qut[1] += 1;
		if (qut[1] % 2 == 0 && qut[0] % 2 != 0)
		{
			dprintf(2, "COUCOU\n");
			expansion_of_expander_in_s_qut(mshell, i);
		}
		else if ((qut[1] % 2 != 0) && (qut[0] % 2 == 0))
		{
			dprintf(2, "COUCOU1\n");
			expansion_of_expander_in_d_qut(mshell, i);
		}
		else if ((qut[1] % 2 == 0) && (qut[0] % 2 == 0) && !mshell->tkn->tkn[i[0] + 1])
			break ;
		else if ((qut[1] % 2 == 0) && (qut[0] % 2 == 0))
		{
			dprintf(2, "COUCOU2\n");
			expansion_of_expander_out_qut(mshell, i);
		}
	}
	return (1);
}

int	center_expand(t_mshell *mshell)
{
	mshell->tkn = mshell->head_tkn;
	while (mshell->tkn->next)
	{
		if (mshell->tkn->type == _CMD || mshell->tkn->type == _ARG || mshell->tkn->type == _FILE)
			expand_checker(mshell);
		mshell->tkn = mshell->tkn->next;
	}
	return (1);
}
