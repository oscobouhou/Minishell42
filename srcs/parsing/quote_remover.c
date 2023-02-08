/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_remover.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 11:38:21 by oboutarf          #+#    #+#             */
/*   Updated: 2023/02/08 11:39:06 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*init_rm_quotes(char *str)
{
	char	*res;
	int		len;

	len = ft_strlen(str);
	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	return (res);
}

char	*remove_quotes(char *str)
{
	static int		in_quotes[2];
	char			*res;
	int				j;
	int				i;

	i = 0;
	j = 0;
	res = init_rm_quotes(str);
	while (str && str[i])
	{
		if (str[i] == DOUBLE_QUOTE && !in_quotes[1])
			in_quotes[0] = !in_quotes[0];
		else if (str[i] == SINGLE_QUOTE && !in_quotes[0])
			in_quotes[1] = !in_quotes[1];
		else if (str[i] == DOUBLE_QUOTE && !in_quotes[1])
			continue ;
		else if (str[i] == SINGLE_QUOTE && !in_quotes[0])
			continue ;
		else
			res[j++] = str[i];
		i++;
	}
	res[j] = '\0';
	free(str);
	return (res);
}

int	closed_quotes(t_mshell *mshell, int *i, int qt)
{
	(*i)++;
	while (mshell->rdline_outp[*i])
	{
		if (mshell->rdline_outp[*i] == qt)
			return (1);
		(*i)++;
	}
	return (0);
}

int	check_closed_quotes(t_mshell *mshell)
{
	int	i;

	i = 0;
	while (mshell->rdline_outp[i])
	{
		if (mshell->rdline_outp[i] == DOUBLE_QUOTE)
			if (!closed_quotes(mshell, &i, DOUBLE_QUOTE))
				return (0);
		if (mshell->rdline_outp[i] == SINGLE_QUOTE)
			if (!closed_quotes(mshell, &i, SINGLE_QUOTE))
				return (0);
		i++;
	}
	return (1);
}

int	center_quotes(t_mshell *mshell)
{
	t_tkn	*head;

	head = mshell->tkn;
	while (head)
	{
		head->tkn = remove_quotes(head->tkn);
		if (!head->tkn)
			return (0);
		head = head->next;
	}
	head = mshell->head_tkn;
	return (1);
}
