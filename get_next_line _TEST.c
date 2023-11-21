/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line _TEST.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agtshiba <agtshiba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 16:34:54 by agtshiba          #+#    #+#             */
/*   Updated: 2023/11/21 19:26:43 by agtshiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strdup(const char *s)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = ft_strlen(s);
	str = (char *)malloc(sizeof(*str) * (j + 1));
	while (i < j)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	char	*str;

	str = (char *)malloc(sizeof(*s) * (len + 1));
	if (str == 0)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (i >= start && j < len)
		{
			str[j] = s[i];
			j++;
		}
		i++;
	}
	str[j] = 0;
	return (str);
}


char	*ft_strchr(const char *s, int i)
{
	while (*s)
	{
		if (*s == i)
			return ((char *)s);
		s++;
	}
	if (i == '\0')
		return ((char *)s);
	return (0);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (str == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	return (str);
}

// static char *make_line(int fd, char *buffer, char *storage)
// {
// 	int read_bytes;
// 	char *temp;

// 	read_bytes = 1;
	
// 	while (read_bytes > 0)
// 	{
// 		read_bytes = read(fd, buffer, BUFFER_SIZE);
// 		if (read_bytes == -1)
// 			return (free(storage), NULL);

// 		else if (read_bytes == 0)
// 			break ;
// 		buffer[read_bytes] = '\0';
// 		if (!storage)
// 			storage = ft_strdup("");
// 		temp = storage; 
// 		//printf("temp : %s\n", temp);
// 		storage = ft_strjoin(temp, buffer);
// 		free(temp);
// 		temp = NULL;
// 		if (ft_strchr(buffer, '\n'))
// 			break;
// 	}
// 	return (storage);
// }  


// static char *make_line(int fd, char *buffer, char *storage)
// {
// 	int read_bytes;
// 	char *temp;

// 	read_bytes = 1;

// 	while (read_bytes > 0)
// 	{
// 		read_bytes = read(fd, buffer, BUFFER_SIZE);
// 		if (read_bytes == -1)
// 			return (free(storage), NULL);

// 		buffer[read_bytes] = '\0';
// 		if (!storage)
// 			storage = ft_strdup("");
// 		temp = storage; 
// 		//printf("temp : %s\n", temp);
// 		storage = ft_strjoin(temp, buffer);
// 		free(temp);
// 		temp = NULL;
// 		if (ft_strchr(buffer, '\n'))
// 			break;
// 	}

// 	if (read_bytes < 0)
//         return NULL;

// 	return (storage);
// }



static char *make_line(int fd, char *buffer, char *storage)
{
    int read_bytes;
    char *temp;

  
	read_bytes = 1;
    while (read_bytes > 0)
    {
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes == -1)
			return (0);
		else if (read_bytes == 0)
			break ;
        buffer[read_bytes] = '\0';
		if (!storage)
			storage = ft_strdup("");
        temp = storage;
        storage = ft_strjoin(temp, buffer);
		free(temp);
		temp = NULL;
        if (ft_strchr(buffer, '\n'))
            break;
    }

    if (read_bytes < 0)
        return NULL;

    return (storage);
}






// ZERO LEAKS WITH THIS ONE this is my logic//
static char	*my_extract(char *line)
{
	size_t	len;
	size_t	start;
	char	*backup;
	char	*newline_pos;
	
	len = 0;
	newline_pos = ft_strchr(line, '\n');
	if (newline_pos == NULL || *newline_pos == '\0')
		return NULL;
	while (line[len] != '\0' && line + len != newline_pos)
		len++;
	if (line[len] == '\0')	
		return (0);
	start = len + 1;
	size_t substring_len = ft_strlen(line) - len;
	backup = ft_substr(line, start, substring_len);
	if (*backup == '\0')
	{
		free(backup);
		backup = NULL;
	}
    line[len + 1] = '\0';
    return (backup);
}

char	*get_next_line(int fd)
{
	//char buffer[BUFFER_SIZE]; //avec ca, pas besoin de mallocer
	char *buffer;
    char *line;
	static char *storage;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return 0;
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (0);
		// return NULL;
	line = make_line(fd, buffer, storage);
	free(buffer);
	if (!line)
	{
		if (storage)
		{
			free(storage);
			storage = NULL;
		}
		return (NULL);
	}
	if (ft_strchr(line, '\n') || line != NULL)
		storage = my_extract(line);
	return (line);
}

int main() 
{
    int fd;
    char *line;

    fd = open("example.txt", O_RDONLY);

    if (fd == -1) {
        perror("Erreur lors de l'ouverture du fichier");
        return 1;
    }

    while ((line = get_next_line(fd)) != NULL) {
        printf("Ligne lue : %s", line);
        free(line);
    }
    close(fd);
    return 0;
}
