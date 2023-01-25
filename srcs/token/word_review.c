/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_review.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 14:02:28 by oboutarf          #+#    #+#             */
/*   Updated: 2023/01/25 03:14:16 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	word_review(t_mshell *mshell, int *cmd_cnt)
{
	if (mshell->tkn->type == WORD)
	{
		if (mshell->tkn == mshell->head_tkn || *cmd_cnt == 0)
		{
			mshell->tkn->type = _CMD;
			*cmd_cnt = 1;
		}
		else
			mshell->tkn->type = _ARG;
	}
}
