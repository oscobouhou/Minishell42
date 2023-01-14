/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 23:44:54 by oboutarf          #+#    #+#             */
/*   Updated: 2023/01/14 23:45:15 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tokens(t_mshell *mshell)
{
	t_tkn	*tmp;

	mshell->tkn = mshell->head_tkn;
	while (mshell->tkn)
	{
		free(mshell->tkn->tkn);
		tmp = mshell->tkn;
		mshell->tkn = mshell->tkn->next;
		free(tmp);
	}
}