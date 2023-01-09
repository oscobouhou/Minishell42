/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 16:57:45 by oboutarf          #+#    #+#             */
/*   Updated: 2023/01/09 19:41:34 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
// @ ----------------------- #Includes --------------------------- @ //
# include <stdio.h>
# include <stdlib.h> 
# include <unistd.h>
# include <signal.h>
# include <sys/types.h>
# include <readline/history.h>
# include <readline/readline.h>
// @ ------------------------ #Signals ---------------------------- @ //
void	handle_sigint(void);
void	manage_signals(void);
void	sig_handler(int signum);
int		check_eof(char *rdline_outp);
// @ ------------------------- #libft ---------------------------- @ //
void	ft_putchar(char c);
void	ft_putstr(char *str);
int		ft_strlen(char *str);
// @ ------------------------- #Parser --------------------------- @ //
int		parse_rdline_outp(char *rdline_outp);
// @ --------------------------- ### ----------------------------- @ //
#endif
