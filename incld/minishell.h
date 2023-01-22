/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 16:57:45 by oboutarf          #+#    #+#             */
/*   Updated: 2023/01/22 12:43:32 by oboutarf         ###   ########.fr       */
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
# define BACKSLSH	92
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

typedef struct s_expd
{
	int				old_expd_len;
	int				new_expd_len;
	int				n_types;
	char			**types;
	char			*expander;
	char			*update_tkn;
}					t_expd;


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

typedef struct s_exec
{
	int				pipe_fd[2];
	int				*fd;
	t_tkn			*start_exec_head;
	t_tkn			*start_exec;
	struct s_exec	*next;
}					t_exec;

typedef struct s_execve
{
	char				*cmd;
	char				**paths;
	char				**cmd_args;
	struct s_execve		*next;
}						t_execve;

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
	t_exec			*exec;
	t_exec 			*head_exec;
	t_env			*env;
	t_expt			*expt;
	t_expd			*expd;
	t_execve		*execve;
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
int					init_exec(t_mshell *mshell);
int					init_t_token(t_mshell *mshell);
int					init_builtins(t_mshell *mshell);
int					init_expansion(t_mshell *mshell);
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
int					redirs_review(t_mshell *mshell);
int					center_review(t_mshell *mshell);
int					make_new_token(t_mshell *mshell);
int					type_next_token(t_tkn *tkn, int type);
void				word_review(t_mshell *mshell, int *cmd_cnt);
int					pipe_review(t_mshell *mshell, int *cmd_cnt);
int					hrdoc_review(t_mshell *mshell, int *cmd_cnt);
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
// @ -------------------------- # exec # ---------------------------- @ //
int					center_exec(t_mshell *mshell);
// @ ------------------------- # expand # --------------------------- @ //
int					center_expand(t_mshell *mshell);
int					check_expander(t_mshell *mshell);
int					cut_types_expd(t_mshell *mshell);
int					treat_expd_hrdoc(t_mshell *mshell);
int					find_types_len_expd(t_mshell *mshell);
int					join_types_expanded(t_mshell *mshell);
int					manage_expands_in_types(t_mshell *mshell);
int					make_expansion(t_mshell *mshell, char *input);
int					manage_expands_oq(t_mshell *mshell, int n_tp);
int					update_type(t_mshell *mshell, int *i, int n_tp);
int					cut_expander(t_mshell *mshell, int n_tp, int i);
int					manage_expands_in_sq(t_mshell *mshell, int n_tp);
int					manage_expands_in_dq(t_mshell *mshell, int n_tp);
int					remove_closing_quotes_dq(t_mshell *mshell, int n_tp);
int					alloc_new_token_for_join(t_mshell *mshell, int *i0, int *n_tp, int *i1);
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
// @ ------------------------- # printer # --------------------------- @ //
void				what_token(int token);
void				print_tokens(t_mshell *mshell);
int					print_exec_chains(t_mshell *mshell);
// @ -------------------------- # free # ----------------------------- @ //
void				terminate(t_mshell *mshell);
void				free_t_env(t_mshell *mshell);
void				free_exprt(t_mshell *mshell);
void				free_tokens(t_mshell *mshell);
void				free_actualise(t_env *actualise);
void				free_env_sorter(t_env *env_sorter);
// @ -------------------------- # error # ---------------------------- @ //
int					error_manager(t_mshell *mshell);
void				syntax_error(void);
// @ ---------------------------- ### -------------------------------- @ //
#endif