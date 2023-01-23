/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hrdoc_review.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oscobou <oscobou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 14:03:56 by oboutarf          #+#    #+#             */
/*   Updated: 2023/01/23 15:46:25 by oscobou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	hrdoc_review(t_mshell *mshell, int *cmd_cnt)
{
	if (mshell->tkn->type == HRDOC)
	{
		if (!type_next_token(mshell->tkn, DLIM_HRDOC))
			return (0);
		mshell->tkn = mshell->tkn->next;
		center_hrdoc_delim_treatment(mshell);
		if (mshell->tkn->next->tkn && mshell->tkn->next->type == WORD && *cmd_cnt == 0)
			return (mshell->tkn->next->type = _CMD, *cmd_cnt += 1, 1);
	}
	return (1);
}
