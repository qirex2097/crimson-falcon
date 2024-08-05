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

t_node *expr(char   *token[]);
t_node *mul();

bool is_numeric(const char *str) {
    // 文字列が NULL もしくは空の場合、数字ではないと見なします
    if (str == NULL || *str == '\0') {
        return false;
    }
    // 文字列の各文字を調べます
    while (*str) {
        if (!isdigit(*str)) {
            return false;  // 数字ではない文字が含まれている場合
        }
        str++;
    }
    return true;  // すべての文字が数字だった場合
}

//+ - の判定
t_node *expr(char   *token[])
{
    t_node  *node;
    int i = 0;

    if(!is_numeric(token[i]))
    {
        perror("error!\n");
        exit(1);
    }
    else
    {
        node = new_node_num(atoi(token[i]));
        i++;
        while(token[i])
        {
            if(strcmp(token[i], "+") == 0 && is_numeric(token[i+1]))
            {
                node = new_node(ND_ADD, node, new_node_num(atoi(token[i+1])));
                i = i + 2;
            }
            else if(strcmp(token[i],"-") == 0 && is_numeric(token[i+1]))
            {
                node = new_node(ND_SUB, node, new_node_num(atoi(token[i+1])));
                i = i + 2;
                
            }
            else
            {
                perror("error!!\n");
                exit(1);
            }
        }
    }
    return(node);
}



int main()
{
    char    *token[] = {"100", "+" , "300", "-", "7", NULL};

    t_node  *node = expr(token);
    return(0);
}