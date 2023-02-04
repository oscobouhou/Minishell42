/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkermia <dkermia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 11:06:44 by dkermia           #+#    #+#             */
/*   Updated: 2023/02/03 11:09:13 by dkermia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_bzero(void *b, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
		((char *)b)[i++] = 0;
}


void	fill_s1(char *str, char *s1, int *i)
{
	while (s1[*i])
	{
		str[*i] = s1[*i];
		(*i)++;
	}
}

char	*ft_strjoin(char *s1, char *s2, int upend)
{
	char	*str;
	int		i;
	int		n;

	if (!s1 && s2)
		return (ft_strdup(s2));
	if (s1 && !s2)
		return (ft_strdup(s2));
	str = malloc((ft_strlen(s1) + ft_strlen(s2) + 1));
	if (str == NULL)
		return (NULL);
	i = 0;
	n = 0;
	if (s1)
		fill_s1(str, s1, &i);
	while (s2[n])
	{
		str[i] = s2[n];
		n++;
		i++;
	}
	str[i] = '\0';
	if (upend == 1)
		free(s1);
	return (str);
}

char	*ft_charcat(char *str, char c)
{
	int		len;
	char	*new_str;
	int		i;

	i = 0;
	len = ft_strlen(str);
	new_str = malloc(sizeof(char) * (len + 2));
	if (!new_str)
		return (NULL);
	while (str[i])
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[i] = c;
	new_str[i + 1] = 0;
	return (new_str);
}

char	*ft_substr(char *s, int start, size_t len)
{
	char			*str;
	unsigned int	j;

	j = 0;
	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
	{
		str = malloc(1);
		str[0] = '\0';
		return (str);
	}
	if ((ft_strlen(s) - start) <= (int)len)
		str = (char *)malloc(ft_strlen(s) - start + 1);
	else
		str = (char *)malloc(len + 1);
	if (!str)
		return (NULL);
	while (s[start] && j < len)
			str[j++] = s[start++];
	str[j] = 0;
	return (str);
}
