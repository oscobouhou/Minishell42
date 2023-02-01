/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 11:45:41 by oboutarf          #+#    #+#             */
/*   Updated: 2023/01/31 23:26:07 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strequal_sign(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (i);
}

int	ft_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] && s2[i])
		i++;
	return (s1[i] - s2[i]);
}

int	ft_strlen(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

int	set_pos_to_cmd(t_mshell *mshell)
{
	if (mshell->exec->start_exec->type != -1)
	{
		while (mshell->exec->start_exec && mshell->exec->start_exec->type != _CMD)
		{
			if (!mshell->exec->start_exec->next && !mshell->exec->next)
				return (mshell->exec->no_cmd = 42, 0);
			mshell->exec->start_exec = mshell->exec->start_exec->next;
		}
	}
	return (1);
}

int search_lowest(char *val, t_env *env)
{
	t_env	*head;
	int		cmp;

	head = env;
	while (env->next)
	{
		cmp = ft_strcmp(val, env->envar);
		if (cmp > 0)
			return (env = head, 0);
		env = env->next;
	}
	env = head;
	return (1);
}

void	ft_putstr(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		ft_putchar(str[i]);
}
