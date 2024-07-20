#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct s_token t_token;
enum e_token_kind {
    TK_WORD,
    TK_OP,
    TK_EOF,
};
typedef enum e_token_kind t_token_kind;

struct s_token {
    char *word;
    t_token_kind kind;
    t_token *next;
};

// 新しいトークンを作成する関数
t_token *new_token(t_token_kind kind, char *word, t_token *next) {
    t_token *tok = malloc(sizeof(t_token));
    tok->kind = kind;
    tok->word = strdup(word);
    tok->next = next;
    return tok;
}

// 入力文字列をトークン化する関数
t_token *tokenize(char *input) {
    t_token head;
    head.next = NULL;
    t_token *cur = &head;

    char *p = input;
    while (*p) {
        // 空白をスキップ
        if (isspace(*p)) {
            p++;
            continue;
        }

        // 演算子
        if (*p == '|' || *p == '<' || *p == '>') {
            char op[2] = {*p, '\0'};
            cur = cur->next = new_token(TK_OP, op, NULL);
            p++;
            continue;
        }

        // 単語
        if (isalpha(*p) || *p == '_' || *p == '$') {
            char *start = p;
            while (isalnum(*p) || *p == '_' || *p == '$' || *p == '.') p++;
            int len = p - start;
            char *word = malloc(len + 1);
            strncpy(word, start, len);
            word[len] = '\0';

            cur = cur->next = new_token(TK_WORD, word, NULL);
            free(word);
            continue;
        }

        fprintf(stderr, "undefined char: %c\n", *p);
        exit(1);
    }

    cur = cur->next = new_token(TK_EOF, "", NULL);
    return head.next;
}

// トークンリストを表示する関数
void print_tokens(t_token *tok) {
    while (tok) {
        printf("Token: ");
        switch (tok->kind) {
            case TK_WORD: printf("WORD"); break;
            case TK_OP:   printf("OPERATOR"); break;
            case TK_EOF:  printf("EOF"); break;
        }
        printf(", Value: '%s'\n", tok->word);
        tok = tok->next;
    }
}

int main() {
    char input[] = "echo 'Hello     world' '42Tokyo'";
    t_token *tokens = tokenize(input);
    print_tokens(tokens);

    // メモリの解放（本来はちゃんと行うべき）
    // ...

    return 0;
}