/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfelipa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 14:42:45 by pfelipa           #+#    #+#             */
/*   Updated: 2020/09/02 18:56:32 by pfelipa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"
#include <stdio.h>

static char	*ft_strjoin_gnl(char const *s1, char const *s2)
{
	char	*res;
	int		l1;
	int		l2;

	if (!s1 || !s2)
		return (NULL);
	l1 = ft_strlen(s1);
	l2 = ft_strlen(s2);
	res = malloc((l1 + l2 + 1) * sizeof(char));
	if (res)
	{
		res[0] = '\0';
		ft_strlcat(res, s1, (l1 + l2 + 1) * sizeof(char));
		ft_strlcat(res, s2, (l1 + l2 + 1) * sizeof(char));
	}
	free((void *)s1);
	return (res);
}

int		liberate_s(char **s, int out)
{
	free(*s);
	*s = NULL;
	return (out);
}

int		process_output(int fd, int n_read, char **s, char **line)
{
	char *ptrns;
	char *ptrnl;

	if (fd < 0 || n_read < 0 || BUFFER_SIZE < 1 || !line)
		return (-1);
	if ((ptrnl = ft_strchr(*s, '\n')))
	{
		*ptrnl = '\0';
		if (!(*line = ft_strdup(*s)))
			return (liberate_s(s, -1));
		ptrns = *s + ft_strlen(*s) + 1;
		ft_strlcpy(*s, ptrns, ft_strlen(ptrns) + 1);
		return (1);
	}
	else
	{
		if (!(*line = ft_strdup(*s)))
			return (liberate_s(s, -1));
		return (liberate_s(s, 0));
	}
}

int		get_next_line(int fd, char **line)
{
	static char	*s[2048];
	char		buff[(BUFFER_SIZE > 0) ? BUFFER_SIZE + 1 : 1];
	int			n_read;

	n_read = 0;
	while ((fd >= 0 && BUFFER_SIZE > 0 && line)
	&& (!s[fd] || !ft_strchr(s[fd], '\n'))
	&& (n_read = read(fd, buff, BUFFER_SIZE)) > 0)
	{
		buff[n_read] = '\0';
		if (!s[fd])
		{
			if (!(s[fd] = ft_strdup(buff)))
				return (-1);
			continue ;
		}
		if (!(s[fd] = ft_strjoin_gnl(s[fd], buff)))
			return (-1);
	}
	if (!s[fd])
		if (!(s[fd] = ft_strdup("\0")))
			return (-1);
	return (process_output(fd, n_read, &s[fd], line));
}
