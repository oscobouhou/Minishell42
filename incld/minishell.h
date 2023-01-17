/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 16:57:45 by oboutarf          #+#    #+#             */
/*   Updated: 2023/01/17 20:45:40 by oboutarf         ###   ########.fr       */
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

typedef struct s_expt
{
	char			*exptvar;
	char			*value;
	struct s_expt	*next;
}					t_expt;

typedef struct s_tkn
{
	int				type;
	char			*tkn;
	struct s_tkn	*next;
}					t_tkn;

typedef struct s_err
{
	int				(*parse_err[3])();
}					t_err;

typedef struct s_mshell
{
	char			*rdline_outp;
	uint64_t		exprtc;
	uint64_t		envc;
	t_tkn			*tkn;
	t_tkn			*head_tkn;
	t_env			*env;
	t_expt			*expt;
	t_err			*error;
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
	APPEND,
	HRDOC,
	DLIM_HRDOC,
	_FILE,
	_ARG,
	_CMD
};

enum e_parserr
{
	PIPE_ERR,
	QUOTE_ERR,
	REDIR_ERR
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
int					new_node_export(t_mshell *mshell);
int					init_sort_export(t_mshell *mshell);
int					obtain_env_content(t_env **lst, char *env);
int					init_dependencies(t_mshell *mshell, char **env);
int					dup_env(t_env **lst, char **env, uint64_t *count);
int					init_env_sorter(t_mshell *mshell, t_env **env_sorter);
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
int					review_tokens(t_mshell *mshell);
int					make_new_token(t_mshell *mshell);
int					tokenizer(t_mshell *mshell, int strt, int end);
// @ ------------------------ # signals # --------------------------- @ //
void				handle_sigint(void);
void				manage_signals(void);
void				sig_handler(int signum);
int					check_eof(char *rdline_outp);
// @ ------------------------- # compose # -------------------------- @ //
void				what_token(int token);
int					compose_tkn(t_mshell *mhsell);
// @ ------------------------- # libft # ---------------------------- @ //
void				ft_putchar(char c);
void				ft_putstr(char *str);
int					ft_strlen(char *str);
int					ft_strequal_sign(char *str);
int					ft_strcmp(char *s1, char *s2);
int					search_lowest(char *val, t_env *env);
// @ ------------------------- # expand # ---------------------------- @ //
int					is_expand(t_mshell*mshell);
int					center_expand(t_mshell *mshell);
int					check_valid_expand(t_mshell *mshell, int *i);
int					suppress_expand(t_mshell *mshell, int start, int len);
int					make_expand(t_mshell *mshell, char *expander, int len);
int					search_expand_in_export(t_mshell *mshell, char *expander);
// @ ------------------------- # parser # ---------------------------- @ //
int					sort_kinds(char read);
int					sort_export(t_mshell *mshell);
int					parse_output(t_mshell *mshell);
int					check_printable_char(char print);
int					treat_pipe(t_mshell *mshell, int *i);
int					treat_quote(t_mshell *mshell, int *i);
int					treat_space(t_mshell *mshell, int *i);
int					treat_redir(t_mshell *mshell, int *i);
int					treat_printable(t_mshell *mshell, int *i);
int					copy_env_content(t_env *dest, t_env *src);
int					copy_env_sorter_content(t_expt *dest, t_env *src);
int					search_next_quote(t_mshell *mshell, char quote, int *q);
int					copy_and_suppress_env_node(t_mshell *mshell, t_env *env_sorter, t_env *actualise);
// @ -------------------------- # free # ----------------------------- @ //
void				terminate(t_mshell *mshell);
void				free_t_env(t_mshell *mshell);
void				free_exprt(t_mshell *mshell);
void				free_tokens(t_mshell *mshell);
void				free_actualise(t_env *actualise);
void				free_env_sorter(t_env *env_sorter);
// @ ---------------------------- ### -------------------------------- @ //
#endif