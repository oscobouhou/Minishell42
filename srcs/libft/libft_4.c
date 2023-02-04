/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkermia <dkermia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 11:09:22 by dkermia           #+#    #+#             */
/*   Updated: 2023/02/03 11:13:30 by dkermia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isalnum(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
		|| (c >= '0' && c <= '9'))
		return (1);
	else
		return (0);
}

int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

char	*ft_strchr(char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (((unsigned char *)s)[i] == (unsigned char)c)
			return ((char *)&s[i]);
		i++;
	}
	if (c == 0)
		return (((char *)&s[i]));
	return (NULL);
}


int	search_lowest(char *val, t_env *env)
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

char	*ft_strdup(char *str)
{
	size_t	i;
	char	*s;
	size_t	size;

	i = 0;
	size = ft_strlen(str) + 1;
	s = malloc(size * sizeof(char));
	if (!s)
		return (NULL);
	while (i < size -1)
	{
		s[i] = str[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}