/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 16:02:44 by tiemen            #+#    #+#             */
/*   Updated: 2022/08/03 14:33:01 by tbouma           ###   ########.fr       */
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

# define P_OUT 0
# define P_IN 1
# define STD_OUT 1
# define STD_IN 0
# define S_OUT 1
# define S_IN 0
# define CUR (i + 1) % 2
# define PREV i % 2


struct	s_redir {
	int	in;
	int	out;
};
// struct	s_redir {
// 	int	in;
// 	int	out;
// };

// struct	s_matrix {
// 	struct s_redir redir;
// 	struct s_pipe_nr_node	*result;
// 	char	**input; //array of the tokens from expantion func
// };

// struct	s_data {
// 	char			**splitted_tokens;
// 	struct s_matrix	matrix;
// };

typedef struct s_node
{
	char			*str;
	int				i;
	struct s_node	*n;
	struct s_node	*p;
}	t_node;

struct	s_pipe_cmd {
	int		fd_in;
	int		fd_out;
	char	**exec_line;
};

struct	s_cmd_info {
	char				**tokens;
	int					token_count;
	int					has_infile;
	int					has_outfile;
	char				*infile; //**infile
	char				*outfile;//**outfile;
	struct s_pipe_cmd	pipe_cmd;
};

struct	s_cmd_lines {
	char				*input_str;
	char				**root_paths;
	char				**all_tokens;
	char				***cmd_lines;
	int					cmd_count;
	struct s_cmd_info	*cmd_info;
	char				**env_var;
	struct s_node		*env_list;
	//pipex
	int					curr_exec_cmd_n;
	pid_t				pid_child;
	int					tube[2];
	struct sigaction	sa;
	
	// t_node				*env_list;
};

//DAN
int	err_chk(int i, int t, char *s);
int	exec(struct	s_cmd_lines	*d);
char	*ft_sjf(char *s1, char *s2, int f);
int	is_builtin(char	*s);
int	exec_builtin(struct	s_cmd_lines	*d, char **s, int n);

//UTILS
int				error_msg(char *msg, int err);
void			perror_msg(char *msg, int err);
int 			free_stuff(char *str);
int				ft_strcmp_var(const char *s1, const char *s2);
int	is_special_char(char c);
char	*ft_substr_edit(char const *s, unsigned int start, size_t len);

//size_t			ft_strlcpy(char *dest, const char *src, size_t dest_size);

//PATH COMMAND
char			**find_path(char **envp);
int	add_path(char **exec_line, char **root_paths);
char			*find_cmd_path(char **path_and_cmd_lines, char **root_paths, char *cmd);

//PARSING_tokens
char			**ft_split_tokens(char const *s);

//PARSING CMD LINES
char			***make_cmd_lines(char **tokens);

//MAKE CMD STRUCTS
int				make_cmd_structs(struct s_cmd_lines *cmd_lines);

//FREE
void	free_struct(struct s_cmd_lines *var);

//LInkedLIST
t_node	*ft_new_node(char *str);
void	ft_list_node_add_back(t_node **node_lst, t_node *new_node);
int	ft_list_size(t_node *lst);
t_node	*ft_list_find_last_node(t_node **list);
void	ft_remove_node(t_node **list, char *var_line);
t_node *find_node_in_list(t_node **list, char *var_line);


//env_var_list
t_node	*add_env_to_list(char **environ);
char	*find_var(t_node **list, char *var_name);
int	expand_var(char **input_str, t_node **list);

//testing
int	print_structs(struct s_cmd_lines *s);
int	print_dubble_str(char **str, char *name);
int	print_linked_list(t_node **list);

#endif