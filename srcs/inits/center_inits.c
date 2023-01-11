/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   center_inits.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 16:42:16 by oboutarf          #+#    #+#             */
/*   Updated: 2023/01/10 18:37:30 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	center_init(t_mshell *mshell)
{
	if (!mshell)
		return (0);
	mshell->tkn = init_tokens(mshell);
	if (!mshell->tkn)
		return (0);
	return (1);
}