/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfelipa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 14:42:45 by pfelipa           #+#    #+#             */
/*   Updated: 2020/09/02 18:56:32 by pfelipa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <unistd.h>
# include <stdlib.h>
# include "libftprintf.h"
# include "get_next_line.h"

typedef struct		s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;
typedef struct		s_pair
{
	char			*key;
	char			*value;
}					t_pair;
typedef struct		s_ht
{
	t_list			**items;
	int				count;
	int				size;
}					t_ht;
int					ft_strlen(const char *str);
size_t				ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t				ft_strlcat(char *dst, const char *src, size_t dstsize);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
char				*ft_strnstr(const char *haystack,\
					const char *needle, size_t len);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_atoi(const char *s);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_toupper(int c);
int					ft_tolower(int c);
void				*ft_memset(void *s, int c, size_t len);
void				ft_bzero(void *s, size_t len);
void				*ft_calloc(size_t count, size_t bsize);
void				*ft_memcpy(void *dst, const void *src, size_t len);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memccpy(void *dst, const void *src, int c, size_t len);
void				*ft_memchr(const void *s, int c, size_t n);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s, char const *set);
char				**ft_split(char const *s, char c);
char				*ft_itoa(int n);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);
char				*ft_strdup(const char *s);
t_list				*ft_lstnew(void *content);
void				ft_lstadd_front(t_list **lst, t_list *new);
int					ft_lstsize(t_list *lst);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstiter(t_list *lst, void (*f)(void *));
int					ft_lstsearch(t_list *lst, void *content,\
					int (*f)(void *, void *));
t_list				*ft_lstget(t_list *lst, int index);
void				ft_lstremove(t_list **lst, int index);
int					ft_atoi_base(char *s, char *base);
char				*ft_itoa_base(int n, char *base);
double 				ft_atof(const char *str);
t_list				*ft_lstmap(t_list *lst, void *(*f)(void*),\
					void (*del)(void *));
int					ft_abs(int a);
int					ft_max(int a, int b);
int					ft_min(int a, int b);
long				hash_s(char *s, int m);
t_pair				*ht_newpair(char *key, char *value);
int					ht_paircmpr(t_pair *a, char *key);
t_ht				*ht_create(int size);
void				ht_freeitem(t_pair *item);
void				ht_freetable(t_ht *table);
void				ht_insert(t_ht *table, char *key, char *value);
void				ht_remove(t_ht	*table, char *key);
void				ht_print(t_ht *hashtable);
void				ht_process_collision(t_ht *table, long index, t_pair *pair);

#endif
