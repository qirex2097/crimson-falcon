#include "minishell.h"
#include <string.h>


/*TODO: 後でlibft使うからいらない。*/
static int	ft_isset(char c, char const *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		++set;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	start;
	size_t	end;
	char	*result;

	i = 0;
	start = 0;
	if (!s1 || !set)
		return (NULL);
	while (s1[start] && ft_isset(s1[start], set))
		start++;
	end = strlen(s1);
	while (end > start && ft_isset(s1[end - 1], set))
		end--;
	result = malloc(sizeof(char) * (end - start + 1));
	if (result == NULL)
		return (NULL);
	while (start < end)
		result[i++] = s1[start++];
	result[i] = '\0';
	return ((char *)result);
}

char *ft_itoa(int num)//i=0-255の範囲でよい
{
    int i;
    char *buff;

    buff = (char*)malloc(20);
    if (buff == NULL)
        return(NULL);
    i = 0;
    if (num / 100 > 0) {
        buff[i] = '0' + (num % 1000) / 100;
        i++;
    }
    if (num / 10 > 0) {
        buff[i] = '0' + (num % 100) /10;
        i++;
    }
    buff[i] = '0' + (num % 10);
    i++;
    buff[i] = '\0';
    return(buff);
}

size_t ft_strlen(const char *str)
{
	return strlen(str);
}

char *ft_strncpy(char *dst, const char *src, size_t len)
{
	return strncpy(dst, src, len);
}

int ft_strcmp(const char *s1, const char *s2)
{
	return strcmp(s1, s2);
}

int ft_strncmp(const char *s1, const char *s2, size_t n)
{
	return strncmp(s1, s2, n);
}

char *ft_strchr(const char *s, int c)
{
	return strchr(s, c);
}

char *ft_strdup(const char *s1)
{
	return strdup(s1);
}

char *ft_strncat(char *s1, const char *s2, size_t n)
{
	return strncat(s1, s2, n);
}

char	*ft_strndup(const char *str, size_t n)
{
	char	*line;
	size_t		i;

	line = malloc(sizeof(char) * (n + 1));
	i = 0;
	while (i < n)
	{
		line[i] = str[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

