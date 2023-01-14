/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_sort_export.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 19:29:41 by oboutarf          #+#    #+#             */
/*   Updated: 2023/01/14 19:32:41 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_actualise(t_env *actualise)
{
	free(actualise->value);
	free(actualise->envar);
	free(actualise->next);
	free(actualise);
}