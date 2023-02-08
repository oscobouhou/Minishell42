/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils_0.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 12:45:21 by oboutarf          #+#    #+#             */
/*   Updated: 2023/02/08 12:53:38 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	single_dollar_in_dq(t_mshell *mshell, int n_tp)
{
	free(mshell->expd->types[n_tp]);
	mshell->expd->types[n_tp] = malloc(sizeof(char) * 2);
	mshell->expd->types[n_tp][0] = '$';
	mshell->expd->types[n_tp][1] = '\0';
	return (1);
}

int	hrdoc_scannner(t_mshell *mshell, int n_tp)
{
	if (scan_herdoc(mshell, n_tp - 1))
	{
		get_all_content_from_string(mshell, n_tp);
		return (1);
	}
	return (0);
}

int	scan_herdoc(t_mshell *mshell, int n_tp)
{
	int	i;

	i = 0;
	while (mshell->expd->types[n_tp][i])
	{
		if (mshell->expd->types[n_tp][i + 1] \
			&& mshell->expd->types[n_tp][i] == REDIR_L \
			&& mshell->expd->types[n_tp][i + 1] == REDIR_L)
			return (1);
		i++;
	}
	return (0);
}

int	get_all_content_from_string(t_mshell *mshell, int n_tp)
{
	char	*new_type;
	int		i;

	i = ft_strlen(mshell->expd->types[n_tp]);
	new_type = malloc(sizeof(char) * (i + 1));
	if (!new_type)
		return (0);
	i = 0;
	while (mshell->expd->types[n_tp][i])
	{
		new_type[i] = mshell->expd->types[n_tp][i];
		i++;
	}
	new_type[i] = '\0';
	free(mshell->expd->types[n_tp]);
	mshell->expd->types[n_tp] = new_type;
	return (1);
}
