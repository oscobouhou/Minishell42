/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 16:57:45 by oboutarf          #+#    #+#             */
/*   Updated: 2023/01/13 20:59:20 by oboutarf         ###   ########.fr       */
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
typedef struct s_env
{
	char			*envar;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_tkn
{
	int				type;
	char			*tkn;
	struct s_tkn	*next;
}					t_tkn;

typedef struct s_mshell
{
	char			*rdline_outp;
	uint64_t		exprtc;
	uint64_t		envc;
	t_env			*env;
	t_tkn			*tkn;
	t_env			*exprt;
	t_tkn			*head_tkn;
	int				(*built[7])();
}					t_mshell;
// @ --------------------------- # enums # -------------------------- @ //
enum e_tokens
{
	WORD,
	PIPE,
	SQ_WORD,
	DQ_WORD,
	RDIR_R,
	RDIR_L,
	BUILTIN,
	HEREDOC,
	APPEND,
};

enum e_builtins
{
	CD,
	PWD,
	ENV,
	ECHO,
	EXIT,
	UNSET,
	EXPORT
};

enum e_parse
{
	TREAT_PRINTABLE,
	TREAT_SPACE,
	TREAT_PIPE,
	TREAT_REDIR,
	TREAT_QUOTE
};
// @ -------------------------- # init # ---------------------------- @ //
t_mshell			*init_mshell(char **env);
int					init_t_token(t_mshell *mshell);
int					init_builtins(t_mshell *mshell);
int					init_dependencies(t_mshell *mshell, char **env);
int					obtain_env_content(t_env **lst, char *env);
int					dup_env(t_env **lst, char **env, uint64_t *count);
// @ ------------------------ # builtins # -------------------------- @ //
int					center_builtins(t_mshell *mshell);
int					do_cd(t_mshell *mshell);
int					do_echo(t_mshell *mshell);
int					do_env(t_mshell *mshell);
int					do_exit(t_mshell *mshell);
int					do_export(t_mshell *mshell);
int					do_pwd(t_mshell *mshell);
int					do_unset(t_mshell *mshell);
// @ -------------------------- # token # --------------------------- @ //
int					tokenizer(t_mshell *mshell, int strt, int end);
int					make_new_token(t_mshell *mshell);
// @ ------------------------ # signals # --------------------------- @ //
void				handle_sigint(void);
void				manage_signals(void);
void				sig_handler(int signum);
int					check_eof(char *rdline_outp);
// @ ------------------------- # compose # -------------------------- @ //
int					compose_tkn(t_mshell *mhsell);
// @ ------------------------- # libft # ---------------------------- @ //
void				ft_putchar(char c);
void				ft_putstr(char *str);
int					ft_strlen(char *str);
int					ft_strequal_sign(char *str);
// @ ------------------------- # expand # ---------------------------- @ //
int					ft_expand(char *str, t_env *exprt);
// @ ------------------------- # parser # ---------------------------- @ //
int					sort_kinds(char read);
int					parse_output(t_mshell *mshell);
int					treat_pipe(t_mshell *mshell, int *i);
int					treat_quote(t_mshell *mshell, int *i);
int					treat_space(t_mshell *mshell, int *i);
int					treat_redir(t_mshell *mshell, int *i);
int					treat_hyphen(t_mshell *mshell, int *i);
int					treat_printable(t_mshell *mshell, int *i);
int					search_next_quote(t_mshell *mshell, char quote, int *q);
// @ -------------------------- # free # ----------------------------- @ //
void				terminate(t_mshell *mshell);
void				free_t_env(t_mshell *mshell);
// @ ---------------------------- ### -------------------------------- @ //
#endif
