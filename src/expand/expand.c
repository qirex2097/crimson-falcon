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

int set_env_var_value(char *new_line, char *line, int length)
{
    char env_var_name[LINE_MAX];
    const char *env_var_value;

    ft_strncpy(env_var_name, line, length - 1);
    env_var_name[length - 1] = '\0';
    env_var_value = ms_getenv(env_var_name);
    if (env_var_value != NULL)
    {
        ft_strncpy(new_line, env_var_value, ft_strlen(env_var_value));
        return ft_strlen(env_var_value);
    }
    return(0);
}

void replace_env_variable(char *new_line, char *line, int *pi, int *pj, int status)
{
    int end;
    char *num_str;

    if (line[1] == '?')
    {
        num_str = ft_itoa(status);
        ft_strncpy(&new_line[*pj], num_str, ft_strlen(num_str));//ステータスをitoaしてからコピーする
        *pj += ft_strlen(num_str);
        (*pi)++;
        free(num_str);
    }
    else
    {
        end = get_env_variable_name_end(&line[*pi]);//環境変数名の最後の位置
        if (end > 0)
        {
            *pj += set_env_var_value(&new_line[*pj], &line[*pi + 1], end);
            *pi = *pi + end - 1;
        }
        else
        {
            new_line[(*pj)++] = line[*pi];
        }
    }
}

char *remove_quotes(char *line, int status)
{
    char *new_line;
    int i, j;
    bool in_single_quotes;
    bool in_double_quotes;

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
            new_line[j++] = line[++i]; //バックスラッシュの後の文字を入れる
        }
        else if (line[i] == '$')//環境変数の処理
        {
            replace_env_variable(new_line, line, &i, &j, status);
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

void expand(t_token *tokens, int status)
{
    t_token *pt;
    char *new_token;

    pt = tokens;
    while (pt)
    {
        if (ft_strchr(pt->token, '\'') != NULL ||
            ft_strchr(pt->token, '"') != NULL ||
            ft_strchr(pt->token, '\\') != NULL ||
            ft_strchr(pt->token, '$')) {
            new_token = remove_quotes(pt->token, status);
            free(pt->token);
            pt->token = new_token;
        }
        pt = pt->next;
    }
}
