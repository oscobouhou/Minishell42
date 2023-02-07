/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 16:28:57 by oboutarf          #+#    #+#             */
/*   Updated: 2023/02/07 17:59:19 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	make_new_heredoc(t_mshell *mshell)
{
	mshell->heredoc->next = malloc(sizeof(t_heredoc));
	if (!mshell->heredoc->next)
		return (0);
	mshell->heredoc = mshell->heredoc->next;
	mshell->heredoc->pipe_heredoc[0] = -42;
	mshell->heredoc->pipe_heredoc[1] = -42;
	mshell->heredoc->next = NULL;
	return (1);
}

int	init_heredoc(t_mshell *mshell)
{
	mshell->heredoc = malloc(sizeof(t_heredoc));
	if (!mshell->heredoc)
		return (0);
	mshell->hd_heredoc = mshell->heredoc;
	mshell->heredoc->pipe_heredoc[0] = -42;
	mshell->heredoc->pipe_heredoc[1] = -42;
	mshell->heredoc->next = NULL;
	return (1);
}
