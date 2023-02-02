/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hrdoc_review.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 14:03:56 by oboutarf          #+#    #+#             */
/*   Updated: 2023/02/02 11:26:23 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	gather_content_from_delim(t_mshell *mshell)
{
	char	*usr_input;
	int		i;

	i = 0;
	while (mshell->tkn->next->tkn[i])
		i++;
	usr_input = malloc(sizeof(char) * (i + 1));
	if (!usr_input)
		return (0);
	i = 0;
	while (mshell->tkn->next->tkn[i])
	{
		usr_input[i] = mshell->tkn->next->tkn[i];
		i++;
	}
	usr_input[i] = '\0';
	free(mshell->tkn->tkn);
	mshell->tkn->tkn = usr_input;
	return (1);
}

int	hrdoc_review(t_mshell *mshell, int *cmd_cnt)
{
	int		expander;
	t_tkn	*tmp;

	expander = -42;
	if (mshell->tkn->type == HRDOC)
	{
		tmp = mshell->tkn;
		if (!type_next_token(mshell->tkn, DLIM_HRDOC))
			return (0);
		mshell->tkn = mshell->tkn->next;
		center_hrdoc_delim_treatment(mshell, &expander);
		execute_hrdoc(mshell, expander);
		mshell->tkn = tmp;
		gather_content_from_delim(mshell);
		tmp = mshell->tkn->next->next;
		free(mshell->tkn->next);
		mshell->tkn->next = tmp;
		mshell->tkn->type = HRDOC_RDIR;
		if (mshell->tkn->next->tkn
			&& mshell->tkn->next->type == WORD && *cmd_cnt == 0)
			return (mshell->tkn->next->type = _CMD, *cmd_cnt += 1, 1);
	}
	return (1);
}
