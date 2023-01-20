/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 00:52:19 by oboutarf          #+#    #+#             */
/*   Updated: 2023/01/21 00:52:46 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_expander(t_mshell *mshell)
{
	t_expt	*head;

	head = mshell->expt;
	mshell->expd->old_expd_len = ft_strlen(mshell->expd->expander);
	while (mshell->expt->next)
	{
		if (!ft_strcmp(mshell->expd->expander, mshell->expt->exptvar))
		{
			make_expansion(mshell, mshell->expt->value);
			mshell->expd->new_expd_len = ft_strlen(mshell->expd->expander);
			mshell->expt = head;
			return (1);
		}
		mshell->expt = mshell->expt->next;
	}
	mshell->expd->expander = NULL;
	mshell->expd->new_expd_len = ft_strlen(mshell->expd->expander);
	mshell->expt = head;
	return (1);
}
