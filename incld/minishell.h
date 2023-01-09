/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 16:57:45 by oboutarf          #+#    #+#             */
/*   Updated: 2023/01/09 22:31:47 by oboutarf         ###   ########.fr       */
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
// @ ----------------------- # structures # ------------------------- @ //
typedef struct		s_env
{
	char			*envar;
	struct s_env 	*next;
}					t_env;

typedef struct	s_mshell
{
	t_env		*env;
}				t_mshell;
// @ -------------------------- # init # ---------------------------- @ //
void		obtain_envar_content(t_mshell *mshell, char **env, int i);
void		dup_env(t_mshell *mshell, char **env);
t_mshell	*init_struct(char **env);
// @ ------------------------ # builtins # -------------------------- @ //
void	exec_env(t_mshell *shell);
// @ ------------------------ # signals # --------------------------- @ //
void	handle_sigint(void);
void	manage_signals(void);
void	sig_handler(int signum);
int		check_eof(char *rdline_outp);
// @ ------------------------- # libft # ---------------------------- @ //
void	ft_putchar(char c);
void	ft_putstr(char *str);
int		ft_strlen(char *str);
// @ ------------------------- # parser # --------------------------- @ //
int		parse_rdline_outp(char *rdline_outp);
// @ -------------------------- # free # ---------------------------- @ //
void	free_mshell_env(t_mshell *mshell);
void    terminate(t_mshell *mshell);
// @ ---------------------------- ### ------------------------------- @ //
#endif
