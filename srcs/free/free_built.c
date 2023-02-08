/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_built.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 12:40:04 by oboutarf          #+#    #+#             */
/*   Updated: 2023/02/08 12:42:25 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	free_built_echo_tab(t_mshell *mshell)
{
	int	n;

	n = 0;
	while (mshell->built->echo_arg[n])
	{
		free(mshell->built->echo_arg[n]);
		n++;
	}
	free(mshell->built->echo_arg);
	return (1);
}

int	free_built(t_mshell *mshell)
{
	if (mshell->built->cd_arg)
		free(mshell->built->cd_arg);
	if (mshell->built->cd_chdir)
		free(mshell->built->cd_chdir);
	if (mshell->built->echo_arg)
		free_built_echo_tab(mshell);
	free(mshell->built);
	return (1);
}
