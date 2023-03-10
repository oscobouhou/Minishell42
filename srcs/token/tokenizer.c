/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 14:43:56 by oboutarf          #+#    #+#             */
/*   Updated: 2023/02/10 14:32:26 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	make_new_token(t_mshell *mshell)
{
	mshell->tkn->next = malloc(sizeof(t_tkn));
	if (!mshell->tkn->next)
		return (0);
	mshell->tkn = mshell->tkn->next;
	mshell->tkn->pipe_fd_hrdoc[0] = -42;
	mshell->tkn->pipe_fd_hrdoc[1] = -42;
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
	if (!make_new_token(mshell))
		return (0);
	return (1);
}
