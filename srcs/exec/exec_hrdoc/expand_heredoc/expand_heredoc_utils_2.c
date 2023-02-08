/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc_utils_2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 23:23:54 by oboutarf          #+#    #+#             */
/*   Updated: 2023/02/08 23:24:36 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	gather_usr_input(char *content, t_mshell *mshell)
{
	free(mshell->tkn->tkn);
	mshell->tkn->tkn = content;
	return (1);
}

int	dup_expander___hrdoc(t_mshell *mshell, char *exptval, int n_tp)
{
	int	i;

	i = 0;
	free(mshell->expd->types[n_tp]);
	mshell->expd->types[n_tp] = NULL;
	mshell->expd->types[n_tp] = malloc(sizeof(char) * (ft_strlen(exptval) + 1));
	if (!mshell->expd->types[n_tp])
		return (0);
	while (exptval[i])
	{
		mshell->expd->types[n_tp][i] = exptval[i];
		i++;
	}
	mshell->expd->types[n_tp][i] = '\0';
	return (1);
}

int	lens_types_expd__hrdoc(char *usr_input)
{
	int	cuts;
	int	i;

	i = 0;
	cuts = 0;
	while (usr_input[i])
	{
		if (usr_input[i] == EXPAND)
		{
			i += 1;
			while (usr_input[i] && usr_input[i] != DOUBLE_QUOTE
				&& usr_input[i] != SINGLE_QUOTE && usr_input[i] != EXPAND
				&& usr_input[i] != '\n' && usr_input[i] != ' ')
				i++;
			cuts++;
		}
		else if (usr_input[i] != EXPAND)
		{
			while (usr_input[i] && usr_input[i] != EXPAND)
				i++;
			cuts++;
		}
	}
	return (cuts);
}

int	alloc__hrdoc_for_join(t_mshell *mshell)
{
	int	n_tp;
	int	i0;
	int	i1;

	i1 = 0;
	n_tp = 0;
	while (mshell->expd->types[n_tp])
	{
		i0 = 0;
		while (mshell->expd->types[n_tp][i0])
			i0++;
		i1 += i0;
		n_tp++;
	}
	return (i1);
}

int	joinit_heredoc(t_mshell *mshell, char **new_token, int n_tp, int *i1)
{
	int	i0;

	i0 = 0;
	while (mshell->expd->types[n_tp][i0])
	{
		(*new_token)[*i1] = mshell->expd->types[n_tp][i0];
		i0++;
		(*i1)++;
	}
	return (1);
}
