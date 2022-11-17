/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanwopa <chanwopa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 15:20:49 by chanwopa          #+#    #+#             */
/*   Updated: 2022/11/18 00:47:14 by chanwopa         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*trim(char **strs)
{
	int		i;
	char	*trim;
	char	*temp;

	i = 0;
	while ((*strs)[i] && (*strs)[i] != '\n')
		i++;
	if (!(*strs)[i]) // this str has no newline
	{
		trim = ft_strdup(*strs);
		free(*strs);
		*strs = 0;
	}
	else
	{
		trim = ft_substr(*strs, 0, i + 1);
		temp = ft_strdup(&(*strs)[i + 1]);
		free(*strs);
		*strs = 0;
		if (*temp)
			*strs = ft_strdup(temp);
		free(temp);
	}
	return (trim);
}

char	*get_next_line(int fd)
{
	static char	*str_left[FD_SIZE];
	char		buff[BUFFER_SIZE + 1];
	char		*temp;
	ssize_t		n_bytes_rd;

	n_bytes_rd = 0;
	if (fd < 0 || fd > 1024 || BUFFER_SIZE < 1)
		return (NULL);
	n_bytes_rd = read(fd, buff, BUFFER_SIZE);
	while (n_bytes_rd > 0)
	{
		buff[n_bytes_rd] = '\0';
		if (!str_left[fd])
			str_left[fd] = ft_strdup("");
		temp = ft_strdup(str_left[fd]);
		free(str_left[fd]);
		str_left[fd] = ft_strjoin(temp, buff);
		free(temp);
		if (ft_strchr(str_left[fd], '\n'))
			break ;
		n_bytes_rd = read(fd, buff, BUFFER_SIZE);
	}
	if (n_bytes_rd < 0 || (n_bytes_rd == 0 && !str_left[fd]))
		return (NULL);
	return (trim(&str_left[fd]));
}
