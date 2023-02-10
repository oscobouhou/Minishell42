/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 16:57:45 by oboutarf          #+#    #+#             */
/*   Updated: 2023/02/10 16:30:17 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
// @ ------------------------ # Defines # --------------------------- @ //
# define WRITE_ERR "minishell: echo: write error: No space left on \
your device\n"
# define CD_ERR_ARG "minishell: cd: too many arguments\n"
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
	char				*envar;
	char				*value;
	struct s_env		*next;
}						t_env;

typedef struct s_heredoc
{
	int					pipe_heredoc[2];
	struct s_heredoc	*next;
}						t_heredoc;

typedef struct s_expd
{
	int					old_expd_len;
	int					new_expd_len;
	int					n_types;
	char				**types;
	char				*expander;
	char				*update_tkn;
}						t_expd;

typedef struct s_built
{
	int					builtin_p;
	int					echo_flag;
	int					echo_args_len;
	int					export_args_len;
	char				*cd_arg;
	char				*cd_chdir;
	char				**echo_arg;
	char				**export_arg;
	char				*export_var;
	char				*export_value;
}						t_built;

typedef struct s_expt
{
	char				*exptvar;
	char				*value;
	struct s_expt		*next;
}						t_expt;

typedef struct s_tkn
{
	int					type;
	int					pipe_fd_hrdoc[2];
	char				*tkn;
	struct s_tkn		*next;
}						t_tkn;

typedef struct s_exec
{
	int					*fd;
	int					n_fd;
	int					fd_in;
	int					fd_out;
	int					no_cmd;
	int					no_redirs;
	int					p_listener;
	pid_t				pid;
	t_tkn				*start_exec_head;
	t_tkn				*start_exec;
	struct s_exec		*next;
}						t_exec;

typedef struct s_execve
{
	char				*cmd;
	char				**paths;
	char				**cmd_args;
}						t_execve;

typedef struct s_mshell
{
	int					no_env;
	int					empty_cmd;
	int					exit_status;
	int					dup_heredoc;
	int					old_expd__hrdoc;
	int					pipe_fd[2];
	char				*rdline_outp;
	uint64_t			exprtc;
	uint64_t			envc;
	char				**exec_env;
	t_heredoc			*hd_heredoc;	
	t_heredoc			*heredoc;
	t_tkn				*tkn;
	t_tkn				*head_tkn;
	t_exec				*exec;
	t_exec				*head_exec;
	t_env				*env;
	t_env				*head_env;
	t_expt				*expt;
	t_expt				*head_expt;
	t_expd				*expd;
	t_built				*built;
	t_execve			*execve;
}						t_mshell;
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

extern int	g_exit;

// @ -------------------------- # init # ---------------------------- @ //
t_mshell			*init_mshell(char **env);
int					init_exec(t_mshell *mshell);
int					init_built(t_mshell *mshell);
int					init_t_token(t_mshell *mshell);
int					init_heredoc(t_mshell *mshell);
int					init_builtins(t_mshell *mshell);
int					init_expansion(t_mshell *mshell);
int					copy_underscore(t_mshell *mshell);
int					set_default_env(t_mshell *mshell);
int					new_node_export(t_mshell *mshell);
int					make_new_heredoc(t_mshell *mshell);
int					init_sort_export(t_mshell *mshell);
int					set_default_export(t_mshell *mshell);
int					set_default_envars(t_mshell *mshell);
int					fill_default_export(t_mshell *mshell);
int					copy_shlvl(t_mshell *mshell, char *shlvl);
int					init_execve(t_mshell *mshell, char **env);
int					obtain_env_content(t_env **lst, char *env);
int					begin_command(t_mshell *mshell, char **env);
int					dup_env(t_env **lst, char **env, uint64_t *count);
int					copy_pwd(t_mshell *mshell, char *pwd_var, char *pwd);
int					init_env_sorter(t_mshell *mshell, t_env **env_sorter);
// @ ------------------------ # builtins # -------------------------- @ //
// #  STD BUILT
int					bckup_stdin_out(int *backup);
int					re_establish_stdin_out(int *backup);
int					exit_builtin(t_mshell *mshell, int *backup, int exit_code);
int					unforked_builtin_redir_treat(t_mshell *mshell, int *backup);
// #  CD
int					do_cd(t_mshell *mshell);
int					cd_home(t_mshell *mshell);
int					cd_tilde(t_mshell *mshell);
int					copy_cd_arg(t_mshell *mshell);
int					absolute_path(t_mshell *mshell);
int					cd_args_checker(t_mshell *mshell);
int					special_cd(t_mshell *mshell, char *path, int *backup);
int					cd_join_pwd_to_directory(t_mshell *mshell, char *path);
int					assembling_pwdir__cd(t_mshell *mshell, char *path, int i, \
					int j);
// # ENV
char				*new_str(char *input);
int					do_env(t_mshell *mshell);
char				*catch_enval(t_mshell *mshell, char *envar);
int					change_enval(t_mshell *mshell, char *envar, char *replace);
// # ECHO
int					do_echo(t_mshell *mshell);
int					scan_echo_args(t_mshell *mshell);
int					count_echo_args(t_mshell *mshell);
int					print_echo_args(t_mshell *mshell);
int					copy_echo_arg(t_mshell *mshell, int *c);
int					verif_flags(t_mshell *mshell, int *flag);
int					echo_printer(char *to_print, t_mshell *mshell);
// 
int					do_pwd(t_mshell *mshell);
// # EXIT
int					do_exit(t_mshell *mshell);
int					exit_numeric_char(t_mshell *mshell);
int					exit_types(t_mshell *mshell, int arg);
int					do_exit_too_many_arg(t_mshell *mshell);
int					do_exit_numeric_error(t_mshell *mshell);
int					count_number_args_exit(t_mshell *mshell);
//
int					do_unset(t_mshell *mshell);
// # EXPORT
int					do_exprt(t_mshell *mshell);
int					set_arg_tab(t_mshell *mshell);
int					declare_export(t_mshell *mshell);
int					check_existing(t_mshell *mshell);
int					cut_args_in_tab(t_mshell *mshell);
int					fill_environement(t_mshell *mshell);
int					replace_env_value(t_mshell *mshell);
int					replace_export_value(t_mshell *mshell);
int					create_new_var_export(t_mshell *mshell);
int					treat_export_arg(t_mshell *mshell, int i);
int					export_new_var_value_env(t_mshell *mshell);
int					export_new_var_value_export(t_mshell *mshell);
int					cut_expt_var(t_mshell *mshell, char *to_expt, int i);
int					cut_expt_value(t_mshell *mshell, char *to_expt, int i);
int					check_export_assignement(t_mshell *mshell, char *to_expt);
//
t_env				*create_env_node(char *var);
int					check_arg(char *current_arg);
t_expt				*create_expt_node(char *var);
void				builtin_fork_exit(t_mshell *mshell);
int					copy_echo_arg(t_mshell *mshell, int *c);
int					verif_flags(t_mshell *mshell, int *flag);
t_expt				*search_exprt_pos(char *val, t_expt *head);
int					center_builtins(t_mshell *mshell, int type);
void				append_to_env(t_env **head, t_env *new_node);
int					add_new_envar(char **to_add, t_mshell *mshell);
int					manage_env(char **to_export, t_mshell *mshell);
int					add_new_exptar(char **to_add, t_mshell *mshell);
int					manage_expt(char **to_export, t_mshell *mshell);
void				append_to_expt(t_expt **head, t_expt *new_node);
// @ -------------------------- # token # --------------------------- @ //
int					redirs_review(t_mshell *mshell);
int					center_review(t_mshell *mshell);
int					make_new_token(t_mshell *mshell);
int					type_next_token(t_tkn *tkn, int type);
void				word_review(t_mshell *mshell, int *cmd_cnt);
int					pipe_review(t_mshell *mshell, int *cmd_cnt);
int					hrdoc_review(t_mshell *mshell, int *cmd_cnt);
int					tokenizer(t_mshell *mshell, int strt, int end);
int					suppress_heredoc_token(t_mshell *mshell, t_tkn *tmp);
int					review_nxt_after_pipe(t_mshell *mshell, int *cmd_cnt);
// @ ------------------------ # signals # --------------------------- @ //
void				stop_signals(void);
void				handle_sigint(void);
void				handle_sigquit(void);
void				manage_signals(void);
void				handle_sigint_hd(void);
void				retrieve_signals(void);
void				sig_handler(int signum);
void				handle_sigint_fork(void);
void				stop_signals_heredoc(void);
int					check_eof(char *rdline_outp);
void				sig_fork_handler(int signum);
int					sigint_exit(t_mshell *mshell);
void				sig_heredoc_handler(int signum);
// @ ------------------------- # compose # -------------------------- @ //
void				what_token(int token);
int					compose_and_launch_command(t_mshell *mhsell, char **env);
// @ ------------------------- # libft # ---------------------------- @ //
char				*ft_itoa(int n);
int					ft_nbrlen(int n);
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
void				cmd_err_message(char *cmd);
int					wait_pids(t_mshell *mshell);
int					controler(t_mshell *mshell);
int					popen_tube(t_mshell *mshell);
int					hrdoc_rdir(t_mshell *mshell);
int					absolute_cmd_exec(char *tkn);
int					pclose_tube(t_mshell *mshell);
int					handle_tube(t_mshell *mshell);
int					find_access(t_mshell *mshell);
int					scan_builtin(t_mshell *mshell);
char				*exit_status(t_mshell *mshell);
int					new_exec_line(t_mshell *mshell);
int					close_file_fd(t_mshell *mshell);
int					make_new_exec(t_mshell *mshell);
int					seek_cmd_args(t_mshell *mshell);
int					close_heredocs(t_mshell *mshell);
int					close_pipe_fds(t_mshell *mshell);
int					set_pos_to_cmd(t_mshell *mshell);
int					append(t_mshell *mshell, int *fd);
int					rdir_l(t_mshell *mshell, int *fd);
int					rdir_r(t_mshell *mshell, int *fd);
int					search_next_pipe(t_mshell *mshell);
int					heredoc_controler(t_mshell *mshell);
int					start_cmd_pipeline(t_mshell *mshell);
int					enable_redirections(t_mshell *mshell);
int					copy_cmd_arg(t_mshell *mshell, int *i);
int					make_expand_in_hrdoc(t_mshell *mshell);
int					build_commands_chains(t_mshell *mshell);
int					cut_types_expd__hrdoc(t_mshell *mshell);
int					alloc__hrdoc_for_join(t_mshell *mshell);
int					lens_types_expd__hrdoc(char *usr_input);
int					unforked(t_mshell *mshell, int *backup);
int					eof_err_heredoc(t_mshell *mshell, int l);
int					start_exec(t_mshell *mshell, int *backup);
int					center_exec(t_mshell *mshell, char **env);
int					set_end_of_command_chain(t_mshell *mshell);
int					exec_heredoc(t_mshell *mshell, int expander);
int					find_types_len_expd__hrdoc(t_mshell *mshell);
int					copy_first_cmd_arg(t_mshell *mshell, int *i);
int					no_cmd_no_pipe(t_mshell *mshell, int *backup);
char				*join_types_expanded__hrdoc(t_mshell *mshell);
int					join_cmd_for_access(t_mshell *mshell, int *i);
int					execute_hrdoc(t_mshell *mshell, int expander);
int					skip_pipe_token(t_mshell *mshell, t_tkn *skip);
int					init_cut_types_expander__hrdoc(t_mshell *mshell);
int					gather_usr_input(char *content, t_mshell *mshell);
void				exit_process(int err, char *tkn, t_mshell *mshell);
int					hrdoc_expander(char **usr_input, t_mshell *mshell);
int					delimiter_detected(char *usr_input, t_mshell *mshell);
int					make_expands_types__hrdoc(t_mshell *mshell, int n_tp);
int					eof_heredoc(char *usr_input, t_mshell *mshell, int line);
int					joinit_heredoc(t_mshell *mshell, char **new_token, \
					int n_tp, int *i1);
int					types_expd_cut_usr_input__hrdoc(t_mshell *mshell, \
					char *usr_input, int *n_tp, int *i);
int					types_expd_cut_expander__hrdoc(t_mshell *mshell, \
					char *usr_input, int *n_tp, int *i);
void				cutitintypes_heredoc(t_mshell *mshell, int *tmp_i, \
					int *n_tp, int *i);
int					dup_expander___hrdoc(t_mshell *mshell, char *exptval, \
					int n_tp);
int					treat_double_quote_expand_cut__hrdoc(t_mshell *mshell, \
					int *i, int *tmp_i, int *n_tp);
int					treat_single_quote_expand_cut__hrdoc(t_mshell *mshell, \
					int *i, int *tmp_i, int *n_tp);
int					treat_out_quote_expand_cut__hrdoc(t_mshell *mshell, \
					int *i, int *tmp_i, int *n_tp);
int					lens_types_expd__hrdoc(char *usr_input);
int					check_expander__hrdoc(char *expander, t_mshell *mshell, \
					int n_tp);
int					types_expd_cut__hrdoc(t_mshell *mshell, char *usr_input, \
					int n_tp);
int					center_hrdoc_delim_treatment(t_mshell *mshell, \
					int *expander);
// @ ------------------------- # expand # --------------------------- @ //
int					center_expand(t_mshell *mshell);
int					check_expander(t_mshell *mshell);
int					cut_types_expd(t_mshell *mshell);
int					new_command_line(t_mshell *mshell);
int					find_types_len_expd(t_mshell *mshell);
char				*join_types_expanded(t_mshell *mshell);
int					scan_herdoc(t_mshell *mshell, int n_tp);
int					init_cut_types_expander(t_mshell *mshell);
int					manage_expands_in_types(t_mshell *mshell);
int					hrdoc_scannner(t_mshell *mshell, int n_tp);
int					make_expansion(t_mshell *mshell, char *input);
int					manage_expands_oq(t_mshell *mshell, int n_tp);
int					update_type(t_mshell *mshell, int *i, int n_tp);
int					single_dollar_in_dq(t_mshell *mshell, int n_tp);
int					update_type(t_mshell *mshell, int *i, int n_tp);
int					cut_expander(t_mshell *mshell, int n_tp, int i);
int					manage_expands_in_sq(t_mshell *mshell, int n_tp);
int					manage_expands_in_dq(t_mshell *mshell, int n_tp);
int					remove_closing_quotes_dq(t_mshell *mshell, int n_tp);
int					get_all_content_from_string(t_mshell *mshell, int n_tp);
int					skip_hexpander_hrdoc(t_mshell *mshell, int n_tp, int *i);
int					treat_export_exit_status(t_mshell *mshell, int n_tp, int i);
void				cutitintypes(t_mshell *mshell, int *tmp_i, \
					int *n_tp, int *i);
int					check_update_string_with_expand(t_mshell *mshell, \
					int n_tp, int *i);
int					update_type_expanded(t_mshell *mshell, int *ptr, \
					int n_tp, char **update);
int					update_type_no_expand(t_mshell *mshell, int *ptr, \
					int n_tp, char **update);
int					alloc_new_token_for_join(t_mshell *mshell, int *i0, \
					int *n_tp, int *i1);
int					close_string_after_expand_update(t_mshell *mshell, \
					int *ptr, char **update, int n_tp);
// @ ------------------------- # parser # ---------------------------- @ //
int					sort_kinds(char read);
char				*remove_quotes(char *str);
char				*init_rm_quotes(char *str);
int					parse_paths(t_mshell *mshell);
int					sort_export(t_mshell *mshell);
int					parse_output(t_mshell *mshell);
int					center_quotes(t_mshell *mshell);
int					check_printable_char(char print);
int					treat_pipe(t_mshell *mshell, int *i);
int					check_closed_quotes(t_mshell *mshell);
int					treat_quote(t_mshell *mshell, int *i);
int					treat_space(t_mshell *mshell, int *i);
int					treat_redir(t_mshell *mshell, int *i);
int					treat_printable(t_mshell *mshell, int *i);
int					copy_env_content(t_env *dest, t_env *src);
int					closed_quotes(t_mshell *mshell, int *i, int qt);
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
int					free_heredoc(t_mshell *mshell);
void				free_actualise(t_env *actualise);
void				free_env_sorter(t_env *env_sorter);
void				builtin_fork_exit(t_mshell *mshell);
int					free_paths_execve(t_mshell *mshell);
int					free_built_echo_tab(t_mshell *mshell);
int					free_cmd_args_execve(t_mshell *mshell);
// @ -------------------------- # error # ---------------------------- @ //
void				syntax_error(char *tkn);
int					open_error(t_mshell *mshell);
int					export_numeric_error(t_mshell *mshell);
int					error_manager(char *process, char *tkn, char *error);
// @ ---------------------------- ### -------------------------------- @ //
#endif