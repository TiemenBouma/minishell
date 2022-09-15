/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 16:02:44 by tiemen            #+#    #+#             */
/*   Updated: 2022/09/15 12:05:33 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include "libft/libft.h"
# include <unistd.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <sys/param.h>
# include <signal.h>
# include <termios.h>
# include <errno.h>
//linux
# include <sys/types.h>
# include <sys/wait.h>

# define ERR_FILE		"Infile or outfile error"
# define ERR_FORK		"Fork error"
# define ERR_INPUT		"Invalid number of arguments"
# define ERR_PIPE		"Pipe error"
# define ERR_CMD		"command not found"
# define ERR_MALLOC		"Malloc error"
# define ERR_DUP		"Dup2 error"
# define ERR_PROCCES	"Procces error"
# define ERR_EXEC		"Execve error"
# define ERR_PATH		"Path error"
# define EXIT_CD 1
# define EXIT_PWD 1
# define P_OUT 0
# define P_IN 1
# define STD_OUT 1
# define STD_IN 0
# define S_OUT 1
# define S_IN 0
# define GREATER 20
# define SMALLER 21
# define HEREDOC 22
# define APPEND 23
# define CD_BUILD 0
# define EXPORT_BUILD 1
# define UNSET_BUILD 2
# define ECHO_BUILD 3
# define PWD_BUILD 4
# define ENV_BUILD 5
# define EXIT_BUILD 6

typedef struct s_node
{
	char				*str;
	int					i;
	struct s_node		*n;
	struct s_node		*p;
}	t_node;

struct	s_cmd_info {
	int					fd_in;
	int					fd_out;
	char				**exec_line;
	int					cmd_count;
	int					cmd_index;
	char				**curr_line_tokens;
	int					token_count;
	int					has_infile;
	int					has_outfile;
	int					has_appendfile;
	int					has_heredoc;
	int					heredoc_pipe[2];
	char				*infile;
	char				*outfile;
	char				*appendfile;
	char				*heredoc;
	int					heredoc_fd_opened;
	int					set_file_err;
	int					err_syntax;
	struct s_node		*env_llist;
	char				**e_list;
};

/*
oxs = old exit status
*/
struct	s_main {
	char				*input_str;
	char				**root_paths;
	char				**all_tokens;
	char				***cmd_lines;
	int					cmd_count;
	struct s_cmd_info	*c_s_arr;
	struct s_node		*env_llist;
	int					oxs;
	int					err;
	int					minishell_nr;
};

//MAIN_ERROR
int						basic_error_handeling(struct s_main *m_s);
int						check_error(struct s_main *m_s);

//DAN
int						err_chk(int i, int t, char *s);
int						exec(struct	s_main *m_s);
char					*ft_sjf(char *s1, char *s2, int f);

//BUILDIN's
int						is_builtin(char	*s);
int						exec_builtin(struct s_main *m_s,
							struct s_cmd_info *cmd_struct, int build_n);
int						check_buildin_fork(struct s_cmd_info *cmd_struct);
char					*make_var_name(char *var_line);
int						ft_exit(char **s, int is_in_child, struct s_main *m_s);
int						ft_cd(t_node **list, char ***exec_line);
void					ft_echo(char **s);
void					ft_env(t_node **list);
int						ft_export(t_node **list, char **exec_line);
void					ft_pwd(t_node **list);
int						ft_unset(t_node **list, char **exec_line);

//UTILS
int						error_msg(char *msg, int err);
int						perror_msg(char *cmd, char *att, int exit_status);
int						free_stuff(char *str);
int						ft_strcmp_var(const char *s1, const char *s2);
int						is_special_char(char c);
char					*ft_substr_edit(char const *s,
							unsigned int start, size_t len);
char					**make_arr_from_list(t_node **list);
int						check_n_flag(char *flag);

//PATH COMMAND
char					**find_path(t_node **list);
int						add_path(char **exec_line, char **root_paths);
char					*find_cmd_path(char **path_and_cmd_lines,
							char **root_paths, char *cmd);

//PARSING_tokens
char					**split_tokens(char const *s);
int						find_end_token(char const *input_str, int *index);

//PARSING CMD LINES
char					***make_cmd_lines(char **curr_line_tokens);

//MAKE CMD STRUCTS
int						make_cmd_structs(struct s_main *cmd_lines);
int						is_arrow_sign(char *str);

//FREE
void					free_struct(struct s_main *var);

//LInkedLIST
t_node					*ft_new_node(char *str);
void					ft_list_node_add_back(t_node **node_lst,
							t_node *new_node);
int						ft_list_size(t_node *lst);
t_node					*ft_list_find_last_node(t_node **list);
void					ft_remove_node(t_node **list, t_node *node_to_remove);
t_node					*ft_find_node_in_list(t_node **list,
							char *var_line);
void					ft_find_and_remove_node(t_node **list, char *var_line);
int						ft_replace_node_content(t_node *first_node,
							char *var_line);
void					ft_find_and_edit_node(t_node **list, char *var_name,
							char *content);
int						ft_free_linked_list(t_node **list);
void					ft_add_or_change_list(t_node **list, t_node *match_node,
							char *exec_line);

//env_var_list
t_node					*add_env_to_list(struct s_main *m_s, char **environ);
char					*find_var(t_node **list, char *var_name);
int						ft_print_var_content(t_node **list, char *var_name);
char					*find_var_in_list(t_node **list, char *var_name);
void					inc_shlvl(struct s_main *m_s, t_node **list);

//expand var
void					expand_variables(struct s_main *m_s);
int						find_len_var_name(char **in, int s);
void					replace_input(char **in, char *content, int *i,
							char *v_name);
void					replace_input1(struct s_main *m_s, char *v_name,
							int *index);

//expand var HEREDOC
void					expand_variables_heredoc(char **input,
							t_node **list, int oxs, int index);

//SIGNALS
void					sigint_handler(int sig);
void					signals_handeler(void);
void					sigint_handler_in_process(int sig);
void					sigquit_handler_in_process(int sig);
void					sigint_handler_nonl(int sig);
void					ft_suppress_output(void);
void					sigquit_handler_in_process_minishell(int sig);

//HEREDOC
int						heredoc(struct s_main *m_s, char *stop_word, int index);
char					*make_heredoc_filename(int index);
int						heredoc_counter(char **curr_line_tokens);
int						dummy_heredoc(char *stop_word);

//testing
int						print_structs(struct s_main *s);
int						print_dubble_str(char **str, char *name);
int						print_linked_list(t_node **list);

//Parsing_redir
int						heredoc_redir_check(struct s_main *m_s,
							struct s_cmd_info *cmd_struct);
int						redir_check(struct s_cmd_info *cmd_struct);

//parsing_redir_open_fd
int						open_fd_out_append(struct s_cmd_info *cmd_struct);
int						open_fd_out(struct s_cmd_info *cmd_struct);
int						open_fd_in(struct s_cmd_info *cmd_struct);
void					error_exit_redir(char *str);

//parsing_redir_utils
int						is_arrow_sign(char *str);
int						is_special_c_redir(char *str);
void					set_redir_error(struct s_cmd_info *cmd_struct,
							char *token);

//parsing_make_exec_line
int						make_exec_line(struct s_cmd_info *cmd_struct);

//FREE
void					free_double_str(char **str);

#endif