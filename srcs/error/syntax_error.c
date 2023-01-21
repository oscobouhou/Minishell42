/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkermia <dkermia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 13:59:17 by oboutarf          #+#    #+#             */
/*   Updated: 2023/01/21 15:37:47 by dkermia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void syntax_error(void)
{
	dprintf(2, "minishell: syntax error near unexpected token\n");
}
