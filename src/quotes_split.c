/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 15:02:16 by tbouma            #+#    #+#             */
/*   Updated: 2022/07/17 13:57:37 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	free_string(char **str_arr, int i)
{
	while (i >= 0)
	{
		free(str_arr[i]);
		i--;
	}
	free(str_arr);
}

static int	calc_len_next_str(char const *s, char c, int mem_i)
{
	int	i;

	i = 0;
	while (s[mem_i] != c && s[mem_i] != '\0')
	{
		i++;
		mem_i++;
	}
	printf("calc len = %d \n", i);
	return (i);
}

static int	is_quote(char c)
{
	if (c == 34 || c == 39)
		return (1);
	return (0);
}

static void	make_sub_str(const char *s, char **str_arr, int i, int *current_str, char c)
{
	str_arr[*current_str] = ft_substr(s, i, (calc_len_next_str(s, c, i)));
	if (str_arr[*current_str] == NULL)
	{
		free_string(str_arr, *current_str);
		//SET ERROR
	}
	(*current_str)++;
}


static int	str_maker(char const *s, char c, char	**str_arr)
{
	int		i;
	int	current_str;

	current_str = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && is_quote(s[i]))
		{
			printf("str_maker test\n");
			printf("I = %d, s[i] = %c\n", i, s[i]);
			make_sub_str(s, str_arr, i + 1, &current_str, s[i]);
			i++;//save string withougt "" ''
			while (s[i] && is_quote(s[i]) == 0)
				i++;
			if (is_quote(s[i]))
				i++;
		}
		if (s[i] && s[i] != c && is_quote(s[i]) == 0)
		{
			make_sub_str(s, str_arr, i, &current_str, c);
			while (s[i] && s[i] != c && is_quote(s[i]) == 0)
				i++;
		}
	}
	return (0);
}

static int	str_counter(char const *s, char c)
{
	int		str_count;
	int		i;
	bool	first_string;

	first_string = false;
	i = 0;
	str_count = 1;
	while (s[i])
	{
		
		if (s[i] && s[i] == c)
		{
			if (first_string == true)
				str_count++;
			while (s[i] && s[i] == c)
				i++;
		}
		if (s[i] && is_quote(s[i]))
		{
			i++;
			first_string = true;
			while (s[i] && is_quote(s[i]) == 0)
				i++;
			if (is_quote(s[i]))
				i++;
		}
		while (s[i] && s[i] != c && is_quote(s[i]) == 0)
		{
			first_string = true;
			i++;
		}
	}
	return (str_count);
}

char	**ft_split_tokens(char const *s, char c)
{
	char	**str_arr;
	int		str_count;

	if (!s)
		return (NULL);
	str_count = str_counter(s, c);
	str_arr = (char **) malloc((str_count + 1) * sizeof(char *));
	if (str_arr == NULL)
		return (NULL);
	if (!(*s))
	{
		str_arr[0] = NULL;
		return (str_arr);
	}
	str_maker(s, c, str_arr);
	str_arr[str_count] = NULL;
	return (str_arr);
}

// int main(void)
// {
// 	char **str;
// 	int i = 0;

// 	str = ft_split("test | \" sfdsf\" fefr | testing", '|');
// 	while (str[i])
// 	{
// 		printf("%s\n", str[i]);
// 		i++;
// 	}
// }