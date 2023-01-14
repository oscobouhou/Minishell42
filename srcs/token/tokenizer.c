/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 14:43:56 by oboutarf          #+#    #+#             */
/*   Updated: 2023/01/14 15:12:50 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	make_new_token(t_mshell *mshell)
{
	mshell->tkn->next = malloc(sizeof(t_tkn));
	if (!mshell->tkn->next)
		return (0);
	mshell->tkn = mshell->tkn->next;
	mshell->tkn->tkn = NULL;
	mshell->tkn->type = -1;
	mshell->tkn->next = NULL;
	return (1);
}

int	tokenizer(t_mshell *mshell, int strt, int end)
{
	int	i;

	i = -1;
	mshell->tkn->tkn = malloc(sizeof(char) * ((end - strt) + 1));
	if (!mshell->tkn->tkn)
		return (0);
	while (strt < end)
	{
		mshell->tkn->tkn[++i] = mshell->rdline_outp[strt];
		strt++;
	}
	mshell->tkn->tkn[++i] = '\0';
	dprintf(2, "%s\n  type:  %d\n", mshell->tkn->tkn, mshell->tkn->type);
	if (!make_new_token(mshell))
		return (0);
	return (1);
}

//string = input

//parsing de la string

//split au pipe

//expand

//split au espaces

//ls | grep -e 'minishell' | cat

/*
	int i = 0;
	while (list) {
		if (i == 0 && list != redirection)
			list = cmd;
			i++;
		else if (i != 0 && list !+ redirection)
			list = option / arguments
		else
			list = redirection
	}
*/