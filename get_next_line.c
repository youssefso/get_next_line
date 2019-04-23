/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymoukhli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 13:59:04 by ymoukhli          #+#    #+#             */
/*   Updated: 2019/04/23 15:57:42 by ymoukhli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

int	getchrine(int fd, char *t[256], char **line)
{
	int i;
	char *tmp;

	i = 0;
	while (t[fd][i] != '\n' && t[fd][i] != '\0')
		i++;
	if (t[fd] != NULL)
	{
		if (t[fd][i] == '\0')
		{
			*line = ft_strdup(t[fd]);
			free(t[fd]);
			t[fd] = NULL;
			return (1);
		}
		t[fd][i++] = '\0';
		tmp = t[fd];
		*line = ft_strdup(t[fd]);
		t[fd] = ft_strdup(&t[fd][i]);
		free(tmp);
		return (1);
	}
	return (0);
}

int	get_next_line(const int fd, char **line)
{
	int			ret;
	char		buf[BUFF_SIZE + 1];
	static char	*t[256];
	char		*tmp;

	if (fd < 0 || !line || BUFF_SIZE < 0 || read(fd, buf, 0) < 0)
		return (-1);
	if (t[fd] == NULL)
		t[fd] = ft_strnew(0);
	while ((ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[ret] = '\0';
		tmp = t[fd];
		t[fd] = ft_strjoin(t[fd], buf);
		free(tmp);
		if (ft_strchr(buf, '\n'))
			break ;
	}
	return (getchrine(fd, t, line));
}

int main()
{
	int fd;
	char *s;

	while (1)
	{
		fd = open("file.txt", O_RDONLY);
		while (get_next_line(fd, &s))
		{
			printf(" %s\n", s);
			free(s);
		}
		close(fd);
	}
}
