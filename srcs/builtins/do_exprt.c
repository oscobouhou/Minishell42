/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_exprt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 20:51:12 by oboutarf          #+#    #+#             */
/*   Updated: 2023/02/04 21:08:52 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_export(t_mshell *mshell)
{
	t_expt *env;

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

t_expt *search_exprt_pos(char *val, t_expt *head)
{
	t_expt *prev;
	int cmp;

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

int check_arg(char *current_arg)
{
	int i;

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

char **split_args(char *args)
{
	char **to_export;
	int value_len;
	int var_len;
	int arg_len;

	arg_len = ft_strlen(args);
	var_len = ft_strequal_sign(args);
	value_len = arg_len - var_len;
	if (var_len == arg_len)
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
	to_export[0] = ft_substr(args, 0, var_len);
	if (!to_export[0])
		return (free(to_export), NULL);
	if (var_len != arg_len)
	{
		to_export[1] = ft_substr(args, var_len + 1, value_len);
		if (!to_export[1])
			return (free(to_export[0]), free(to_export), NULL);
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

int do_exprt(t_mshell *mshell)
{
	char **export_split;
	t_tkn *args;

	export_split = NULL;
	if (mshell->exec->start_exec->next == NULL)
		return (print_export(mshell), 1);
	args = mshell->exec->start_exec->next;
	while (args != NULL && args->tkn != NULL)
	{
		if (!check_arg(args->tkn))
		{
			ft_putstr("minishell: export: '");
			ft_putstr(args->tkn);
			ft_putstr("': not a valid identifier\n");
			args = args->next;
			continue;
		}
		export_split = split_args(args->tkn);
		if (manage_expt(export_split, mshell) != 1)
			return (ft_putstr("Shit, i coulnt export in export\n"), 0);
		if (ft_strchr(args->tkn, '='))
			if (!export_split || manage_env(export_split, mshell) != 1)
				return (0);
		args = args->next;
	}
	free_export_split(export_split);
	free(export_split);
	return (1);
}
