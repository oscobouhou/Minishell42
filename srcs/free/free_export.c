/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_sort_export.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 19:29:41 by oboutarf          #+#    #+#             */
/*   Updated: 2023/01/14 23:42:00 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_actualise(t_env *actualise)
{
	free(actualise->value);
	free(actualise->envar);
	free(actualise->next);
	free(actualise);
}

void	free_exprt(t_mshell *mshell)
{
	t_expt	*tmp;

	while (mshell->expt)
	{
		free(mshell->expt->exptvar);
		free(mshell->expt->value);
		tmp = mshell->expt;
		mshell->expt = mshell->expt->next;
		free(tmp);
	}
}
