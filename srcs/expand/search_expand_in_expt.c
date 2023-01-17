/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_expand_in_export.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 20:40:25 by oboutarf          #+#    #+#             */
/*   Updated: 2023/01/17 20:40:48 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	search_expand_in_export(t_mshell *mshell, char *expander)
{
	t_expt	*head;

	head = mshell->expt;
	while (mshell->expt->next)
	{
		if (!ft_strcmp(mshell->expt->exptvar, expander))
			return (mshell->expt = head, 1);
		mshell->expt = mshell->expt->next;
	}
	return (mshell->expt = head, 0);
}
