/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_seeker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 14:19:19 by oboutarf          #+#    #+#             */
/*   Updated: 2023/01/15 16:03:14 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	make_expansion(t_mshell *mshell, char **expander, char *expt_value)
{
	char	*new_token;
	int		new_len;
	int		tmp_i;
	int		i;
	int 	j;

	i = -1;
	new_len = ((ft_strlen(mshell->tkn->tkn) - ft_strlen(*expander)) + ft_strlen(expt_value) + 1);
	new_token = malloc(sizeof(char) * new_len);
	if (!new_token)
		return (0);
	while (mshell->tkn->tkn[++i] != EXPAND)
		new_token[i] = mshell->tkn->tkn[i];
	tmp_i = ft_strlen(*expander) + i;
	j = i - 1;
	i = -1;
	while (mshell->expt->value[++i])
		new_token[++j] = mshell->expt->value[i];
	while (mshell->tkn->tkn[++tmp_i])
		new_token[++j] = mshell->tkn->tkn[tmp_i];
	new_token[++j] = '\0';
	free(mshell->tkn->tkn);
	mshell->tkn->tkn = malloc(sizeof(char) * new_len);
	if (!mshell->tkn->tkn)
		return (0);
	i = -1;
	while (new_token[++i])
		mshell->tkn->tkn[i] = new_token[i];
	mshell->tkn->tkn[++i] = '\0';
	return (1);
}

int export_seeker(t_mshell *mshell, char **expander)
{
    t_expt  *head;

    head = mshell->expt;
    while (mshell->expt->next)
    {
        if (ft_strcmp(mshell->expt->exptvar, *expander) == 0)
            make_expansion(mshell, expander, mshell->expt->value);
        mshell->expt = mshell->expt->next;
    }
    mshell->expt = head;
    return (1);
}
