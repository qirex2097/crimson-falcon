#include "minishell.h"


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