/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 19:23:26 by oboutarf          #+#    #+#             */
/*   Updated: 2023/01/14 19:25:09 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	new_node_export(t_mshell *mshell)
{
	mshell->expt->next = malloc(sizeof(t_expt));
	if (!mshell->expt->next)
		return (0);
	mshell->expt = mshell->expt->next;
	mshell->expt->exptvar = NULL;
	mshell->expt->value = NULL;
	mshell->expt->next = NULL;
	return (1);
}

int	init_sort_export(t_mshell *mshell)
{
	mshell->expt = malloc(sizeof(t_expt));
	if (!mshell->expt)
		return (0);
	mshell->expt->value = NULL;
	mshell->expt->exptvar = NULL;
	mshell->expt->next = NULL;
	return (1);
}