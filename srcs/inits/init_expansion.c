/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_expansion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 11:58:51 by oboutarf          #+#    #+#             */
/*   Updated: 2023/01/20 18:03:38 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_expansion(t_mshell *mshell)
{
	mshell->expd = malloc(sizeof(t_expd));
	if (!mshell->expd)
		return (0);
	mshell->expd->n_types = 0;
	mshell->expd->old_expd_len = 0;
	mshell->expd->new_expd_len = 0;
	mshell->expd->types = NULL;
	mshell->expd->expander = NULL;
	mshell->expd->update_tkn = NULL;
	return (1);
}