/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_paths.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 13:51:45 by oboutarf          #+#    #+#             */
/*   Updated: 2023/02/05 02:52:49 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cut_paths(t_mshell *mshell, int start, int *end, int *n_pth)
{
	int	i;

	i = 0;
	mshell->execve->paths[*n_pth] = malloc(sizeof(char) * ((*end - start) + 2));
	if (!mshell->execve->paths[*n_pth])
		return (0);
	while (mshell->env->value[start] && mshell->env->value[start] != ':')
	{
		mshell->execve->paths[*n_pth][i] = mshell->env->value[start];
		start++;
		i++;
	}
	mshell->execve->paths[*n_pth][i] = '/';
	mshell->execve->paths[*n_pth][i + 1] = '\0';
	(*n_pth)++;
	(*end) += 1;
	return (1);
}

int	manage_cut_paths(t_mshell *mshell, int *n_pth)
{
	int	tmp_i;
	int	i;

	i = 0;
	mshell->execve->paths = malloc(sizeof(char *) * (*n_pth + 1));
	if (!mshell->execve->paths)
		return (0);
	mshell->execve->paths[*n_pth] = NULL;
	*n_pth = 0;
	while (mshell->env->value[i])
	{
		tmp_i = i;
		while (mshell->env->value[i] && mshell->env->value[i] != ':')
			i++;
		cut_paths(mshell, tmp_i, &i, n_pth);
		if (i > ft_strlen(mshell->env->value))
			break ;
	}
	return (1);
}

int	count_n_pths(t_mshell *mshell, int *n_pth)
{
	int	i;

	i = 0;
	if (!mshell->env->value)
		return (0);
	while (mshell->env->value[i])
	{
		if (mshell->env->value[i] == ':')
			(*n_pth) += 1;
		i++;
	}
	(*n_pth) += 1;
	return (1);
}

int	parse_paths(t_mshell *mshell)
{
	t_env	*head;
	int		n_pth;

	n_pth = 0;
	head = mshell->env;
	while (mshell->env->next)
	{
		if (!ft_strcmp("PATH", mshell->env->envar))
			break ;
		mshell->env = mshell->env->next;
	}
	if (!count_n_pths(mshell, &n_pth))
		return (0);
	manage_cut_paths(mshell, &n_pth);
	mshell->env = head;
	return (1);
}
