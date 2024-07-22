#include <stdio.h>
#include <libc.h>

char    *skip_blank(char *line)
{
    char    *current = line;
    while (*current == ' ' && *current)
        current++;
    return current;
}

char    *word(char *line)
{
    char    *current = line;
    while (*current != ' ' && *current)
        current++;
    return current;


}

void tokenizer(char *line)
{
    while(*line)
    {
        line = skip_blank(line);
        printf("%s\n", line);
        break ;
    }

}



int main()
{
    char *line = "    ls -l  ";
    // printf("$%s$\n", skip_blank(line));
    tokenizer(line);
}