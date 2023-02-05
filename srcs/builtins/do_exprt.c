/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_exprt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkermia <dkermia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 20:51:12 by oboutarf          #+#    #+#             */
/*   Updated: 2023/02/05 05:29:38 by dkermia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_export(t_mshell *mshell)
{
	t_expt	*env;

	env = mshell->expt;
	while (env->next)
	{
		ft_putstr("declare -x ");
		ft_putstr(env->exptvar);
		if (env->value)
		{
			ft_putchar('=');
			ft_putstr("\"");
			ft_putstr(env->value);
			ft_putstr("\"");
		}
		ft_putchar('\n');
		env = env->next;
	}
}

t_expt	*search_exprt_pos(char *val, t_expt *head)
{
	t_expt	*prev;
	int		cmp;

	prev = NULL;
	while (head->next)
	{
		cmp = ft_strcmp(val, head->exptvar);
		if (cmp <= 0)
			return (prev);
		prev = head;
		head = head->next;
	}
	return (prev);
}

int	check_arg(char *current_arg)
{
	int	i;

	i = 0;
	if (!current_arg)
		return (0);
	if (!ft_isalpha(*current_arg) || *current_arg == '_')
		return (0);
	while (ft_isalnum(current_arg[i]) || current_arg[i] == '_')
		i++;
	if (current_arg[i] == '\0')
		return (2);
	if (current_arg[i] == '+' && current_arg[i + 1] == '=')
		return (1);
	if (current_arg[i] == '=')
		return (1);
	return (0);
}

char	**split_args_vars(char *args, int *len)
{
	char	**to_export;

	len[ARG] = ft_strlen(args);
	len[VAR] = ft_strequal_sign(args);
	len[VALUE] = len[ARG] - len[VAR];
	if (len[VAR] == len[ARG])
	{
		to_export = malloc(sizeof(char *) * 2);
		to_export[1] = NULL;
	}
	else
	{
		to_export = malloc(sizeof(char *) * 3);
		to_export[2] = NULL;
	}
	if (!to_export)
		return (NULL);
	to_export[VAR] = ft_substr(args, 0, len[VAR]);
	if (!to_export[VAR])
		return (free(to_export), NULL);
	return (to_export);
}

char	**split_args(char *args)
{
	char	**to_export;
	int		len[3];

	to_export = split_args_vars(args, len);
	if (!to_export)
		return (NULL);
	if (len[VAR] != len[ARG])
	{
		to_export[VALUE] = ft_substr(args, len[VAR] + 1, len[VALUE]);
		if (!to_export[VALUE])
			return (free(to_export[VAR]), free(to_export), NULL);
	}
	return (to_export);
}

int	free_export_split(char **export_split)
{
	int	i;

	i = 0;
	while (export_split[i])
	{
		free(export_split[i]);
		i++;
	}
	return (1);
}

int	do_exprt_split_args(char *args, t_mshell *mshell)
{
	char	**export_split;

	export_split = split_args(args);
	if (manage_expt(export_split, mshell) != 1)
		return (0);
	if (ft_strchr(args, '='))
		if (!export_split || manage_env(export_split, mshell) != 1)
			return (0);
	free_export_split(export_split);
	free(export_split);
	return (1);
}

int	do_exprt(t_mshell *mshell)
{
	t_tkn	*args;

	if (mshell->exec->start_exec->next == NULL)
		return (print_export(mshell), 1);
	args = mshell->exec->start_exec->next;
	while (args != NULL && args->tkn != NULL)
	{
		if (!check_arg(args->tkn))
		{
			error_manager("export", args->tkn, "not a valid identifier");
			args = args->next;
			continue ;
		}
		if (!do_exprt_split_args(args->tkn, mshell))
			return (0);
		args = args->next;
	}
	return (1);
}
