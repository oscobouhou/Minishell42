/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 16:18:22 by oboutarf          #+#    #+#             */
/*   Updated: 2023/02/05 07:45:17 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	error_manager(char *process, char *tkn, char *error)
{
	ft_putstr("minishell: ");
	ft_putstr(process);
	if (tkn)
	{
		ft_putstr(": `");
		ft_putstr(tkn);
		ft_putstr("': ");
	}
	else
		ft_putstr(": ");
	ft_putstr(error);
	ft_putchar('\n');
	return (1);
}
