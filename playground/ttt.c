#include <stdio.h>
#include <libc.h>

/*===strtrim===*/
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

/*==========================*/

char    *skip_blank(char *line)
{
    char    *current = line;
    while (*current == ' ' && *current)
        current++;
    return current;
}

static char *skip_quate(char *p, char quote)
{
    if(*p != quote)
        return(p);
    p++;
    while(*p != quote && *p)
        p++;
    if(*p == quote)
        p++;
    return(p);
}

char *skip_token(char *line)
{
    char *p;

    p = line;
    if (*p == '\'' || *p == '"')
    {
        p = skip_quate(p, *p);
    }
    else if (*p == ';')
    {
        p++;
    }
    else
    {
        while (*p != ' ' && *p != ';' && *p) 
        {
            if (*p == '\\' && *(p + 1) != '\0')
                p = p + 2;
            else if (*p == '\'' || *p == '"')
                p = skip_quate(p, *p);
            else
                p++;
        }
    }
    return p;
}


void expand(char **buffs) 
{
    int i = 0;
    while (buffs[i] != NULL)
    {
        char *p = buffs[i];
        char *buff;
        if(*p == '\'')
        {
            buff = ft_strtrim(p, "'");
        }
        else if (*p == '"')
        {
            buff = ft_strtrim(p, "\"");
        }
        else
        {
            buff = strdup(p);
        }
        free(buffs[i]);
        buffs[i] = buff;
        i++;
    }
}

char    *copy_token(char *start, char *end)
{
    char    *token;
    char    *src;
    char    *dest;

    token = malloc(sizeof(char) * (end - start + 1));
    if(token == NULL)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    src = start;
    dest = token;
    while(src < end)
    {
        if(*src == '\\' && *(src + 1) != '\0')
            src++;
        *dest++ = *src++;
    }
    *dest = '\0';
    return(token);
}

char **tokenizer(char *line)
{
    int i;
    char *start;
    char **tokens;

    tokens = malloc(sizeof(char *) * 1000);
    if (tokens == NULL)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    i = 0;
    while (*line)
    {
        line = skip_blank(line);
        if (*line == '\0')
            break;

        if (*line == ';')
        {
            tokens[i++] = copy_token(line, line + 1);
            line++;
        }
        else
        {
            start = line;
            line = skip_token(line);
            //tokenをcopyして配列に格納する
            tokens[i++] = copy_token(start, line);
        }
    }
    tokens[i] = NULL;

    return tokens;
}

int main()
{
    char *input = "ls;pwd";
    char **tokens = tokenizer(input);
    for (int i = 0; tokens[i] != NULL; i++)
    {
        printf("Token %d: %s\n", i, tokens[i]);
        free(tokens[i]);
    }
    free(tokens);
    return 0;
}
