#include <libc.h>
#include<stdbool.h>

typedef enum e_token_kind
{
    TK_WORD,
    TK_OP,
    TK_EOF,
}   t_token_kind;

struct s_token
{
    char *word;
    t_token_kind    kind;
    t_token_kind    *next;
}   t_token;

//fatal error

bool    is_metachar(char c)
{
    return (c == '|' || c == '&' || c == ';' || c == '(' || c == ')');
}


bool	is_blank(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

t_token	*new_token(char *word, t_token_kind kind)
{
	t_token	*tok;

	tok = calloc(1, sizeof(*tok));
	if (tok == NULL)
		fatal_error("calloc");
	tok->word = word;
	tok->kind = kind;
	return (tok);
}

bool    skip_blank(char **rest, char *line)
{
    if(is_blank(*line))
    {
        while(*line && is_blank(*line))
            line++;
        *rest = line;
        return(true);
    }
    *rest = line;
    return(false);
}

t_token *word(char **rest, char *line)
{
    const char  *start = line;
    char    *word;

    whlie(*line && !is_metachar(*line))
        line++;
    word = strndup(start, line - start);
    if(!word)
    {
        fatal_error("strndup");
    }
    *rest = line;
    return(new_token(word, TK_WORD));
}

void print_token(t_token *token)
{
	while (token)
	{
		ft_printf("str: %s, kind: %d\n", token->str, token->kind);
		token = token->next;
	}
}


t_token *tokenize(char *line)
{
	t_token head;
	t_token *current;

	head.next = NULL;
	current = &head;
	printf("line: %s\n", line);
	while (*line)
	{
		printf("line: %c\n", *line);
		if (skip_blank(&line, line))
			continue ;
		else
			current->next = word(&line, line);
		current = current->next;
		// line++;
	}
	current->next = new_token(NULL, TK_EOF);
	print_token(head.next);
	return (head.next);
}

int main(void)
{
    char input_line[] = "This is a test line with some words and operators.";

    // Tokenize the input line
    t_token *tokens = tokenize(input_line);

    // Print the tokens
    printf("Tokenized output:\n");
    while (tokens)
    {
        printf("Word: %s, Kind: %d\n", tokens->word, tokens->kind);
        tokens = tokens->next;
    }

    // Clean up (free memory, etc.) if needed

    return 0;
}