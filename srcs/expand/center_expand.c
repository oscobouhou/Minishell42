/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   center_expand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 22:46:34 by oboutarf          #+#    #+#             */
/*   Updated: 2023/01/20 20:21:34 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	update_type(t_mshell *mshell, int *i, int n_tp)
{
	char 	*update;
	int		i0;
	int		i1;
	int		i2;

	i0 = 0;
	i1 = 0;
	i2 = 0;
	while (i1 != (*i + mshell->expd->new_expd_len))
		i1++;
	while (mshell->expd->types[n_tp][i2 + *i + mshell->expd->old_expd_len])
		i2++;
	update = malloc(sizeof(char) + (i1 + i2));
	if (!update)
		return (0);
	i2 = 0;
	while (i2 < *i)
	{
		update[i2] = mshell->expd->types[n_tp][i2];
		i2++;
	}
	if (mshell->expd->expander)
	{
		while (mshell->expd->expander[i0])
		{
			update[i2] = mshell->expd->expander[i0];
			i0++;
			i2++;
		}
	}
	i0 = 1;
	while (mshell->expd->types[n_tp][*i + i0 + mshell->expd->old_expd_len])
	{
		update[i2] = mshell->expd->types[n_tp][*i + i0 + mshell->expd->old_expd_len];
		i2++;
		i0++;
	}
	update[i2] = '\0';
	free(mshell->expd->types[n_tp]);
	mshell->expd->types[n_tp] = update;
	*i += mshell->expd->new_expd_len;
	return (1);
}

int	make_expansion(t_mshell *mshell, char *input)
{
	int	i;

	i = 0;
	free(mshell->expd->expander);
	mshell->expd->expander = malloc(sizeof(char) * (ft_strlen(input) + 1));
	if (!mshell->expd->expander)
		return (0);
	while (input[i])
	{
		mshell->expd->expander[i] = input[i];
		i++;
	}
	mshell->expd->expander[i] = '\0';
	return (1);	
}

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

int	cut_expander(t_mshell *mshell, int n_tp, int i)
{
	int	tmp_i;
	int	j;

	j = 0;
	i += 1;
	tmp_i = i;
	while (mshell->expd->types[n_tp][i] != SINGLE_QUOTE && mshell->expd->types[n_tp][i] != DOUBLE_QUOTE && mshell->expd->types[n_tp][i] != EXPAND)
		i++;
	mshell->expd->expander = malloc(sizeof(char) * ((i - tmp_i) + 1));
	i = tmp_i;
	while (mshell->expd->types[n_tp][i] != SINGLE_QUOTE && mshell->expd->types[n_tp][i] != DOUBLE_QUOTE && mshell->expd->types[n_tp][i] != EXPAND)
	{
		mshell->expd->expander[j] = mshell->expd->types[n_tp][i];
		j++;
		i++;
		
	}
	mshell->expd->expander[j] = '\0';
	return (1);
}

int	manage_expands_in_sq(t_mshell *mshell, int n_tp)
{
	char	*new_type;
	int		i;
	int		j;

	i = 1;
	j = 0;
	new_type = malloc(sizeof(char) * (ft_strlen(mshell->expd->types[n_tp]) - 2) + 1);
	while (mshell->expd->types[n_tp][i] != SINGLE_QUOTE)
	{
		new_type[j] = mshell->expd->types[n_tp][i];
		j++;
		i++;
	}
	new_type[j] = '\0';
	free(mshell->expd->types[n_tp]);
	mshell->expd->types[n_tp] = new_type;
	return (1);
}

int	manage_expands_in_dq(t_mshell *mshell, int n_tp)
{
	int	tmp_i;
	int	i;

	i = 1;
	if (mshell->expd->types[n_tp][i + 1] == DOUBLE_QUOTE)
	{
		free(mshell->expd->types[n_tp]);
		mshell->expd->types[n_tp] = "$\0";
		return (1);
	}
	while (mshell->expd->types[n_tp][i])
	{
		if (mshell->expd->types[n_tp][i] == EXPAND)
		{
			cut_expander(mshell, n_tp, i);
			check_expander(mshell);
			update_type(mshell, &i, n_tp);
			i -= 1;
		}
		i++;
	}
	(void)tmp_i;
	return (1);
}

int	manage_expands_oq(t_mshell *mshell, int n_tp)
{
	// int		i;

	// i = 0;
	// while (mshell->expd->types[n_tp][i])
	// {
	// 	if (mshell->expd->types[n_tp][i] == EXPAND)
	// 	{
	// 		cut_expander(mshell, n_tp, i);
	// 		check_expander(mshell);
	// 		update_type(mshell, &i, n_tp);
	// 		i -= 1;
	// 	}
	// }
	// return (1);
}

int	manage_expands_in_types(t_mshell *mshell)
{
	int	n_tp;

	n_tp = 0;
	while (mshell->expd->types[n_tp])
	{
		if (mshell->expd->types[n_tp][0] == SINGLE_QUOTE)
			manage_expands_in_sq(mshell, n_tp);
		if (mshell->expd->types[n_tp][0] == DOUBLE_QUOTE)
			manage_expands_in_dq(mshell, n_tp);
		if (mshell->expd->types[n_tp][0] != SINGLE_QUOTE && mshell->expd->types[n_tp][0] != DOUBLE_QUOTE)
			manage_expands_oq(mshell, n_tp);
		n_tp++;
	}
	return (1);
}

int	cut_types_expd(t_mshell *mshell)
{
	int	tmp_i;
	int	n_tp;
	int	i;
	int j;

	mshell->expd->types = malloc(sizeof(char *) * (mshell->expd->n_types + 1));
	mshell->expd->types[mshell->expd->n_types] = '\0';
	if (!mshell->expd->types)
		return (0);
	i = 0;
	n_tp = 0;
	tmp_i = 0;
	while (mshell->tkn->tkn[i])
	{
		if (mshell->tkn->tkn[i] != DOUBLE_QUOTE && mshell->tkn->tkn[i] != SINGLE_QUOTE)
		{
			tmp_i = i;
			while (mshell->tkn->tkn[i] && mshell->tkn->tkn[i] != DOUBLE_QUOTE && mshell->tkn->tkn[i] != SINGLE_QUOTE)
				i++;
			mshell->expd->types[n_tp] = malloc(sizeof(char) * (i - tmp_i) + 1);
			if (!mshell->expd->types[n_tp])
				return (0);
			j = 0;
			while (tmp_i < i)
			{
				mshell->expd->types[n_tp][j] = mshell->tkn->tkn[tmp_i];
				tmp_i++;
				j++;
			}
			mshell->expd->types[n_tp][j] = '\0';
			n_tp++;
		}
		if (mshell->tkn->tkn[i] == DOUBLE_QUOTE)
		{
			tmp_i = i;
			i += 1;
			while (mshell->tkn->tkn[i] && mshell->tkn->tkn[i] != DOUBLE_QUOTE)
				i++;
			i += 1;
			mshell->expd->types[n_tp] = malloc(sizeof(char) * (i - tmp_i) + 1);
			if (!mshell->expd->types[n_tp])
				return (0);
			j = 0;
			while (tmp_i <= (i - 1))
			{
				mshell->expd->types[n_tp][j] = mshell->tkn->tkn[tmp_i];
				tmp_i++;
				j++;
			}
			mshell->expd->types[n_tp][j] = '\0';
			n_tp++;
		}
		if (mshell->tkn->tkn[i] == SINGLE_QUOTE)
		{
			tmp_i = i;
			i += 1;
			while (mshell->tkn->tkn[i] && mshell->tkn->tkn[i] != SINGLE_QUOTE)
				i++;
			i += 1;
			mshell->expd->types[n_tp] = malloc(sizeof(char) * (i - tmp_i) + 1);
			if (!mshell->expd->types[n_tp])
				return (0);
			j = 0;
			while (tmp_i <= (i - 1))
			{
				mshell->expd->types[n_tp][j] = mshell->tkn->tkn[tmp_i];
				tmp_i++;
				j++;
			}
			mshell->expd->types[n_tp][j] = '\0';
			n_tp++;
		}
	}
	return (1);
}

int	find_types_len_expd(t_mshell *mshell)
{
	int	cuts;
	int	i;
	
	i = 0;
	cuts = 0;
	while (mshell->tkn->tkn[i])
	{
		if (mshell->tkn->tkn[i] != DOUBLE_QUOTE && mshell->tkn->tkn[i] != SINGLE_QUOTE)
		{
			while (mshell->tkn->tkn[i] && mshell->tkn->tkn[i] != DOUBLE_QUOTE && mshell->tkn->tkn[i] != SINGLE_QUOTE)
				i++;
			cuts++;
		}
		if (mshell->tkn->tkn[i] == DOUBLE_QUOTE)
		{
			i += 1;
			while (mshell->tkn->tkn[i] && mshell->tkn->tkn[i] != DOUBLE_QUOTE)
				i++;
			cuts++;
			i += 1;
		}
		if (mshell->tkn->tkn[i] == SINGLE_QUOTE)
		{
			i += 1;
			while (mshell->tkn->tkn[i] && mshell->tkn->tkn[i] != SINGLE_QUOTE)
				i++;
			cuts++;
			i += 1;
		}
	}
	return (cuts);
}

int	center_expand(t_mshell *mshell)
{
	mshell->tkn = mshell->head_tkn;
	while (mshell->tkn->next)
	{
		if (mshell->tkn->type == _CMD || mshell->tkn->type == _ARG || mshell->tkn->type == _FILE)
		{
			mshell->expd->n_types = find_types_len_expd(mshell);
			cut_types_expd(mshell);
			manage_expands_in_types(mshell);
			// join_types_expanded(mshell);
		}
		mshell->tkn = mshell->tkn->next;
	}
	return (1);
}
