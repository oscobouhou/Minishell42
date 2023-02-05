/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 13:59:17 by oboutarf          #+#    #+#             */
/*   Updated: 2023/02/05 07:45:24 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	syntax_error(char *tkn)
{
	ft_putstr_fd("minishell: syntax error near unexpected token`", 2);
	if (tkn)
		ft_putstr_fd(tkn, 2);
	else
		ft_putstr_fd("newline", 2);
	ft_putstr_fd("'.\n", 2);
}
