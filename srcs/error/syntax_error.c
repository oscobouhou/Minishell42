/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 13:59:17 by oboutarf          #+#    #+#             */
/*   Updated: 2023/02/07 00:31:46 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	syntax_error(char *tkn)
{
	ft_putstr_fd(2, "minishell: syntax error near unexpected token`");
	if (tkn)
		ft_putstr_fd(2, tkn);
	else
		ft_putstr_fd(2, "newline");
	ft_putstr_fd(2, "'.\n");
}
