#include <libc.h>
#include <stdbool.h>

typedef struct s_token {
    char *word;
    int kind;
    struct s_token *next;
} t_token;

typedef enum e_token_kind {
    TK_WORD,
    TK_EOF
} t_token_kind;

bool skip_blank(char **line, char *current) {
    if (*current == ' ') {
        while (*current == ' ')
            current++;
        *line = current;
        return true;
    }
    return false;
}

bool is_blank(char c) {
    return (c == ' ' || c == '\t' || c == '\n');
}

bool is_metachara(char c) 
{
    return (c && strchr("|&;()<>\t\n", c));
}

bool    start_with(const char *s, const char *key)
{
    return(memcmp(s, key, strlen(key)) == 0);
}

bool    is_operator(const char *s)
{
    static char *const operators[] = {"|", "<", ">", ">>", "<<", "&&", "||", ";", "&"};
    size_t i;

    i = 0;
    while (i < sizeof(operators) / sizeof(operators[0]))
    {
        if (start_with(s, operators[i]))
            return (true);
        i++;
    }
    return (false);
}

t_token *new_token(char *word, t_token_kind kind) {
    t_token *token = calloc(1,sizeof(t_token));
    token->word = word;
    token->kind = kind;
    token->next = NULL;
    return token;
}

t_token *word(char **line)
{
    char *current = *line;
    char *start = current;
    char *word;

    while (*current && !is_blank(*current) && !is_metachara(*current))
        current++;
    if (current == start)
        return NULL;
    word = strndup(start, current - start);
    *line = current;
    return new_token(word, TK_WORD);
}

t_token *tokenize(char *line) 
{
    t_token head;
    t_token *cur = &head;

    while (*line) {
        if (skip_blank(&line, line))
            continue;
        if (is_operator(line)) {
            cur->next = new_token(strndup(line, 1), TK_WORD);
            cur = cur->next;
            line++;
        } else {
            cur->next = word(&line);
            if (cur->next)
                cur = cur->next;
        }
    }
    cur->next = new_token(NULL, TK_EOF);
    return(head.next);
}

// for debug
void print_token(t_token *token) {
    while (token) {
        printf("kind=%d, word=%s\n", token->kind, token->word);
        token = token->next;
    }
}

int main() {
    char *line = "ls -l | grep foo";
    t_token *token = tokenize(line);
    print_token(token);
    return 0;
}