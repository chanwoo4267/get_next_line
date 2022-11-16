/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanwopa <chanwopa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 15:20:51 by chanwopa          #+#    #+#             */
/*   Updated: 2022/11/16 19:37:50 by chanwopa         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	if (!s)
		return (-1);
	while (*s)
	{
		len++;
		s++;
	}
	return (len);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	src_len;
	size_t	copied_len;

	if ((!dst || !src) && !dstsize)
		return (0);
	src_len = ft_strlen(src);
	copied_len = 0;
	while (*src && copied_len + 1 < dstsize)
	{
		*dst = *src;
		dst++;
		src++;
		copied_len++;
	}
	if (dstsize)
		*dst = '\0';
	return (src_len);
}

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	int		dest_idx;
	int		src_idx;
	size_t	dest_len;
	size_t	src_len;

	dest_len = ft_strlen(dest);
	src_len = ft_strlen(src);
	dest_idx = dest_len;
	src_idx = 0;
	while (*(src + src_idx) && (src_idx + dest_len + 1) < size)
	{
		*(dest + dest_idx) = *(src + src_idx);
		dest_idx++;
		src_idx++;
	}
	*(dest + dest_idx) = '\0';
	if (dest_len < size)
		return (src_len + dest_len);
	else
		return (src_len + size);
}