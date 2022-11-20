/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanwopa <chanwopa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 01:11:45 by chanwopa          #+#    #+#             */
/*   Updated: 2022/11/21 05:00:25 by chanwopa         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strdup(const char *s1)
{
	size_t	i;
	char	*p;

	i = 0;
	while (s1[i])
		i++;
	p = malloc(sizeof(char) * (i + 1));
	if (!p)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		p[i] = s1[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	size_t	i;
	char	*str;

	i = 0;
	while (s1[i])
		i++;
	s1_len = i;
	i = 0;
	while (s2[i])
		i++;
	s2_len = i;
	str = malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (!str)
		return (NULL);
	i = -1;
	while (s1[++i])
		str[i] = s1[i];
	i--;
	while (s2[++i - s1_len])
		str[i] = s2[i - s1_len];
	str[i] = '\0';
	return (str);
}

char	*ft_strlcpy(char *dst, const char *src, size_t count)
{
	char	*remain_str;
	size_t	i;
	size_t	l_count;

	l_count = count;
	i = 0;
	while (src[i])
		i++;
	l_count = i - count;
	remain_str = malloc(sizeof(char) * (l_count + 1));
	if (!remain_str)
		return (NULL);
	i = -1;
	while (++i < count)
		dst[i] = src[i];
	dst[i] = '\0';
	i = -1;
	while (++i < l_count)
		remain_str[i] = src[count + i];
	remain_str[i] = '\0';
	return (remain_str);
}	
