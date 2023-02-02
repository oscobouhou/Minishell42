/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_space.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 16:04:08 by oboutarf          #+#    #+#             */
/*   Updated: 2023/02/02 11:37:23 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	treat_space(t_mshell *mshell, int *i)
{
	while (mshell->rdline_outp[*i] == ' '
		|| mshell->rdline_outp[*i] == '\n'
		|| mshell->rdline_outp[*i] == '\t'
		|| mshell->rdline_outp[*i] == '\v'
		|| mshell->rdline_outp[*i] == '\f'
		|| mshell->rdline_outp[*i] == '\r')
		++(*i);
	return (1);
}
