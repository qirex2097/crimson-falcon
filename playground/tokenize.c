#include <libc.h>
#include   <stdbool.h>
#include <ctype.h>

// トークンの種類
typedef enum {
  TK_RESERVED, // 記号
  TK_NUM,      // 整数トークン
  TK_EOF,      // 入力の終わりを表すトークン
} TokenKind;

typedef struct Token Token;

// トークン型
struct Token {
  TokenKind kind; // トークンの型
  Token *next;    // 次の入力トークン
  int val;        // kindがTK_NUMの場合、その数値
  char *str;      // トークン文字列
};

Token *token;

//tokenは直接触らない
void	error(char *fmt, ...)
{
	va_list ap;
	va_start(ap,fmt);
	vfprintf(stderr, fmt, ap);
	fprintf(stderr, "\n");
	exit(1);
}

bool	consume(char op)
{
	if(token->kind != TK_RESERVED || token->str[0] != op)
        return false;
    token = token->next;
    return(true);
}

void    expect (char op)
{
    if(token->kind != TK_RESERVED || token -> str[0] != op)
        error("not %c",op);
    token=token->next;
}

int expect_num()
{
    if(token->kind != TK_NUM)
        error("its not num");
    int val = token -> val;
    token = token -> next;
    return val;
}

bool    at_eof()
{
    return(token->kind == TK_EOF);
}

Token *new_token(TokenKind kind, Token *cur, char *str)
{
    Token *tok = calloc(1, sizeof(Token));
    if(tok == NULL)
        error("calloc");
    tok->kind = kind;
    tok->str = str;
    //cur->next = tok;
    return(tok);
}

Token *tokenize(char *p)
{
    Token   head;
    head.next = NULL;
    Token *cur = &head;

    while(*p)
    {
        if(isspace(*p))
        {
            p++;
            continue;
        }
        if(*p == '+' || *p == '-')
        {
            cur = new_token(TK_RESERVED,cur,p++);
            continue;
        }
        if(isdigit(*p))
        {
            cur = new_token(TK_NUM,cur,p);
            cur->val = strtol(p,&p,10);
            continue;
        }
        error("Tokenize error");
    }
    new_token(TK_EOF,cur,p);
    return(head.next);
}


int main(int ac, char **av)
{
    if(ac != 2)
    {
        fprintf(stderr, "invalid arguments\n");
        return 1;
    }
    token = tokenize(av[1]);

    printf(".intel_syntax noprefix\n");
    printf(".global main\n");
    printf("main:\n");

    printf("    mov rax, %d\n", expect_num());

    while(!at_eof())
    {
        if(consume('+'))
        {
            printf("    add rax, %d\n", expect_num());
            continue;
        }
        expect('-');
        printf("    sub rax, %d\n", expect_num());
    }
    printf("    ret\n");
    return 0;
}