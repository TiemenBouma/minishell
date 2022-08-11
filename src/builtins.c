/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 14:09:35 by dkocob            #+#    #+#             */
/*   Updated: 2022/08/11 09:49:14 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_echo(char **s)
{
	int	i = 0;
	// int	size_of_arg;
	// char *result;
	// s = "Yo";

	// write(1, "YO!\n", 4);
	// size_of_arg = 0;
	// size_of_arg += 7;
	while (s[i])
	{
		ft_putstr_fd(s[i], 2);
		write(1, " ", 2);
	//	printf("%s ", s[i]);
		i++;
	}
	printf("\n");
	// 	i++;
	// write (1, s, i);
	// write(1, "\n", 1); //TIEMEN WROTE THIS NEW LINE, NOT SURE IF IT IS THE RIGHT PLACE
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

void	ft_pwd(void)
{
	char	*cwd;
	
	cwd = malloc(sizeof(char) * (MAXPATHLEN + 1));
	cwd[PATH_MAX] = '\0';
	getcwd(cwd, MAXPATHLEN);// check if it worked
	ft_putstr_fd(cwd, 1);
	write(1, "\n", 1);
	free(cwd);
}

// void	ft_cd(struct	s_main	*main_struct)
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

void ft_cd(t_node **list, char **exec_line)// WORKS WITH ABSOLUTE PATH, not relative. NEED TO BUILD IN CHECKS IF  getcwd AND chdir WORKED.
{
	//int i = 0;
	char	*cwd;
	t_node	*temp_node;
	char	*temp_str;
	
	cwd = malloc(sizeof(char) * (MAXPATHLEN + 1));
	cwd[PATH_MAX] = '\0';
	getcwd(cwd, MAXPATHLEN);// check if it worked
	temp_str = ft_strjoin("OLDPWD=", cwd);
	free(cwd);
	//printf("old: %s\n", temp_str);
	ft_find_and_remove_node(list, "OLDPWD");
	temp_node = ft_new_node(temp_str);
	free(temp_str);
	ft_list_node_add_back(list, temp_node);
	
	
	chdir(exec_line[1]);//check if it worked, ernno is made on error.
	//PWD= becomes new path.
	temp_str = ft_strjoin("PWD=", exec_line[1]);
	//printf("new: %s\n", temp_str);
	ft_find_and_remove_node(list, "PWD");
	temp_node = ft_new_node(temp_str);
	ft_list_node_add_back(list, temp_node);
	cwd = malloc(sizeof(char) * (MAXPATHLEN + 1));
	cwd[PATH_MAX] = '\0';
	getcwd(cwd, MAXPATHLEN);//checked if switch worked
	//printf("cwd in cd = %s\n", cwd);
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


void	ft_export(t_node **list, /*struct	s_main	*main_struct,*/ char *var_line)
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
		return (7);
	return (0);
}

int	exec_builtin(struct	s_main	*main_struct, char **exec_line, int n)
{
	//char *cmd = s[0];

	// s[0] = "Yo";
	//printf ("test%s\n", cmd);
	//(void) exec_line;
	if (n == 1)
		ft_echo(main_struct->cmd_struct_arr->exec.exec_line + 1);
	else if (n == 2) //change abs path? exec all fucns with abs path?
		ft_cd(&main_struct->env_llist, exec_line);
	else if (n == 3) //exec all fucns with abs path?
		ft_pwd();
	// else if (n == 3)
	// 	ft_export(main_struct, cmd);
	// else if (n == 4)
	// 	ft_unset(main_struct, cmd);
	// else if (n == 5)
	// 	ft_env(main_struct);
	//exit (0);
	return (0);
}


int	check_buildin_stdinout(struct s_cmd_info *cmd_struct)// NEED TO CHECK FOR SYSTEMFUNC probably
{
	int checker;
	
	checker = is_builtin(cmd_struct->exec.exec_line[0]);
	if (checker == 2 || checker == 4 || checker == 5 || checker == 7)
		return (0);
	else
		return (1);
}