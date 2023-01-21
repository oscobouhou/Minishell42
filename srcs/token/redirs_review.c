/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs_review.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkermia <dkermia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 14:04:59 by oboutarf          #+#    #+#             */
/*   Updated: 2023/01/21 15:36:13 by dkermia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirs_review(t_mshell *mshell)
{
	if (mshell->tkn->type == RDIR_L \
	|| mshell->tkn->type == RDIR_R \
	|| mshell->tkn->type == APPEND)
		if (!type_next_token(mshell->tkn, _FILE))
			return (0);
    return (1);
	
}
