/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 20:51:18 by oboutarf          #+#    #+#             */
/*   Updated: 2023/02/07 12:19:42 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_current_unset_arg(char *arg)
{
	int	i;

	i = 0;
	if (!arg)
		return (0);
	if (!ft_isalpha(*arg) || *arg == '_')
		return (0);
	while (ft_isalnum(arg[i]) || arg[i] == '_')
		i++;
	if (arg[i] == '\0')
		return (2);
	if (arg[i] == '+' && arg[i + 1] == '=')
		return (1);
	if (arg[i] == '=')
		return (1);
	return (0);
}

void	remove_env(char *to_rm, t_mshell *mshell)
{
	t_env	*env;
	t_env	*prev;

	prev = NULL;
	env = mshell->env;
	if (!env)
		return ;
	while (env->next && env->envar && ft_strcmp(env->envar, to_rm) != 0)
	{
		prev = env;
		env = env->next;
	}
	if (!prev)
		mshell->env = env->next;
	else
		prev->next = env->next;
	free(env->envar);
	free(env->value);
	free(env);
}

void	remove_expt(char *to_rm, t_mshell *mshell)
{
	t_expt	*export;
	t_expt	*prev;

	prev = NULL;
	export = mshell->expt;
	if (!export)
		return ;
	while (export->next && export->exptvar && \
	ft_strcmp(export->exptvar, to_rm) != 0)
	{
		prev = export;
		export = export->next;
	}
	if (!export && !export->exptvar)
		return ;
	if (!prev)
		mshell->expt = export->next;
	else
		prev->next = export->next;
	free(export->exptvar);
	if (export->value)
		free(export->value);
	free(export);
}

int	close_fd(t_mshell *mshell)
{
	if (mshell->exec->no_redirs != -42)
		close_file_fd(mshell);
	if (mshell->built->builtin_p == 42)
	{
		if (mshell->exec->next)
			close_pipe_fds(mshell);
		terminate(mshell);
		exit(0);
	}
	return (1);
}

int	do_unset(t_mshell *mshell)
{
	t_tkn	*args;
	int		backup[2];

	unforked_builtin_redir_treat(mshell, backup);
	mshell->exec->start_exec = mshell->exec->start_exec_head;
	if (mshell->exec->start_exec->next == NULL)
		return (1);
	args = mshell->exec->start_exec->next;
	while (args != NULL && args->tkn != NULL)
	{
		if (!check_current_unset_arg(args->tkn))
		{
			error_manager("unset", args->tkn, "not a valid identifier");
			args = args->next;
			continue ;
		}
		remove_env(args->tkn, mshell);
		remove_expt(args->tkn, mshell);
		args = args->next;
	}
	close_fd(mshell);
	re_establish_stdin_out(backup);
	mshell->exit_status = 0;
	return (1);
}
