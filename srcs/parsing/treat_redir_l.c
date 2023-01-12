/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_redir_l.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 16:01:55 by oboutarf          #+#    #+#             */
/*   Updated: 2023/01/12 13:31:04 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	treat_redir_l(t_mshell *mshell, int *i)
{
	int	tmp_i;

	tmp_i = *i;
	++(*i);
	mshell->tkn->type = 10;
	if (!tokenizer(mshell, tmp_i, *i))
		return (0);
	return (1);
}
