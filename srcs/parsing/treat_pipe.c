/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 16:00:20 by oboutarf          #+#    #+#             */
/*   Updated: 2023/01/12 13:33:52 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	treat_pipe(t_mshell *mshell, int *i)
{
	int	tmp_i;

	tmp_i = *i;
	++(*i);
	mshell->tkn->type = 0;
	if (!tokenizer(mshell, tmp_i, *i))
		return (0);
	return (1);
}
