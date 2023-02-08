/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 00:17:03 by oboutarf          #+#    #+#             */
/*   Updated: 2023/02/08 11:33:48 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*new_str(char *input)
{
	char	*new;
	int		i;

	if (!input)
		return (NULL);
	new = malloc(sizeof(char) * (ft_strlen(input) + 1));
	if (!new)
		return (NULL);
	i = 0;
	while (input[i])
	{
		new[i] = input[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

char	*catch_enval(t_mshell *mshell, char *envar)
{
	t_env	*head;
	char	*val;

	head = mshell->env;
	while (mshell->env)
	{
		if (!ft_strcmp(mshell->env->envar, envar))
		{
			val = mshell->env->value;
			mshell->env = head;
			return (val);
		}
		mshell->env = mshell->env->next;
	}
	mshell->env = head;
	return (NULL);
}

int	change_enval(t_mshell *mshell, char *envar, char *replace)
{
	t_env	*head;

	head = mshell->env;
	catch_enval(mshell, envar);
	free(mshell->env->value);
	mshell->env->value = new_str(replace);
	mshell->env = head;
	return (1);
}
