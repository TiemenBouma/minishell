/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tiemen <tiemen@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/13 15:52:01 by tiemen        #+#    #+#                 */
/*   Updated: 2022/07/14 09:48:28 by tiemen        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"



char	**find_path(char **envp)
{
	char	*ptr;
	char	**root_paths;
	int		i;

	i = 0;
	while (envp[i])
	{
		ptr = ft_strnstr(envp[i], "PATH=", strlen(envp[i]));
		if (ptr != NULL)
			break ;
		i++;
	}
	if (ptr == NULL)
		error_msg(ERR_PATH, 1);
	ptr += 5;
	root_paths = ft_split(ptr, ':');
	if (root_paths == NULL)
		error_msg(ERR_MALLOC, 1);
	return (root_paths);
}

int free_stuff(char *str)
{
	free(str);
	return (0);
}

int	main(void)
{
	//int	i;
	char	*str;
	
	str = readline("SuperShell: ");
	// printf("\n");
	
	printf("readline:%s\n", str);
	free_stuff(str);
	
}

// gcc main.c -lreadline
