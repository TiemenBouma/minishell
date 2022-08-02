/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 14:09:35 by dkocob            #+#    #+#             */
/*   Updated: 2022/08/02 12:02:50 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_echo(char *s)
{
	int	i = 0;
	// int	size_of_arg;
	// char *result;
	// s = "Yo";

	// write(1, "YO!\n", 4);
	// size_of_arg = 0;
	// size_of_arg += 7;
	while (s[i])
		i++;
	write (1, s, i);
	write(1, "\n", 1); //TIEMEN WROTE THIS NEW LINE, NOT SURE IF IT IS THE RIGHT PLACE
}

// t_node *find_node_in_list(t_node *list, char *var_line)
// {
// 	t_node *current;

// 	current = list;
// 	while (1)
// 	{
// 		if (ft_strncmp(current->str, var_line, ft_strlen(var_line) + 1))
// 			return (current);
// 		if (current->n == NULL)
// 			break ;
// 		current = current->n;
// 	}
// 	return (NULL);
// }

// void	ft_pwd(struct	s_cmd_lines	*d)
// {
// 	//print current pwd
// }

// void	ft_cd(struct	s_cmd_lines	*d)
// {
// 	//check pwd
// 	//check if dest location is exist (access?)
// 	//modify pwd
// }

// void	ft_unset(t_node *first_node, char *var_line)
// {
// 	t_node	*match_node;
// 	t_node	*prev;
// 	t_node	*next;

// 	match_node = find_node_in_list(first_node, var_line);
// 	if (match_node == NULL)
// 		return ;
// 	if (match_node->p == NULL && first_node->n)
// 	{
// 		first_node = first_node->n;
// 		first_node->p = NULL;

// 	}
// 	if (match_node->p)
// 		prev = match_node->p;
// 	if (match_node->n)
// 		next = match_node->n;

// 	if (prev && next)
// 	{
// 		next->p = prev;
// 		prev->n = next;
// 	}
// 	free(match_node->str);
// 	free(match_node);
// }

void ft_cd(t_node **list)
{
	int i = 0;
	int	*cwd;
	
	cwd = malloc(sizeof(char) * (MAXPATHLEN));
	cwd[PATH_MAX] = '\0';
	getcwd(cwd, MAXPATHLEN);// check if it worked
	//OLDPWD= becomes cwd.
	
	chdir(/*new path*/ );//check if it worked
	//PWD= becomes new path.

	getcwd(cwd, MAXPATHLEN);//checked if switch worked
}

void	ft_env(t_node **list)
{

	t_node *current;

	current = *list;
	while (1)
	{
		write(1, &current->str, ft_strlen(current->str));
		if (current->n == NULL)
			break ;
		current = current->n;
	}
}

int	replace_node_content(t_node *first_node, char *var_line)
{
	free(first_node->str);
	first_node->str = var_line; //check after implementation
	return (0);
}

void	ft_export(t_node **list, /*struct	s_cmd_lines	*d,*/ char *var_line)
{
	t_node	*new_node;
	t_node	*match_node;

	match_node = find_node_in_list(list, var_line);
	if (!match_node)
	{
		new_node = ft_new_node(var_line);
		ft_list_node_add_back(list, new_node);	
	}
	else
	{
		replace_node_content(match_node, var_line);
	}
}

int	is_builtin(char	*s)
{
	// write(1, "Y1!\n", 4);
	if (!s)
		return (-1);
	if (ft_strncmp(s, "/bin/echo", 9 + 1) == 0)
		return (1);
	else if (ft_strncmp(s, "/usr/bin/cd", 11 + 1) == 0) //change abs path? exec all fucns with abs path?
		return (2);
	else if (ft_strncmp(s, "/bin/pwd", 8 + 1) == 0) //exec all fucns with abs path?
		return (3);
	else if (ft_strncmp(s, "export", 6 + 1) == 0)
		return (4);
	else if (ft_strncmp(s, "unset", 5 + 1) == 0)
		return (5);
	else if (ft_strncmp(s, "env", 3 + 1) == 0)
		return (6);
	else if (ft_strncmp(s, "exit", 4 + 1) == 0)
		exit (0);
	return (0);
}

int	exec_builtin(struct	s_cmd_lines	*d, char **s, int n)
{
	//char *cmd = s[0];

	// s[0] = "Yo";
	//printf ("test%s\n", cmd);
	(void) s;
	if (n == 1)
		ft_echo(d->cmd_info->pipe_cmd.exec_line[1]);
	// else if (n == 2) //change abs path? exec all fucns with abs path?
	// 	ft_cd(d);
	// else if (n == 2) //exec all fucns with abs path?
	// 	ft_pwd(d);
	// else if (n == 3)
	// 	ft_export(d, cmd);
	// else if (n == 4)
	// 	ft_unset(d, cmd);
	// else if (n == 5)
	// 	ft_env(d);
	exit (0);
}
