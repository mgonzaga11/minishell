/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izanoni <izanoni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 17:38:08 by izanoni           #+#    #+#             */
/*   Updated: 2023/05/28 15:34:32 by izanoni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*c_alloc;
	size_t	alloc_size;

	alloc_size = nmemb * size;
	if (alloc_size != 0 && alloc_size / size != nmemb)
		return (NULL);
	c_alloc = malloc(alloc_size);
	if (!c_alloc)
		return (NULL);
	ft_bzero (c_alloc, alloc_size);
	return (c_alloc);
}
