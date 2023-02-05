/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compose_tkn.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 15:32:02 by oboutarf          #+#    #+#             */
/*   Updated: 2023/02/05 10:03:41 by oboutarf         ###   ########.fr       */
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

int	compose_and_launch_command(t_mshell *mshell, char **env)
{
	mshell->tkn = mshell->head_tkn;
	if (!center_expand(mshell))
		return (0);
	if (!init_t_token(mshell))
		return (0);
	if (!parse_output(mshell))
		return (free_tokens(mshell), 0);
	if (!center_review(mshell))
		return (free_tokens(mshell), 0);
	if (!center_quotes(mshell))
		return (free_tokens(mshell), 0);
	if (!center_exec(mshell, env))
		return (0);
	return (1);
}
