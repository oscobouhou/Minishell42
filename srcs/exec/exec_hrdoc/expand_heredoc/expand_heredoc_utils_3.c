/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc_utils_3.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 23:29:53 by oboutarf          #+#    #+#             */
/*   Updated: 2023/02/08 23:30:10 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*join_types_expanded__hrdoc(t_mshell *mshell)
{
	char	*new_token;
	int		n_tp;
	int		i1;

	n_tp = 0;
	i1 = alloc__hrdoc_for_join(mshell);
	new_token = malloc(sizeof(char) * (i1 + 1));
	if (!new_token)
		return (NULL);
	i1 = 0;
	while (mshell->expd->types[n_tp])
	{
		joinit_heredoc(mshell, &new_token, n_tp, &i1);
		if (mshell->expd->types[n_tp][0])
			free(mshell->expd->types[n_tp]);
		n_tp++;
	}
	new_token[i1] = '\0';
	free(mshell->expd->types);
	return (new_token);
}

int	check_expander__hrdoc(char *expander, t_mshell *mshell, int n_tp)
{
	t_expt	*head;

	head = mshell->expt;
	while (mshell->expt->next)
	{
		if (!ft_strcmp(expander, mshell->expt->exptvar))
		{
			if (!dup_expander___hrdoc(mshell, mshell->expt->value, n_tp))
				return (0);
			mshell->expt = head;
			return (1);
		}
		mshell->expt = mshell->expt->next;
	}
	free(mshell->expd->types[n_tp]);
	mshell->expd->types[n_tp] = "";
	mshell->expt = head;
	return (1);
}

int	make_expands_types__hrdoc(t_mshell *mshell, int n_tp)
{
	if (mshell->expd->types[n_tp][0] == EXPAND
		&& !mshell->expd->types[n_tp][0 + 1])
		return (1);
	else if (mshell->expd->types[n_tp][0] == EXPAND)
		check_expander__hrdoc(&mshell->expd->types[n_tp][1], mshell, n_tp);
	return (1);
}

int	types_expd_cut_expander__hrdoc(t_mshell *mshell, char *usr_input, \
	int *n_tp, int *i)
{
	int	j;

	i[1] = i[0];
	i[0] += 1;
	while (usr_input[i[0]] && usr_input[i[0]] != DOUBLE_QUOTE \
		&& usr_input[i[0]] != SINGLE_QUOTE && usr_input[i[0]] != EXPAND \
		&& usr_input[i[0]] != '\n' && usr_input[i[0]] != ' ')
		i[0]++;
	mshell->expd->types[*n_tp] = malloc(sizeof(char) * (i[0] - i[1]) + 1);
	if (!mshell->expd->types[*n_tp])
		return (0);
	j = 0;
	while (usr_input[i[1]] && i[1] < i[0])
	{
		mshell->expd->types[*n_tp][j] = usr_input[i[1]];
		i[1]++;
		j++;
	}
	mshell->expd->types[*n_tp][j] = '\0';
	(*n_tp)++;
	return (1);
}

int	types_expd_cut_usr_input__hrdoc(t_mshell *mshell, char *usr_input, \
	int *n_tp, int *i)
{
	int	j;

	while (usr_input[i[0]] && usr_input[i[0]] != EXPAND)
		i[0]++;
	mshell->expd->types[*n_tp] = malloc(sizeof(char) * (i[0] - i[1]) + 1);
	if (!mshell->expd->types[*n_tp])
		return (0);
	j = 0;
	while (usr_input[i[1]] && i[1] < i[0])
	{
		mshell->expd->types[*n_tp][j] = usr_input[i[1]];
		i[1]++;
		j++;
	}
	mshell->expd->types[*n_tp][j] = '\0';
	(*n_tp)++;
	return (1);
}
