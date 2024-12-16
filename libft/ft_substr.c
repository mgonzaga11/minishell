/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izanoni <izanoni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 14:56:18 by izanoni           #+#    #+#             */
/*   Updated: 2023/05/29 17:56:05 by izanoni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*substring;
	unsigned int	i;
	size_t			slen;
	size_t			sublen;

	slen = ft_strlen(s);
	if (!s || start >= slen)
	{
		return (ft_strdup(""));
	}
	if (start + len <= slen)
		sublen = len;
	else
		sublen = slen - start;
	substring = (char *)malloc((sublen + 1) * sizeof(char));
	if (!substring)
		return (NULL);
	i = 0;
	while (s[start + i] != '\0' && i < sublen)
	{
		substring[i] = s[start + i];
		i++;
	}
	substring[i] = '\0';
	return (substring);
}
