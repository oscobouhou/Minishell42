/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compose_tkn.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 15:32:02 by oboutarf          #+#    #+#             */
/*   Updated: 2023/02/03 16:19:34 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	compose_and_launch_command(t_mshell *mshell, char **env)
{
	mshell->tkn = mshell->head_tkn;
	if (!center_expand(mshell))
		return (0);
	if (!init_t_token(mshell))
		return (0);
	if (!parse_output(mshell))
		return (free_tokens(mshell), 0);
	if (!center_review(mshell))
		return (free_tokens(mshell), 0);
	if (!center_exec(mshell, env))
		return (0);
	return (1);
}
