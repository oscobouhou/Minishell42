/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 16:57:45 by oboutarf          #+#    #+#             */
/*   Updated: 2023/01/10 22:26:54 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
// @ ------------------------ # Defines # --------------------------- @ //
# define SINGLE_QUOTE 	39			// 		defines: '
# define DOUBLE_QUOTE	34			// 		defines: "
# define PIPE_LINE	124				//		defines: |
# define REDIR_L	60				//		defines: <
# define REDIR_R 	62				//		defines: >
# define EXPAND		36				//		defines: $
// @ ----------------------- # Includes # --------------------------- @ //
# include <stdio.h>
# include <stdlib.h> 
# include <unistd.h>
# include <stdint.h>
# include <signal.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <readline/history.h>
# include <readline/readline.h>
// @ ------------------------ # structures # ------------------------ @ //
typedef struct		s_env
{
	char			*envar;
	char			*value;			 //can be equal to NULL, if NULL, var importer only inside the export, not inside env.
	struct s_env 	*next;
}					t_env;

typedef struct		s_tkn
{
	int				type;
	char			*tkn;
	struct t_tkn	*next;
}					t_tkn;

typedef struct		s_mshell
{
	char			*rdline_outp;
	uint64_t		exprtc;
	uint64_t		envc;
	t_env			*env;			//if == NULL, end of env.
	t_env			*exprt;
	t_tkn			*tkn;
}					t_mshell;
// @ --------------------------- # enums # -------------------------- @ //
enum e_tokens
{
	PIPE,
	WORD,
	HEREDOC,
	STDINPUT,
	STDOUTPUT,
	APPEND,
	DQ_WORD,
	SQ_WORD,
	BUILTIN
};
/* enum e_errs
{
}; */
// @ -------------------------- # init # ---------------------------- @ //
t_mshell			*init_mshell(char **env);
int					center_init(t_mshell *mshell);
t_tkn    			*init_tokens(t_mshell *mshell);
int					dup_env(t_env *lst, char **env, uint64_t *count);
int					obtain_env_content(t_env *lst, char *env);
// @ ------------------------ # builtins # -------------------------- @ //
void				exec_env(t_mshell *shell);
// @ ------------------------ # signals # --------------------------- @ //
void				handle_sigint(void);
void				manage_signals(void);
void				sig_handler(int signum);
int					check_eof(char *rdline_outp);
// @ ------------------------- # libft # ---------------------------- @ //
void				ft_putchar(char c);
void				ft_putstr(char *str);
int					ft_strlen(char *str);
int					ft_strequal_sign(char *str);
// @ ------------------------- # parser # --------------------------- @ //
void				parse_output(t_mshell *mshell);
int					treat_quotes(t_mshell *mshell);
// @ -------------------------- # free # ---------------------------- @ //
void    			terminate(t_mshell *mshell);
void				free_mshell_env(t_mshell *mshell);
// @ ---------------------------- ### ------------------------------- @ //
#endif
