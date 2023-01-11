/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   center_expand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 22:46:34 by oboutarf          #+#    #+#             */
/*   Updated: 2023/01/10 22:47:23 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_envar(char *envar, char *str)
{
	int cnt;
	int	i;

	i = 0;
	cnt = ft_strequal_sign(envar);
	while (str[i] && envar[i] == str[i])
	{
		i++;
		cnt--;
	}
	if (cnt == 0)
		return (i);
	return (0);
}


int	rewrite_envar_with_expand(char *str, t_env *exprt)
{
	int	i;

	i = 0;
	if (!exprt->value)
	{
		// i = (ft_strlen(str) - 2)
	}
	(void)i;
	(void)str;
	return (0);
}


int ft_expand(char *str, t_env *exprt)
{
	int	i = 0;

	while (str[i] != EXPAND)
		i++;
	if (str[i])
		++i;
	while (exprt->next && str[i])
	{
		if (str[i] == exprt->envar[0])
		{
			if (check_envar(exprt->envar, &str[i]))
				rewrite_envar_with_expand(str, exprt);
		}
		exprt = exprt->next;
	}
	return (1);
}