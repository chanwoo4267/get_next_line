/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanwopa <chanwopa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 01:11:56 by chanwopa          #+#    #+#             */
/*   Updated: 2022/11/21 07:17:21 by chanwopa         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

# include <unistd.h>
# include <stdlib.h>

typedef struct s_list
{
	char			*str;
	int				fd;
	struct s_list	*next;
}	t_list;

typedef struct s_obje
{
	t_list	*current;
	char	buffer[BUFFER_SIZE + 1];
	char	*joined_str;
	ssize_t	read_bytes;
	int		flags;
}	t_varcollection;

char	*get_next_line(int fd);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strlcpy(char *dst, const char *src, size_t count);
char	*find_newline(char *joined_str, char **current_str);
void	destroy_current_node(t_list **list_head, int fd);

#endif