/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 11:45:41 by oboutarf          #+#    #+#             */
/*   Updated: 2023/02/05 18:22:18 by oboutarf         ###   ########.fr       */
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

char	*ft_itoa(int n)
{
	char	*str;
	int		i;

	if (!n)
	{
		str = malloc(sizeof(char) * 2);
		if (!str)
			return (NULL);
		return (str[n] = '0', str[n + 1] = '\0', str);
	}
	i = ft_nbrlen(n);
	str = ft_convert_to_str(n, i);
	return (str);
}

char	*ft_convert_to_str(int n, int i)
{
	char			*str;
	unsigned int	nb;

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


