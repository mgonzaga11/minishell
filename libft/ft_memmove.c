/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izanoni <izanoni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 19:06:12 by izanoni           #+#    #+#             */
/*   Updated: 2023/05/29 18:53:17 by izanoni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char		*cdest;
	const char	*csrc;

	cdest = dest;
	csrc = src;
	if (cdest == NULL && csrc == NULL)
		return (NULL);
	if (csrc < cdest)
	{
		cdest += n;
		csrc += n;
		while (n--)
		{
			*--cdest = *--csrc;
		}
	}
	else
	{
		while (n--)
		{
			*cdest++ = *csrc++;
		}
	}
	return (dest);
}
