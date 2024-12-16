/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izanoni <izanoni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 19:04:42 by izanoni           #+#    #+#             */
/*   Updated: 2024/07/24 16:50:35 by izanoni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	if (s == NULL)
		return (0);
	while (*s != '\0')
	{
		if (*s == (char) c)
		{
			return ((char *) s);
		}
		s++;
	}
	if (c == '\0')
		return ((char *) s);
	return (NULL);
}
