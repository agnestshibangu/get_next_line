# include <stdlib.h>
#include <fcntl.h>
# include <unistd.h>
#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 4

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


static char *make_line(int fd, char *buffer, char *storage)
{
	int read_bytes;
	char *temp;

	read_bytes = 1;
	
	while (read_bytes)
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		buffer[read_bytes] = '\0';
		if (read_bytes == -1)
			return NULL;
		else if (read_bytes == 0)
			break ;
		if (!storage)
			storage = ft_strdup("");

		temp = storage; 
		printf("temp : %s\n", temp);
		storage = ft_strjoin(temp, buffer);
		
		free(temp);
		
		if (ft_strchr(buffer, '\n'))
			break;
	}
	return (storage);
}

//             break;
//     }
//     return line;
// }

static char	*extract(char *line)
{
	size_t	count;
	char	*backup;

	count = 0;
	while (line[count] != '\n' && line[count] != '\0')
		count++;
	if (line[count] == '\0' || line[count + 1] == '\0')
		return (0);
	backup = ft_substr(line, count + 1, ft_strlen(line) - count);
	if (*backup == '\0')
	{
		free(backup);
		backup = NULL;
	}
	line[count + 1] = '\0';
	return (backup);
}


int main() {
    int fd; 
    char buffer[BUFFER_SIZE];
    char *line;
    char *storage = NULL;

    ssize_t read_bytes;
	read_bytes = 1;
    
    fd = open("example.txt", O_RDONLY);

    while (read_bytes > 0) {
        line = make_line(fd, buffer, storage); // Utiliser le buffer local ici
        if (strchr(line, '\n') || line != NULL) {
            storage = extract(line);
            printf("storage : %s\n", storage);
            printf("line after traitement: %s\n", line);
        }
        free(line); // Assure-toi de libérer la mémoire allouée pour la ligne.
    }
    free(storage);
	close (fd);
    return 0;
}

/* 

- the first function adds the old storage to the current buffer, loops
until it finds '\n'. OK 

- the second function extract the second part of the line if it exists 
after the '\n'.

- the third function loops through the file, retreive each line;
If the storage contains a '\n', it goes into the extract function
to retreive the begin of the new line. 

*/
