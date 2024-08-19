#include "minishell.h"

bool is_alpha(char ch)
{
    return (('a' <= ch && ch <= 'z') || ('A' <= ch && ch <= 'Z'));
}

bool is_digit(char ch)
{
    return ('0' <= ch && ch <= '9');
}

bool is_alpha_under(char ch)
{
    return (is_alpha(ch) || ch == '_');
}

bool is_alpha_under_number(char ch)
{
    return (is_alpha_under(ch) || is_digit(ch));
}

int get_env_variable_name_end(char *line)
{
    int i;
    i = 0;
    if (line[0] != '$' && is_alpha_under(line[1])) {
        return(0);
    }
    i = 1;
    while(is_alpha_under_number(line[i]))
        i++;
    return(i);
}

char *remove_quotes(char *line)
{
    char *new_line;
    int i, j;
    bool in_single_quotes;
    bool in_double_quotes;
    int end;
    char *env_var_name;
    char *env_var_value;

    new_line = (char*)malloc(LINE_MAX * sizeof(char));

    i = j = 0;
    in_single_quotes = false;
    in_double_quotes = false;
    while(line[i])
    {
        if (line[i] == '\'' && !in_double_quotes)
        {
            in_single_quotes = !in_single_quotes;
        }
        else if (line[i] == '"' && !in_single_quotes)
        {
            in_double_quotes = !in_double_quotes;
        }
        else if (in_single_quotes && line[i] != '\'')//シングルクオート内はそのままコピー
        {
            new_line[j++] = line[i];
        }
        else if ((!in_single_quotes && !in_double_quotes) && line[i] == '\\')//バックスラッシュの処理
        {
            i++;
            new_line[j++] = line[i];
        }
        else if (line[i] == '$' && line[i + 1] == '?')//環境変数の処理
        {
            strncpy(&new_line[j], "100", 3);//ステータスをitoaしてからコピーする
            j += 3;
            i++;
        }
        else if (line[i] == '$')//環境変数の処理
        {
            end = get_env_variable_name_end(&line[i]);//環境変数名の最後の位置
            if (end > 0)
            {
                env_var_name = (char *)malloc((end + 1) * sizeof(char));
                strncpy(env_var_name, &line[i+1], end - 1);
                env_var_name[end] = '\0';
                env_var_value = getenv(env_var_name);
                if (env_var_value != NULL)
                {
                    strncpy(&new_line[j], env_var_value, strlen(env_var_value));
                    j += strlen(env_var_value);
                }
                free(env_var_name);
                i = i + end - 1;
            }
            else
            {
                new_line[j++] = line[i];
            }
        }
        else if ((!in_single_quotes && !in_double_quotes) ||
                 (in_double_quotes && line[i] != '"'))
        {
            new_line[j++] = line[i];
        }
        i++;
    }
    new_line[j] = '\0';
    
    return(new_line);
}

void expand(t_token *tokens)
{
    t_token *pt;
    char *new_token;

    pt = tokens;
    while (pt)
    {
        if (strchr(pt->token, '\'') != NULL || 
            strchr(pt->token, '"') != NULL || 
            strchr(pt->token, '\\') != NULL || 
            strchr(pt->token, '$')) {
            new_token = remove_quotes(pt->token);
            free(pt->token);
            pt->token = new_token;
        }
        pt = pt->next;
    }
}

