/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_redir_r.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 16:02:25 by oboutarf          #+#    #+#             */
/*   Updated: 2023/01/12 13:28:07 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	treat_redir_r(t_mshell *mshell, int *i)
{
	int	tmp_i;

	tmp_i = *i;
	++(*i);
	mshell->tkn->type = 9;
	if (!tokenizer(mshell, tmp_i, *i))
		return (0);
	return (1);
}
