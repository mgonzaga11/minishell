/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izanoni <izanoni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 15:51:51 by izanoni           #+#    #+#             */
/*   Updated: 2023/05/26 19:19:36 by izanoni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_char_in_set(char c, char const *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	size_t	i;
	char	*trimmed_str;

	start = 0;
	if (!s1)
		return (NULL);
	while (s1[start] && is_char_in_set(s1[start], set))
		start++;
	end = ft_strlen(s1);
	while (end > start && is_char_in_set(s1[end - 1], set))
		end--;
	trimmed_str = (char *)malloc((end - start + 1) * sizeof(char));
	if (trimmed_str == (NULL))
		return (NULL);
	i = 0;
	while (i < end - start)
	{
		trimmed_str[i] = s1[start + i];
		i++;
	}
	trimmed_str[i] = '\0';
	return (trimmed_str);
}
