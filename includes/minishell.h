/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 16:02:44 by tiemen            #+#    #+#             */
/*   Updated: 2022/07/21 11:08:33 by tbouma           ###   ########.fr       */
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

struct	s_redir {
	int	in;
	int	out;
};

struct	s_pipe_nr_node {
	int		in;
	int		out;
	char	*exec_line;
};

struct	s_matrix {
	struct s_redir redir;
	struct s_pipe_nr_node	*result;
	char	**input; //array of the tokens from expantion func

};

struct	s_data {
char			**splitted_tokens;
struct s_matrix	matrix;

};

//UTILS
void	error_msg(char *msg, int err);
void	perror_msg(char *msg, int err);
int free_stuff(char *str);
size_t	ft_strlcpy(char *dest, const char *src, size_t dest_size);

//PATH COMMAND
char	**find_path(char **envp);
char	*find_cmd_path(char **root_paths, char *cmd);

//PARSING
char	***parse_line(char *line);

//SPLIT BASH
char	**ft_split_tokens(char const *s, char c);

#endif