/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 11:45:41 by oboutarf          #+#    #+#             */
/*   Updated: 2023/02/01 23:21:05 by oboutarf         ###   ########.fr       */
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

int	ft_atoi(const char *nptr)
{
	int		mns;
	int		num;
	int		i;

	i = 0;
	num = 0;
	mns = 1;
	while (nptr[i] == ' ' || nptr[i] == '\n' || nptr[i] == '\t'
		|| nptr[i] == '\v' || nptr[i] == '\f' || nptr[i] == '\r')
		i++;
	if (nptr[i] == '-')
		mns = -1;
	if (nptr[i] == '+' || nptr[i] == '-')
		i++;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		num = num * 10 + (nptr[i] - 48);
		i++;
	}
	return (num * mns);
}


static int	ft_nbrlen(int n)
{
	int				size;
	unsigned int	nb;

	size = 0;
	if (n == 0)
		return (0);
	else if (n < 0)
	{
		nb = n * -1;
		size = 1;
	}
	else
		nb = n;
	while (nb > 0)
	{
		nb /= 10;
		size++;
	}
	return (size);
}

char	*ft_itoa(int n)
{
	char			*str;
	int				i;
	unsigned int	nb;

	i = ft_nbrlen(n);
	str = malloc(i + 1 * sizeof(char));
	if (!str)
		return (NULL);
	if (n < 0)
		nb = -n;
	else
		nb = n;
	str[i--] = '\0';
	while (i >= 0)
	{
		str[i] = nb % 10 + '0';
		nb /= 10;
		i--;
	}
	if (n < 0)
		str[0] = '-';
	return (str);
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
			if (!mshell->exec->start_exec->next)
				return (mshell->exec->no_cmd = 42, mshell->exec->start_exec = mshell->exec->start_exec_head, 0);
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
