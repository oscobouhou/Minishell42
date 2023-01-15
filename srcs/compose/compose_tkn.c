/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compose_tkn.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 15:32:02 by oboutarf          #+#    #+#             */
/*   Updated: 2023/01/15 17:07:11 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	compose_tkn(t_mshell *mshell)
{
	mshell->tkn = mshell->head_tkn;
	if (!center_expand(mshell))
		return (0);
	return (1);
}
