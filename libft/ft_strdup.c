/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izanoni <izanoni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:33:34 by izanoni           #+#    #+#             */
/*   Updated: 2023/05/25 15:41:17 by izanoni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*copy;
	size_t	i;
	size_t	size;

	if (s == NULL)
		return (0);
	size = ft_strlen(s);
	copy = (char *)malloc((size + 1) * sizeof(char));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < size)
	{
		copy[i] = s[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}
