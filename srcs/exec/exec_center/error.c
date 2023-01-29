/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 10:42:07 by oboutarf          #+#    #+#             */
/*   Updated: 2022/12/17 16:50:46 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	empty_cmd_check(char *str)
{
	int		count_words;
	int		i;

	i = -1;
	count_words = 0;
	while (str[++i])
		if (str[i] != ' ')
			count_words++;
	return (count_words);
}

void	treat_err(int ac, char **av, t_ppx *ppx)
{
	if (ac != 5)
	{
		free(ppx);
		err_msg(ERR_INPUT);
	}
	ppx->infile = open(av[1], O_RDONLY);
	if (ppx->infile < 0)
	{
		ft_putstr_fd("no such file or directory: ", 2);
		ft_putstr_fd(av[1], 2);
		ft_putstr_fd("\n", 2);
	}
	ppx->outfile = open(av[ac - 1], O_TRUNC | O_CREAT | O_RDWR, 0000644);
	if (ppx->outfile < 0)
		err_msg(ERR_FILE);
}

void	err_messages(char *not_found, char **av)
{
	if (av[3] == not_found || av[2] == not_found)
	{
		ft_putstr_fd("commmand not found: ", 2);
		ft_putstr_fd(not_found, 2);
		ft_putstr_fd("\n", 2);
		exit(127);
	}
}

void	err_msg(char *err)
{
	perror(err);
	exit(1);
}
