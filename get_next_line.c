/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanwopa <chanwopa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 15:20:49 by chanwopa          #+#    #+#             */
/*   Updated: 2022/11/16 20:51:31 by chanwopa         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#define BEFORE_NEWLINE 1
#define AFTER_NEWLINE 2

size_t	contains_newline(char *str)
{
	size_t	index;

	index = 0;
	while (*str)
	{
		if (*str == '\n')
			return (index);
		str++;
		index++;
	}
	return (-1);
}

char	*ft_cat_new_str(char *legacy, char *buffer)
{
	size_t	l_len;
	size_t	b_len;
	char	*new_str;

	l_len = ft_strlen(legacy);
	b_len = ft_strlen(buffer);
	if (l_len == -1)
	{
		new_str = malloc(sizeof(char) * (b_len + 1));
		ft_strlcpy(new_str, buffer, b_len + 1);
		return (new_str);
	}
	new_str = malloc(sizeof(char) * (l_len + b_len + 1));
	ft_strlcpy(new_str, legacy, l_len);
	ft_strlcat(new_str, buffer, (l_len + b_len + 1));
	free(legacy);
	return (new_str);
}

char	*ft_slice_str(char *legacy, size_t index, int mode)
{
	size_t	l_len;
	char	*new_str;

	l_len = ft_strlen(legacy);
	if (mode == BEFORE_NEWLINE)
	{
		new_str = malloc(sizeof(char) * (index + 2));
		ft_strlcpy(new_str, legacy, index + 2);
		return (new_str);
	}
	else
	{
		new_str = malloc(sizeof(char) * (l_len - index));
		ft_strlcpy(new_str, legacy + index + 1, l_len - index);
		free(legacy);
		return (new_str);
	}
}

char	*get_next_line(int fd)
{
	char		buffer[BUFFER_SIZE + 1];
	static char	*legacy;
	char		*return_str;
	size_t		read_len;
	size_t		index;

	if (BUFFER_SIZE <= 0)
		return (NULL);
	while (1)
	{
		read_len = read(fd, buffer, BUFFER_SIZE);
		if (read_len <= 0) // 읽은 글자가 한글자도 없다 -> EOF / 이전에 읽은 내용 그대로 반환 / 다음 input을 위해 legacy 비워주기
		{
			return_str = legacy;
			legacy = NULL;
			return (return_str);
		}
		buffer[read_len] = '\0';
		printf("input buffer : %s\n", buffer); //test
		legacy = ft_cat_new_str(legacy, buffer); // 기존 읽은거에 붙여주기 (동적할당 및 해제)
		index = contains_newline(legacy);
		printf("index : %d\n", (int)index); // test
		if (index != -1) // found newline at index
		{
			return_str = ft_slice_str(legacy, index, BEFORE_NEWLINE);
			legacy = ft_slice_str(legacy, index, AFTER_NEWLINE);
			return (return_str);
		}
	}
}

char	*get_next_line_loop(int fd)
{
	char		buffer[BUFFER_SIZE + 1];
	static char	*legacy;
	char		*return_str;
	size_t		read_len;
	size_t		index;

	if (BUFFER_SIZE <= 0)
		return (NULL);
	while (1)
	{
		read_len = read(fd, buffer, BUFFER_SIZE);
		if (read_len <= 0) // 읽은 글자가 한글자도 없다 -> EOF / 이전에 읽은 내용 그대로 반환 / 다음 input을 위해 legacy 비워주기
		{
			return_str = legacy;
			legacy = NULL;
			printf("!!%s!!", return_str);
			return (return_str);
		}
		buffer[read_len] = '\0';
		//printf("input buffer : %s\n", buffer); //test
		legacy = ft_cat_new_str(legacy, buffer); // 기존 읽은거에 붙여주기 (동적할당 및 해제)
		//printf("catted:%s\n", legacy);
		index = contains_newline(legacy);
		if (index != -1) // found newline at index
		{
			return_str = ft_slice_str(legacy, index, BEFORE_NEWLINE);
			legacy = ft_slice_str(legacy, index, AFTER_NEWLINE);
			printf("---%s---", return_str);
			printf("***%s***", legacy);
		}
	}
}
