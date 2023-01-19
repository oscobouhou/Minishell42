/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   center_expand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 22:46:34 by oboutarf          #+#    #+#             */
/*   Updated: 2023/01/19 22:46:07 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	convert_expander(char **expander, char *input)
{
	int	i;

	i = -1;
	free(*expander);
	*expander = malloc(sizeof(char) * (ft_strlen(input) + 1));
	if (!*expander)
		return (0);
	while (input[++i])
		(*expander)[i] = input[i];
	(*expander)[i] = '\0';
	return (1);
}

int	delete_expander(char **expander)
{
	free(*expander);
	*expander = NULL;
	return (1);
}

int	delete_or_convert_expander(t_mshell *mshell, char **expander)
{
	t_expt	*head;

	head = mshell->expt;
	while (mshell->expt->next)
	{
		if (!ft_strcmp(mshell->expt->exptvar, *expander))
		{
			convert_expander(expander, mshell->expt->value);
			return (mshell->expt = head, 1);
		}
		mshell->expt = mshell->expt->next;
	}
	return (delete_expander(expander), 0);
}

char	*check_expander(char *tkn)
{
	char	*expander;
	int		i;

	i = 0;
	if (tkn[0] == DOUBLE_QUOTE)
		return ("$");
	while (tkn[i] != DOUBLE_QUOTE && tkn[i] != EXPAND)
		i++;
	expander = malloc(sizeof(char) * i + 2);
	if (!expander)
		return (NULL);
	i = -1;
	while (tkn[++i] != DOUBLE_QUOTE && tkn[i] != EXPAND)
		expander[i] = tkn[i];
	expander[i] = '\0';
	return (expander);
}

int	expansion_of_expander_out_qut(t_mshell *mshell, int *i)
{
	(void)mshell;
	(void)*i;
	return (1);	
}

int	expansion_of_expander_in_s_qut(t_mshell *mshell, int *i)
{
	char	*update_token;
	int		i1;
	int		i2;

	i1 = 0;
	i2 = 0;
	while (i1 != (i[0] + 1))
		i1++;
	while (mshell->tkn->tkn[i1] != SINGLE_QUOTE)
		i1++;
	i[1] = i1;
	while (mshell->tkn->tkn[i1])
		i1++;
	i[0] = i1;
	update_token = malloc(sizeof(char) * (i1 - 1));
	if (!update_token)
		return (0);
	i1 = 0;
	while (mshell->tkn->tkn[i2])
	{
		if (i2 <= i[1] && mshell->tkn->tkn[i2] == SINGLE_QUOTE)
			i2++;
		if (!mshell->tkn->tkn[i2])
			break ;
		update_token[i1] = mshell->tkn->tkn[i2];
		i1++;
		i2++;
	}
	update_token[i1] = '\0';
	free(mshell->tkn->tkn);
	mshell->tkn->tkn = update_token;
	i[0] = (i[1] - 1);
	return (1);
}

int	update_expand_in_token(t_mshell *mshell, char *expander, char **update_token, int *i)
{
	int	expd_len;
	int	i1;

	i1 = 0;
	expd_len = 0;
	while (i1 != (i[0]))
		i1++;
	if (!expander)
	{
		i[1] = i1;
		while (mshell->tkn->tkn[i1] != EXPAND && mshell->tkn->tkn[i1] != DOUBLE_QUOTE)
		{
			expd_len++;
			i1++;
		}
		i1 = i[1];
		while (mshell->tkn->tkn[i1 + expd_len])
			i1++;
		*update_token = malloc(sizeof(char) * i1);
		if (!*update_token)
			return (0);
		i1 = 0;
		while (i1 != i[0])
		{
			(*update_token)[i1] = mshell->tkn->tkn[i1];
			i1++;
		}
		i1 += 1;
		dprintf(2, "%d\n", i[0]);
		i[0] = i1;
		dprintf(2, "%d\n", i[0]);
		while (mshell->tkn->tkn[i1 + expd_len])
		{
			(*update_token)[i1] = mshell->tkn->tkn[i1 + expd_len];
			i1++;
		}
		(*update_token)[i1] = '\0';
		free(mshell->tkn->tkn);
		mshell->tkn->tkn = *update_token;
		return (1);
	}
	else
	{
		dprintf(2, "HOOOO OUIIII!");
		return (1);
	}
	return (1);
}



int	expansion_of_expander_in_d_qut(t_mshell *mshell, int *i)
{
	char	*update_token;
	char	*expander;
	int		i1;

	i1 = 0;
	i[0] += 1;
	while (i1 != i[0])
		i1++;
	i[1] = i1;
	while (mshell->tkn->tkn[i[1]] != DOUBLE_QUOTE)
	{
		if (mshell->tkn->tkn[i[1]] == EXPAND)
		{
			expander = check_expander(&mshell->tkn->tkn[i[1] + 1]);
			delete_or_convert_expander(mshell, &expander);
			update_expand_in_token(mshell, expander, &update_token, i);
			break ;
		}
		i[1]++;
	}
	return (1);	
}

int	expand_checker(t_mshell *mshell)
{
	int		qut[2];
	int     i[2];

	i[1] = 0;
	i[0] = 0;
	qut[0] = 0;
	qut[1] = 0;
	while (mshell->tkn->tkn[i[0]])
	{
		if (mshell->tkn->tkn[i[0]] == SINGLE_QUOTE)
			qut[0] += 1;
		if (mshell->tkn->tkn[i[0]] == DOUBLE_QUOTE)
			qut[1] += 1;
		if (qut[1] % 2 == 0 && qut[0] % 2 != 0)
		{
			expansion_of_expander_in_s_qut(mshell, i);
			qut[0] += 1;
		}
		else if ((qut[1] % 2 != 0) && (qut[0] % 2 == 0))
		{
			expansion_of_expander_in_d_qut(mshell, i);
			qut[1] += 1;	
		}
		else if ((qut[1] % 2 == 0) && (qut[0] % 2 == 0) && !mshell->tkn->tkn[i[0] + 1])
			break ;
		else if ((qut[1] % 2 == 0) && (qut[0] % 2 == 0))
		{
			expansion_of_expander_out_qut(mshell, i);
		}
		i[0]++;
	}
	return (1);
}

int	center_expand(t_mshell *mshell)
{
	mshell->tkn = mshell->head_tkn;
	while (mshell->tkn->next)
	{
		if (mshell->tkn->type == _CMD || mshell->tkn->type == _ARG || mshell->tkn->type == _FILE)
			expand_checker(mshell);
		mshell->tkn = mshell->tkn->next;
	}
	return (1);
}
