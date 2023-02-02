/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs_review.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 14:04:59 by oboutarf          #+#    #+#             */
/*   Updated: 2023/02/02 11:29:57 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirs_review(t_mshell *mshell)
{
	if (mshell->tkn->type == RDIR_L \
	|| mshell->tkn->type == RDIR_R \
	|| mshell->tkn->type == APPEND)
	{
		if (!type_next_token(mshell->tkn, _FILE))
			return (0);
	}
	return (1);
}
