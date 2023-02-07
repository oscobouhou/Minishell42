/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 16:57:45 by oboutarf          #+#    #+#             */
/*   Updated: 2023/02/07 00:25:18 by oboutarf         ###   ########.fr       */
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
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>
# include <signal.h>
# include <sys/wait.h>
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

typedef struct s_built
{
	int				builtin_p;
	int				echo_flag;
	int				echo_args_len;
	char			*cd_arg;
	char			*cd_chdir;
	char			**echo_arg;
}					t_built;

typedef struct s_expt
{
	char			*exptvar;
	char			*value;
	struct s_expt	*next;
}					t_expt;

typedef struct s_tkn
{
	int				type;
	int				pipe_fd_hrdoc[2];
	char			*tkn;
	struct s_tkn	*next;
}					t_tkn;

typedef struct s_exec
{
	int				*fd;
	int				n_fd;
	int				fd_in;
	int				fd_out;
	int				no_cmd;
	int				no_redirs;
	int				p_listener;
	pid_t			pid;
	t_tkn			*start_exec_head;
	t_tkn			*start_exec;
	struct s_exec	*next;
}					t_exec;

typedef struct s_execve
{
	char				*cmd;
	char				**paths;
	char				**cmd_args;
}						t_execve;

typedef struct s_mshell
{
	int				no_env;
	int				empty_cmd;
	int				exit_status;
	int				old_expd__hrdoc;
	int				pipe_fd[2];
	int				pipe_fd_hrdoc[2];
	char			*rdline_outp;
	uint64_t		exprtc;
	uint64_t		envc;
	t_tkn			*tkn;
	t_tkn			*head_tkn;
	t_exec			*exec;
	t_exec			*head_exec;
	t_env			*env;
	t_expt			*expt;
	t_expd			*expd;
	t_built			*built;
	t_execve		*execve;
	char			**exec_env;
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
	_CMD,
	HRDOC_RDIR
};

enum e_builtins
{
	CD,
	PWD,
	ENV,
	ECHO,
	EXIT,
	UNSET,
	EXPRT
};

enum e_parse
{
	TREAT_PRINTABLE,
	TREAT_SPACE,
	TREAT_PIPE,
	TREAT_REDIR,
	TREAT_QUOTE
};

enum e_bool
{
	FALSE,
	TRUE
};

enum e_env_len
{
	VAR,
	VALUE,
	ARG
};
// @ -------------------------- # init # ---------------------------- @ //
t_mshell			*init_mshell(char **env);
int					init_exec(t_mshell *mshell);
int					init_built(t_mshell *mshell);
int					init_t_token(t_mshell *mshell);
int					init_builtins(t_mshell *mshell);
int					init_expansion(t_mshell *mshell);
int					new_node_export(t_mshell *mshell);
int					init_sort_export(t_mshell *mshell);
int					init_execve(t_mshell *mshell, char **env);
int					obtain_env_content(t_env **lst, char *env);
int					begin_command(t_mshell *mshell, char **env);
int					dup_env(t_env **lst, char **env, uint64_t *count);
int					init_env_sorter(t_mshell *mshell, t_env **env_sorter);
// @ ------------------------ # builtins # -------------------------- @ //
char				*new_str(char *input);
int					do_cd(t_mshell *mshell);
int					do_env(t_mshell *mshell);
int					do_pwd(t_mshell *mshell);
int					do_echo(t_mshell *mshell);
int					do_exit(t_mshell *mshell);
int					do_unset(t_mshell *mshell);
int					do_exprt(t_mshell *mshell);
t_env				*create_env_node(char *var);
int					check_arg(char *current_arg);
t_expt				*create_expt_node(char *var);
int					scan_echo_args(t_mshell *mshell);
int					count_echo_args(t_mshell *mshell);
void				builtin_fork_exit(t_mshell *mshell);
int					copy_echo_arg(t_mshell *mshell, int *c);
int					verif_flags(t_mshell *mshell, int *flag);
t_expt				*search_exprt_pos(char *val, t_expt *head);
int					center_builtins(t_mshell *mshell, int type);
char				*catch_enval(t_mshell *mshell, char *envar);
void				append_to_env(t_env **head, t_env *new_node);
int					add_new_envar(char **to_add, t_mshell *mshell);
int					manage_env(char **to_export, t_mshell *mshell);
int					add_new_exptar(char **to_add, t_mshell *mshell);
int					manage_expt(char **to_export, t_mshell *mshell);
void				append_to_expt(t_expt **head, t_expt *new_node);
int					unforked_builtin_redir_treat(t_mshell *mshell, int *backup);
int					change_enval(t_mshell *mshell, char *envar, char *replace);
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
void				stop_signals(void);
void				handle_sigint(void);
void				manage_signals(void);
void				sig_handler(int signum);
int					check_eof(char *rdline_outp);
void				sig_fork_handler(int signum);
// @ ------------------------- # compose # -------------------------- @ //
void				what_token(int token);
int					compose_and_launch_command(t_mshell *mhsell, char **env);
// @ ------------------------- # libft # ---------------------------- @ //
char				*ft_itoa(int n);
int 				ft_nbrlen(int n);
int					ft_isalnum(int c);
int					ft_isalpha(int c);
void				ft_putchar(char c);
void				ft_putstr(char *str);
int					ft_strlen(char *str);
char				*ft_strdup(char *str);
int					ft_atoi(const char *nptr);
char				*ft_strchr(char *s, int c);
int					ft_strequal_sign(char *str);
int					ft_strcmp(char *s1, char *s2);
char				*ft_charcat(char *str, char c);
void				ft_putstr_fd(int fd, char *str);
char				**ft_split(char *s, char target);
char				*ft_convert_to_str(int n, int i);
char				**copy_env_in_tab(t_mshell *mshell);
int					search_lowest(char *val, t_env *env);
char				*ft_substr(char *s, int start, size_t len);
char				*ft_strjoin(char *s1, char *s2, int upend);
// @ -------------------------- # exec # ---------------------------- @ //
int					popen_tube(t_mshell *mshell);
int					bckup_stdin_out(int *backup);
int					pclose_tube(t_mshell *mshell);
int					handle_tube(t_mshell *mshell);
int					find_access(t_mshell *mshell);
void				print_tokens(t_mshell *mshell);
int					scan_builtin(t_mshell *mshell);
char				*exit_status(t_mshell *mshell);
int					close_file_fd(t_mshell *mshell);
int					make_new_exec(t_mshell *mshell);
int					seek_cmd_args(t_mshell *mshell);
int					close_pipe_fds(t_mshell *mshell);
int					set_pos_to_cmd(t_mshell *mshell);
int					search_next_pipe(t_mshell *mshell);
int					re_establish_stdin_out(int *backup);
int					enable_redirections(t_mshell *mshell);
int					copy_cmd_arg(t_mshell *mshell, int *i);
int					make_expand_in_hrdoc(t_mshell *mshell);
int					build_commands_chains(t_mshell *mshell);
int					center_exec(t_mshell *mshell, char **env);
int					set_end_of_command_chain(t_mshell *mshell);
int					exit_builtin(t_mshell *mshell, int *backup);
int					copy_first_cmd_arg(t_mshell *mshell, int *i);
int					join_cmd_for_access(t_mshell *mshell, int *i);
int					execute_hrdoc(t_mshell *mshell, int expander);
int					center_hrdoc_delim_treatment(t_mshell *mshell, \
					int *expander);
// @ ------------------------- # expand # --------------------------- @ //
int					center_expand(t_mshell *mshell);
int					check_expander(t_mshell *mshell);
int					cut_types_expd(t_mshell *mshell);
int					find_types_len_expd(t_mshell *mshell);
char				*join_types_expanded(t_mshell *mshell);
int					manage_expands_in_types(t_mshell *mshell);
int					make_expansion(t_mshell *mshell, char *input);
int					manage_expands_oq(t_mshell *mshell, int n_tp);
int					update_type(t_mshell *mshell, int *i, int n_tp);
int					cut_expander(t_mshell *mshell, int n_tp, int i);
int					manage_expands_in_sq(t_mshell *mshell, int n_tp);
int					manage_expands_in_dq(t_mshell *mshell, int n_tp);
int					remove_closing_quotes_dq(t_mshell *mshell, int n_tp);
int					alloc_new_token_for_join(t_mshell *mshell, int *i0, \
					int *n_tp, int *i1);
int					alloc_new_token_for_join(t_mshell *mshell, int *i0, \
					int *n_tp, int *i1);
void				cutitintypes(t_mshell *mshell, int *tmp_i, int \
					*n_tp, int *i);
// @ ------------------------- # parser # ---------------------------- @ //
int					sort_kinds(char read);
int					parse_paths(t_mshell *mshell);
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
int					copy_and_suppress_env_node(t_mshell *mshell, \
					t_env *env_sorter, t_env *actualise);
// @ ------------------------- # printer # --------------------------- @ //
void				what_token(int token);
// @ -------------------------- # free # ----------------------------- @ //
int					free_exec(t_mshell *mshell);
void				terminate(t_mshell *mshell);
int					free_expd(t_mshell *mshell);
void				free_t_env(t_mshell *mshell);
int					free_built(t_mshell *mshell);
void				free_exprt(t_mshell *mshell);
int					free_execve(t_mshell *mshell);
void				free_tokens(t_mshell *mshell);
void				free_actualise(t_env *actualise);
void				free_env_sorter(t_env *env_sorter);
void				builtin_fork_exit(t_mshell *mshell);
int					free_paths_execve(t_mshell *mshell);
int					free_built_echo_tab(t_mshell *mshell);
int					free_cmd_args_execve(t_mshell *mshell);
// @ -------------------------- # error # ---------------------------- @ //
int					error_manager(char *process, char *tkn, char *error);
void				syntax_error(char *tkn);
// @ ---------------------------- ### -------------------------------- @ //
#endif