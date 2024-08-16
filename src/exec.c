#include "minishell.h"

//TODO search_pathを書き換える！
char	*search_path(const char *filename)
{
	char	path[PATH_MAX];
	char	*value;
	char	*end;

	value = getenv("PATH");
	while (*value)
	{
		// /bin:/usr/bin
		//     ^
		//     end
		bzero(path, PATH_MAX);
		end = strchr(value, ':');
		if (end) {
			strncpy(path, value, end - value);
		} else {
			strncpy(path, value, PATH_MAX - 1);
			path[PATH_MAX - 1] = '\0';
		}
		strncat(path, "/", PATH_MAX - 1);
		path[PATH_MAX - 1] = '\0';
		strncat(path, filename, PATH_MAX - 1);
		path[PATH_MAX - 1] = '\0';
		if (access(path, X_OK) == 0)
		{
			char	*dup;

			dup = strdup(path);
			if (dup == NULL)
				fatal_error("strdup");
			return (dup);
		}
		if (end == NULL)
			return (NULL);
		value = end + 1;
	}
	return (NULL);
}

void validate_access(const char *path, const char *filename)
{
	if (path == NULL)
		err_exit(filename, "command not found", 127);
	if (access(path, F_OK) < 0)
		err_exit(filename, "command not found", 127);
}

int exec_cmd(t_cmd *cmd, int prev_fd, int *pfd)
{
	char *path;
	char **argv = cmd->args;
	int wstatus;
    pid_t pid;

    if (is_builtin(cmd->args))
    {
        int original_stdin = -1;
        int original_stdout = -1;

        if (prev_fd != -1) {
            original_stdin = dup(STDIN_FILENO);
            dup2(prev_fd, STDIN_FILENO);
            close(prev_fd);
        }
        if (cmd->next) {
            original_stdout = dup(STDOUT_FILENO);
            dup2(pfd[1], STDOUT_FILENO);
            close(pfd[1]);
        }
		if (open_redir_file(cmd->redirects) < 0) {
			return(1);//リダイレクトのファイルがオープンできない時は子プロセス終了
		}
        wstatus = exec_builtin_command(cmd->args);
        // 標準入力と標準出力を戻す
        if (original_stdin != -1) {
            dup2(original_stdin, STDIN_FILENO);
        }
        if (original_stdout != -1) {
            dup2(original_stdout, STDOUT_FILENO);
        }
        return(wstatus);
    } 

	pid = fork();
	if (pid < 0)
		fatal_error("fork");
    if(pid == 0)
    {
		reset_signal();
		if (prev_fd != -1) {	//パイプの読み出し側が設定されていたら
			dup2(prev_fd, STDIN_FILENO);
			close(prev_fd);
		}
		if (cmd->next) {	//パイプの書き込み側を設定する
			close(pfd[0]);
			dup2(pfd[1], STDOUT_FILENO);
			close(pfd[1]);
		}
		if (open_redir_file(cmd->redirects) < 0) {
			exit(1);//リダイレクトのファイルがオープンできない時は子プロセス終了
		}
		if(strchr(argv[0], '/') == NULL)
			path = search_path(argv[0]);
		else
			path = strdup(argv[0]);
		validate_access(path, argv[0]);//コマンドがない時は子プロセス終了
		execve(path, argv, 0);
		fatal_error("execve");//ここには来ない。
    }
    else
    {
		if (prev_fd != -1) {
			close(prev_fd);	//使わないパイプはクローズする
		}
		if (cmd->next) {
			close(pfd[1]);
		}
        wait(&wstatus);
		return(wstatus);
    }
	
	return (0);
}

int exec(t_node *node)
{
	t_cmd *cmd;
	int status = 0;
	int prev_fd;
	int pfd[2];

	while (node)
	{
		prev_fd = -1;	//パイプ処理用（読み出し側）
		cmd = &node->command;
		while (cmd)
		{
            if (cmd->next)
            {
                if (pipe(pfd) < 0) 	// パイプの次のコマンドがあればパイプを作る
                {
                    fatal_error("pipe");
                }
            }
            status = exec_cmd(cmd, prev_fd, pfd);
            if (cmd->next)
            {
                prev_fd = pfd[0];	//パイプの読み出し側を更新
            }
			if (!WIFEXITED(status))
			{
				if (cmd->next)
				{
					close(prev_fd);
				}
				break;//子プロセスの戻り値が0以外の場合はパイプの処理を中断する
			}
			cmd = cmd->next;
		}
		node = node->next;
	}
	return(WEXITSTATUS(status));
}

