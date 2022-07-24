/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 16:02:44 by tiemen            #+#    #+#             */
/*   Updated: 2022/07/24 14:01:38 by tbouma           ###   ########.fr       */
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
};

//DAN
int	err_chk(int i, int t, char *s);
int	exec(struct	s_cmd_lines	*d);
char	*ft_sjf(char *s1, char *s2, int f);

//UTILS
void			error_msg(char *msg, int err);
void			perror_msg(char *msg, int err);
int 			free_stuff(char *str);
//size_t			ft_strlcpy(char *dest, const char *src, size_t dest_size);

//PATH COMMAND
char			**find_path(char **envp);
char			*find_cmd_path(char **path_and_cmd_lines, char **root_paths, char *cmd);

//PARSING_tokens
char			**ft_split_tokens(char const *s, char c);

//PARSING CMD LINES
char			***make_cmd_lines(char **tokens);

//MAKE CMD STRUCTS
int				make_cmd_structs(struct s_cmd_lines *cmd_lines);

//SPLIT BASH
char			**ft_split_tokens(char const *s, char c);

//testing
int	print_structs(struct s_cmd_lines *s);

#endif