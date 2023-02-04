/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_manage_types.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 00:14:51 by oboutarf          #+#    #+#             */
/*   Updated: 2023/02/04 23:39:33 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	manage_expands_in_sq(t_mshell *mshell, int n_tp)
{
	char	*new_type;
	int		i;
	int		j;

	i = 1;
	j = 0;
	new_type = malloc(sizeof(char) * (ft_strlen(mshell->expd->types[n_tp]) - 2) + 1);
	if (!new_type)
		return (0);
	while (mshell->expd->types[n_tp][i] != SINGLE_QUOTE)
	{
		new_type[j] = mshell->expd->types[n_tp][i];
		j++;
		i++;
	}
	new_type[j] = '\0';
	free(mshell->expd->types[n_tp]);
	mshell->expd->types[n_tp] = new_type;
	return (1);
}

int	update_expd_exit(t_mshell *mshell, int n_tp, int *i)
{
	if (!mshell->expd->types[n_tp][*i + 1])
	{
		(*i)++;
		return (1);
	}
	else if (mshell->expd->types[n_tp][*i + 1] == '?')
	{
		free(mshell->expd->expander);
		mshell->expd->expander = NULL;
		mshell->expd->expander = ft_itoa(mshell->exit_status);
		mshell->expd->old_expd_len = 2;
		mshell->expd->new_expd_len = ft_strlen(mshell->expd->expander);
	}
	return (1);
}

void	clean_expander(t_mshell *mshell)
{
	if (mshell->expd->expander)
	{
		free(mshell->expd->expander);
		mshell->expd->expander = NULL;
	}
}

int skip_hexpander_hrdoc(t_mshell *mshell, int n_tp, int *i)
{
	int	tmp_i;

	while (mshell->expd->types[n_tp][*i] && ((mshell->expd->types[n_tp][*i] >= 9 && mshell->expd->types[n_tp][*i] <= 13) || (mshell->expd->types[n_tp][*i] == 32)))
		(*i)++;
	tmp_i = 0;
	while (mshell->expd->types[n_tp][*i] && check_printable_char(mshell->expd->types[n_tp][*i]))
		(*i)++;
	return (*i - tmp_i);
}

int	get_all_content_from_string(t_mshell *mshell, int n_tp)
{
	char 	*new_type;
	int		i;

	i = ft_strlen(mshell->expd->types[n_tp]);
	new_type = malloc(sizeof(char) * (i + 1));
	if (!new_type)
		return (0);
	i = 0;
	while (mshell->expd->types[n_tp][i])
	{
		new_type[i] = mshell->expd->types[n_tp][i];
		i++;
	}
	new_type[i] = '\0';
	free(mshell->expd->types[n_tp]);
	mshell->expd->types[n_tp] = new_type;
	return (1);
}

int	scan_herdoc(t_mshell *mshell, int n_tp)
{
	int	i;

	i = 0;
	while (mshell->expd->types[n_tp][i])
	{
		if (mshell->expd->types[n_tp][i + 1] && mshell->expd->types[n_tp][i] == REDIR_L \
			&& mshell->expd->types[n_tp][i + 1] == REDIR_L)
			return (1);
		i++;
	}
	return (0);
}

int	manage_expands_oq(t_mshell *mshell, int n_tp)
{
	int		i;

	i = 0;
	while (mshell->expd->types[n_tp][i])
	{
		if (mshell->expd->types[n_tp][i] == REDIR_L && mshell->expd->types[n_tp][i + 1] == REDIR_L)
		{
			i += 2;
			skip_hexpander_hrdoc(mshell, n_tp, &i);
			mshell->expd->old_expd_len = 0;
			mshell->expd->new_expd_len = 0;
			update_type(mshell, &i, n_tp);	
		}
		else if (mshell->expd->types[n_tp][i] == EXPAND && mshell->expd->types[n_tp][i + 1] != EXPAND)
		{
			if (mshell->expd->types[n_tp][i + 1] && mshell->expd->types[n_tp][i + 1] != '?')
			{
				if (cut_expander(mshell, n_tp, i) != -42)
					check_expander(mshell);
				update_type(mshell, &i, n_tp);			
			}
			else
			{
				update_expd_exit(mshell, n_tp, &i);
				continue ;
			}
		}
		else
			i++;
		// i++;
	}
	return (1);
}

int treat_export_exit_status(t_mshell *mshell, int n_tp, int i)
{
	if (mshell->expd->types[n_tp][i + 1] == '?')
	{
		if (mshell->expd->expander)
		{
			free(mshell->expd->expander);
			mshell->expd->expander = NULL;
		}
		mshell->expd->expander = ft_itoa(mshell->exit_status);
		mshell->expd->old_expd_len = 1;
		mshell->expd->new_expd_len = ft_strlen(mshell->expd->expander);
	}
	return (1);
}

int	manage_expands_in_dq(t_mshell *mshell, int n_tp)
{
	int	i;

	i = 1;
	if (mshell->expd->types[n_tp][i] == EXPAND && mshell->expd->types[n_tp][i + 1] == DOUBLE_QUOTE)
	{
		free(mshell->expd->types[n_tp]);
		mshell->expd->types[n_tp] = "$\0";
		return (1);
	}
	while (mshell->expd->types[n_tp][i])
	{
		if (n_tp > 0)
		{
			if (scan_herdoc(mshell, n_tp - 1))
				get_all_content_from_string(mshell, n_tp);
					break ;
			
		}
		if (mshell->expd->types[n_tp][i] == EXPAND)
		{
			if (cut_expander(mshell, n_tp, i) != -42)
				check_expander(mshell);
			treat_export_exit_status(mshell, n_tp, i);
			if (mshell->expd->types[n_tp][i + 1] == SINGLE_QUOTE || mshell->expd->types[n_tp][i + 1] == DOUBLE_QUOTE)
			{
				get_all_content_from_string(mshell, n_tp);
				break ;
			}
			update_type(mshell, &i, n_tp);
			i -= 1;
		}
		i++;
	}
	return (1);
}

int	manage_expands_in_types(t_mshell *mshell)
{
	int	n_tp;
	int	dcrm;

	n_tp = 0;
	dcrm = mshell->expd->n_types;
	while (dcrm-- > 0)
	{
		if (mshell->expd->types[n_tp][0] == SINGLE_QUOTE)
			manage_expands_in_sq(mshell, n_tp);
		else if (mshell->expd->types[n_tp][0] == DOUBLE_QUOTE)
			manage_expands_in_dq(mshell, n_tp);
		else if (mshell->expd->types[n_tp][0] != SINGLE_QUOTE && mshell->expd->types[n_tp][0] != DOUBLE_QUOTE)
			manage_expands_oq(mshell, n_tp);
		n_tp++;
	}
	return (1);
}
