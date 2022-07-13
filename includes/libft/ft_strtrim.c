/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 11:29:00 by tbouma            #+#    #+#             */
/*   Updated: 2021/12/15 11:29:51 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	make_string(char *str, char const *s1, int index_s1, int len_s1)
{
	int	l;

	l = 0;
	while (index_s1 < len_s1)
	{
		str[l] = s1[index_s1];
		l++;
		index_s1++;
	}
	str[l] = '\0';
}

int	check_set(char const *s1, char const *set, int count)
{
	int	i;

	i = 0;
	while ((unsigned char)set[i])
	{
		if ((unsigned char)s1[count] == (unsigned char)set[i])
			return (1);
		i++;
	}
	return (0);
}

int	check_begin(char const *s1, char const *set)
{
	int	index_s1;

	index_s1 = 0;
	while ((unsigned char)s1[index_s1])
	{
		if (check_set(s1, set, index_s1))
			index_s1++;
		else
			break ;
	}
	return (index_s1);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		index_s1;
	int		len_s1;
	char	*str;

	if (s1 == NULL || set == NULL)
		return (NULL);
	len_s1 = ft_strlen(s1);
	index_s1 = check_begin(s1, set);
	while (len_s1 > index_s1)
	{
		if (check_set(s1, set, len_s1 - 1))
			len_s1--;
		else
			break ;
	}
	str = (char *) malloc(((len_s1 - index_s1) + 1) * sizeof(char));
	if (str == NULL)
		return (0);
	make_string(str, s1, index_s1, len_s1);
	return (str);
}

// int main(void)
// {
// 	char * s = ft_strtrim("   xxxtripouille", " x");
// 	printf("%s\n", s);
// }