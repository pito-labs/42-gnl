/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thirokaw <thirokaw@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 01:15:43 by thirokaw          #+#    #+#             */
/*   Updated: 2025/11/26 19:37:49 by thirokaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static	char	*join_and_free(int fd, char	*buffer,
					char *backup, ssize_t byte_size)
{
	char	*tmp;

	while ((!backup || !ft_strchr(backup, '\n')) && byte_size > 0)
	{
		byte_size = read(fd, buffer, BUFFER_SIZE);
		if (byte_size == -1)
		{
			free (backup);
			return (NULL);
		}
		if (byte_size == 0)
			break ;
		buffer[byte_size] = '\0';
		tmp = ft_strjoin(backup, buffer);
		if (!tmp)
		{
			free(backup);
			return (NULL);
		}
		free (backup);
		backup = tmp;
	}
	return (backup);
}

char	*read_to_newline(int fd, char *backup)
{
	char	*buffer;
	char	*res;
	ssize_t	byte_size;

	buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	byte_size = 1;
	res = join_and_free(fd, buffer, backup, byte_size);
	if (res == NULL)
	{
		free (buffer);
		return (NULL);
	}
	free (buffer);
	return (res);
}

static	char	*extract_line(char *backup)
{
	size_t	i;
	char	*line;

	i = 0;
	if (!backup || backup[0] == '\0')
		return (NULL);
	while (backup[i] != '\0' && backup[i] != '\n')
		i++;
	line = (char *)malloc(i + 2);
	if (!line)
		return (NULL);
	i = 0;
	while (backup[i] != '\0' && backup[i] != '\n')
	{
		line[i] = backup[i];
		i++;
	}
	if (backup[i] == '\n')
	{
		line[i] = '\n';
		i++;
	}
	line [i] = '\0';
	return (line);
}

static	char	*extract_remainder(char *backup)
{
	size_t	i;
	size_t	k;
	size_t	total;
	char	*remain;

	i = 0;
	k = 0;
	total = ft_strlen(backup);
	while (backup[i] != '\0' && backup[i] != '\n')
		i++;
	if (backup[i] == '\0')
	{
		free(backup);
		return (NULL);
	}
	remain = (char *)malloc(total - i + 1);
	if (!remain)
		return (NULL);
	i++;
	while (backup[i] != '\0')
		remain[k++] = backup[i++];
	remain[k] = '\0';
	free(backup);
	return (remain);
}

char	*get_next_line(int fd)
{
	static char	*backup[OPEN_MAX];
	char		*line;

	if (fd < 0 || fd >= OPEN_MAX || BUFFER_SIZE <= 0)
	{
		if (fd >= 0 && fd < OPEN_MAX && backup[fd])
		{
			free(backup[fd]);
			backup[fd] = NULL;
		}
		return (NULL);
	}
	backup[fd] = read_to_newline(fd, backup[fd]);
	if (!backup[fd])
		return (NULL);
	line = extract_line(backup[fd]);
	if (!line)
	{
		free (backup[fd]);
		backup[fd] = NULL;
		return (NULL);
	}
	backup[fd] = extract_remainder(backup[fd]);
	return (line);
}
