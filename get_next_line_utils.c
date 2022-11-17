/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanwopa <chanwopa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 15:20:51 by chanwopa          #+#    #+#             */
/*   Updated: 2022/11/18 00:49:25 by chanwopa         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (*s != '\0')
	{
		len++;
		s++;
	}
	return (len);
}

char	*ft_strdup(const char *s1)
{
	char	*p;
	char	*ret;
	size_t	len;

	len = ft_strlen(s1);
	p = malloc(sizeof(char) * (len + 1));
	if (!p)
		return (NULL);
	ret = p;
	while (len--)
	{
		*p = *s1;
		p++;
		s1++;
	}
	*p = '\0';
	return (ret);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr;
	char	*ret;

	if (start + len > ft_strlen(s))
		len = ft_strlen(s) - start;
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	ptr = malloc(sizeof(char) * (len + 1));
	if (!ptr)
		return (NULL);
	ret = ptr;
	s += start;
	while (len-- > 0)
	{
		*ptr = *s;
		ptr++;
		s++;
	}
	*ptr = '\0';
	return (ret);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*ptr;
	char	*ret_ptr;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	ptr = malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (!ptr)
		return (NULL);
	ret_ptr = ptr;
	while (*s1)
	{
		*ptr = *s1;
		ptr++;
		s1++;
	}
	while (*s2)
	{
		*ptr = *s2;
		ptr++;
		s2++;
	}
	*ptr = '\0';
	return (ret_ptr);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s != '\0')
	{
		if (*s == (unsigned char)c)
			return ((char *)s);
		s++;
	}
	if ((unsigned char)c == 0)
		return ((char *)s);
	else
		return (NULL);
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
