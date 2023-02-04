/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_expt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkermia <dkermia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 11:19:20 by dkermia           #+#    #+#             */
/*   Updated: 2023/02/03 11:34:30 by dkermia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_expt	*create_expt_node(char *var)
{
	t_expt	*new_node;

	new_node = malloc(sizeof(*new_node));
	if (!new_node)
		return (NULL);
	new_node->exptvar = ft_strdup(var);
	new_node->value = NULL;
	new_node->next = NULL;
	return (new_node);
}

void	append_to_expt(t_expt **head, t_expt *new_node)
{
	t_expt	*pos;

	pos = search_exprt_pos(new_node->exptvar, *head);
	if (!head)
		return ;
	if (pos)
	{
		new_node->next = pos->next;
		pos->next = new_node;
	}
	else
		*head = new_node;
}

int	add_new_exptar(char **to_add, t_mshell *mshell)
{
	t_expt		*new_node;

	new_node = create_expt_node(to_add[0]);
	if (!new_node)
		return (0);
	if (to_add[1])
	{
		new_node->value = ft_strdup(to_add[1]);
		if (!new_node->value)
			return (free(new_node), 0);
	}
	append_to_expt(&mshell->expt, new_node);
	return (1);
}

int	replace_value(t_expt *export, char **to_export)
{
	if (export->value)
		free(export->value);
	export->value = to_export[1];
	return (free(to_export[0]), free(to_export), 1);
}

int	manage_expt(char **to_export, t_mshell *mshell)
{
	int			plus_index;
	t_expt		*export;

	export = mshell->expt;
	plus_index = 0;
	if (to_export[0] && ft_strchr(to_export[0], '+') != NULL)
	{
		plus_index = ft_strlen(to_export[0]) - 1;
		to_export[0][plus_index] = '\0';
	}
	while (export && export->exptvar && \
	ft_strcmp(export->exptvar, to_export[0]) != 0)
		export = export->next;
	if (export && export->exptvar && to_export[1] && plus_index == 0)
		return (replace_value(export, to_export));
	if (export && export->exptvar && plus_index)
	{
		export->value = ft_strjoin(export->value, to_export[1], 1);
		if (!export->value)
			return (0);
	}
	if (!export || !export->exptvar)
		if (add_new_exptar(to_export, mshell) == 0)
			return (0);
	return (mshell->exprtc++, 1);
}
