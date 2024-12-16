/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izanoni <izanoni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 15:56:25 by izanoni           #+#    #+#             */
/*   Updated: 2023/05/24 17:12:37 by izanoni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *s, char c)
{
	int	count;

	count = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s != '\0')
			count++;
		while (*s && *s != c)
			s++;
	}
	return (count);
}

static char	*get_word(char const *s, char c)
{
	char	*word;
	int		len;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	word = (char *)malloc((len + 1) * sizeof(char));
	if (!word)
		return (NULL);
	word[len] = '\0';
	while (len--)
		word[len] = s[len];
	return (word);
}

char	**ft_split(char const *s, char c)
{
	char	**splited_str;
	int		nb_words;
	int		i;

	if (!s)
		return (NULL);
	nb_words = count_words(s, c);
	splited_str = (char **)malloc((nb_words + 1) * sizeof(char *));
	if (!splited_str)
		return (NULL);
	i = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s != '\0')
			splited_str[i++] = get_word(s, c);
		while (*s && *s != c)
			s++;
	}
	splited_str[i] = NULL;
	return (splited_str);
}
