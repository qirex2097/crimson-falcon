#include <libc.h>
#include <stdbool.h>
#include <ctype.h>

/*-------------------------------------------*/
typedef enum {
  ND_ADD, // +
  ND_SUB, // -
  ND_MUL, // *
  ND_DIV, // /
  ND_NUM, // 整数
} NodeKind;

// 抽象構文木のノードの型
typedef struct s_node {
  NodeKind kind; // ノードの型
  struct s_node *lhs;     // 左辺
  struct s_node *rhs;     // 右辺
  int val;       // kindがND_NUMの場合のみ使う
} t_node;

typedef enum {
    TK_NUM,
    TK_RESERVED,
    TK_EOF,
} TokenKind;

typedef struct s_token
{
    TokenKind kind;
    struct s_token *next;
    int val; // value
    char    *str;
}   t_token;

/*-------------------------------------------*/

// グローバル変数
t_token *token;

/*-------------------------------------------*/

int expect_number()
{
    if(token->kind != TK_NUM)
        exit(1);
    int val = token->val;
    token = token->next;
    return (val);
}

bool consume(char op)
{
    if(token->kind != TK_RESERVED || token->str[0] != op)
        return false;
    token = token->next;
    return true;
}

void expect(char op)
{
    if(token->kind != TK_RESERVED || token->str[0] != op)
    {
        fprintf(stderr, "Expected '%c'\n", op);
        exit(1);
    }
    token = token->next;
}

bool at_eof()
{
    return token->kind == TK_EOF;
}

/*-------------------------------------------*/

// 新しいノードを作る関数
t_node *new_node(NodeKind kind, t_node *lhs, t_node *rhs)
{
    t_node *node = calloc(1, sizeof(t_node));
    if(node == NULL)
    {
        fprintf(stderr, "calloc error\n");
        exit(1);
    }
    node->kind = kind;
    node->lhs = lhs;
    node->rhs = rhs;
    return node;
}

// 整数のノードを作る関数
t_node *new_node_num(int val)
{
    t_node *node = calloc(1, sizeof(t_node));
    if(node == NULL)
    {
        fprintf(stderr, "calloc error\n");
        exit(1);
    }
    node->kind = ND_NUM;
    node->val = val;
    return node;
}

/*-------------------------------------------*/

t_node *expr();
t_node *mul();
t_node *primary();

//+ - の判定
t_node *expr()
{
    t_node *node = mul();
    for(;;)
    {
        if(consume('+'))
            node = new_node(ND_ADD, node, mul());
        else if(consume('-'))
            node = new_node(ND_SUB, node, mul());
        else
            return node;
    }
}

//* / の判定
t_node *mul()
{
    t_node *node = primary();
    for(;;)
    {
        if(consume('*'))
            node = new_node(ND_MUL, node, primary());
        else if(consume('/'))
            node = new_node(ND_DIV, node, primary());
        else
            return node;
    }
}

// () numの判定
t_node *primary()
{
    if(consume('('))
    {
        t_node *node = expr();
        expect(')');
        return node;
    }
    return new_node_num(expect_number());
}

int main()
{
    char *tokens[] = {"1", "+", "2", "*", "3"};
}
