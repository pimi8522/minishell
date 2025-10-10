/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miduarte <miduarte@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 10:55:27 by miduarte          #+#    #+#             */
/*   Updated: 2025/04/11 14:48:45 by 
miduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
#include "get_next_line/get_next_line.h"

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

int			ft_isalpha(int ch);
int			ft_isdigit(int arg);
int			ft_isalnum(int arg);
int			ft_isprint(int c);
int			ft_strlen(const char *str);
int			ft_toupper(int ch);
int			ft_tolower(int ch);
int			ft_atoi(const char *str);
char		*ft_strdup(const char *src);
size_t		ft_strlcat(char *dest, const char *src, size_t dstsize);
void		*ft_memset(void *ptr, int value, size_t num);
void		*ft_memcpy(void *dest, const void *source, size_t num);
void		ft_bzero(void *s, size_t n);
void		*ft_calloc(size_t count, size_t size);
void		*ft_memmove(void *dest, const void *src, size_t len);
int			ft_strncmp(const char *str1, const char *str2, size_t num);
int 		ft_strcmp(const char *s1, const char *s2);
char		*ft_strnstr(const char *big, const char *little, size_t len);
char		*ft_strchr(const char *str, int character );
char		*ft_strrchr(const char *str, int character );
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);
void		*ft_memchr(const void *s, int c, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strjoin(char const *s1, char const *s2);
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int nb, int fd);
char		*ft_itoa(int n);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void		ft_striteri(char *s, void (*f)(unsigned int, char*));
char		**ft_split(char const *s, char c);
void		ft_lstadd_front(t_list **lst, t_list *new);
t_list		*ft_lstnew(void *content);
int			ft_lstsize(t_list *lst);
t_list		*ft_lstlast(t_list *lst);
void		ft_lstadd_back(t_list **lst, t_list *new);
void		ft_lstdelone(t_list *lst, void (*del)(void*));
void		ft_lstclear(t_list **lst, void (*del)(void*));
void		ft_lstiter(t_list *lst, void (*f)(void *));
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
int			ft_isascii(int c);
char		*ft_strtrim(char const *s1, char const *set);

char	*get_next_line(int fd);

#endif