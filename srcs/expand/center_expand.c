/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   center_expand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 22:46:34 by oboutarf          #+#    #+#             */
/*   Updated: 2023/01/16 13:12:43 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	center_expand(t_mshell *mshell)
{
	mshell->tkn = mshell->head_tkn;
	if (!check_expand_in_token(mshell))
		return (0);
	mshell->tkn = mshell->head_tkn;
	return (1);
}
