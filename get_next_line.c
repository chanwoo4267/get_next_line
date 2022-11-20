/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanwopa <chanwopa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 01:11:54 by chanwopa          #+#    #+#             */
/*   Updated: 2022/11/21 05:43:51 by chanwopa         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_list	*find_current_node(t_list **list_head, ssize_t fd)
{
	t_list	*ptr;
	t_list	*new_node;

	if (*list_head)
	{
		ptr = (*list_head);
		while (ptr)
		{
			if (ptr->fd == fd)
				return (ptr);
			ptr = ptr->next;
		}
	}
	new_node = malloc(sizeof(t_list));
	if (!new_node)
		return (NULL);
	new_node->fd = fd;
	new_node->next = NULL;
	new_node->str = ft_strdup("");
	if (!(new_node->str))
		return (NULL);
	if (*list_head)
		new_node->next = (*list_head);
	(*list_head) = new_node;
	return (new_node);
}

char	*find_newline(char *joined_str, char **current_str)
{
	size_t	i;
	char	*return_str;
	char	*remain_str;

	i = 0;
	free(*current_str);
	while (joined_str[i] && joined_str[i] != '\n')
		i++;
	if (!joined_str[i])
	{
		*current_str = joined_str;
		return (joined_str);
	}
	else
	{
		return_str = malloc(sizeof(char) * (i + 2));
		remain_str = ft_strlcpy(return_str, joined_str, i + 1);
		if (!remain_str)
			return (NULL);
		free(joined_str);
		*current_str = remain_str;
		return (return_str);
	}
}

void	destroy_current_node(t_list **list_head, int fd)
{
	t_list	*ptr;
	t_list	*ptr_before;

	ptr = *list_head;
	if (ptr->fd == fd)
	{
		*list_head = ptr->next;
		free(ptr->str);
		free(ptr);
	}
	else
	{
		while (ptr->fd != fd)
		{
			ptr_before = ptr;
			ptr = ptr->next;
		}
		ptr_before->next = ptr->next;
		free(ptr->str);
		free(ptr);
	}
	return ;
}

char	*get_next_line(int fd)
{
	static t_list	*list_head;
	t_list			*current;
	char			buffer[BUFFER_SIZE + 1];
	char			*joined_str;
	ssize_t			read_bytes;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	current = find_current_node(&list_head, fd);
	if (!current) // malloc fail
		return (NULL);
	while (1)
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes < BUFFER_SIZE)
		{ 
			/*  읽으려던 것보다 덜 읽었다. 1) 잘못된 fd   2) EOF까지 읽음
			  잘못된 FD -> read 함수가 -1을 반환
			  따라서 잘못된 fd면 읽기가 수행이 안되므로 NULL을 바로 반환하고
			  적게 읽었으면 남은 static 문자열 출력 후, 동적할당을 전-부 해제(문자열, 리스트노드) */
			if (read_bytes < 0)
			{
				destroy_current_node(&list_head, fd); // 여기서 str, node 다 free해주기
				return (NULL);
			}
			else if (read_bytes == 0)
			{
				buffer[read_bytes] = '\0';
				if (current->str[0] == '\0') // 읽은거 0, 저장된거 0
				{
					destroy_current_node(&list_head, fd);
					return (NULL);
				}
				else
				{
					joined_str = ft_strjoin(current->str, buffer);
					joined_str = find_newline(joined_str, &(current->str));
					if (!joined_str)
						return (NULL);
					if (joined_str == current->str) // no newline
					{
						joined_str = ft_strdup(joined_str);
						destroy_current_node(&list_head, fd);
						return (joined_str);
					}
					else
						return (joined_str);
				}
			}
			else
			{
				buffer[read_bytes] = '\0';
				joined_str = ft_strjoin(current->str, buffer);
				joined_str = find_newline(joined_str, &(current->str));
				if (!joined_str)
					return (NULL);
				if (joined_str == current->str) // no newline
				{
					joined_str = ft_strdup(joined_str);
					destroy_current_node(&list_head, fd);
					return (joined_str);
				}
				else
					return (joined_str);
			}
		}
		else /* 꽉 채워서 읽었으므로, 기존 것에 덧붙이기 */
		{
			buffer[read_bytes] = '\0';
			joined_str = ft_strjoin(current->str, buffer);
			joined_str = find_newline(joined_str, &(current->str));
			if (!joined_str)
				return (NULL);
			if (joined_str == current->str) // no newline
				continue ;
			else
				return (joined_str);
		}
	}
}
