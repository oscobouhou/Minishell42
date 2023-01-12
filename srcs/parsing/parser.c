/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 15:25:09 by oboutarf          #+#    #+#             */
/*   Updated: 2023/01/12 13:30:04 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	sort_kinds(char read)
{
	if (read == SINGLE_QUOTE || read == DOUBLE_QUOTE)
		return (TREAT_QUOTE);
	if (read == PIPE_LINE)
		return (TREAT_PIPE);
	if (read == REDIR_L)
		return (TREAT_REDIR_L);
	if (read == REDIR_R)
		return (TREAT_REDIR_R);
	if (read == HYPHEN)
		return (TREAT_HYPHEN);
	if ((read >= 9 && read <= 13) || read == 32)
		return (TREAT_SPACE);
	return (TREAT_PRINTABLE);
}

int	parse_output(t_mshell *mshell)
{
	int	(*parse[6])(t_mshell *mshell, int *i);
	int	i;

	i = 0;
	parse[TREAT_PIPE] = treat_pipe;
	parse[TREAT_SPACE] = treat_space;
	parse[TREAT_QUOTE] = treat_quote;
	parse[TREAT_HYPHEN] = treat_hyphen;
	parse[TREAT_REDIR_R] = treat_redir_r;
	parse[TREAT_REDIR_L] = treat_redir_l;
	parse[TREAT_PRINTABLE] = treat_printable;
	while (mshell->rdline_outp[i])
	{
		if (!parse[sort_kinds(mshell->rdline_outp[i])](mshell, &i))
			return (0);
	}
	return (1);
}
