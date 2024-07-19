#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <limits.h>

// エラーメッセージを表示して終了する関数
void fatal_error(const char *msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}

// エラーメッセージを表示して特定のステータスコードで終了する関数
void err_exit(const char *filename, const char *msg, int status) {
    fprintf(stderr, "%s: %s\n", filename, msg);
    exit(status);
}

// コマンドのパスを探す関数
char *search_path(const char *filename) {
    char path[PATH_MAX];
    char *value;
    char *end;

    value = getenv("PATH"); // PATH環境変数を取得
    while (*value) {
        memset(path, 0, PATH_MAX); // パスのバッファをクリア
        end = strchr(value, ':'); // ':'の位置を探す
        if (end) {
            strncpy(path, value, end - value); // ':'までのパスをコピー
        } else {
            strncpy(path, value, PATH_MAX - 1); // 残りの文字列をコピー
        }
        strncat(path, "/", PATH_MAX - strlen(path) - 1); // '/'を追加
        strncat(path, filename, PATH_MAX - strlen(path) - 1); // コマンド名を追加

        // コマンドが存在し実行可能かチェック
        if (access(path, X_OK) == 0) {
            return strdup(path); // 実行可能ならパスを返す
        }

        if (!end) {
            break; // ':'が見つからない場合ループ終了
        }
        value = end + 1; // 次のパスに進む
    }
    return NULL; // 見つからない場合NULLを返す
}

// コマンドのパスが有効かチェックする関数
void validate_access(const char *path, const char *filename) {
    if (path == NULL) {
        err_exit(filename, "command not found", 127);
    }
    if (access(path, F_OK) < 0) {
        err_exit(filename, "command not found", 127);
    }
}

// コマンドを実行する関数
int exec_command(char *argv[]) {
    extern char **environ;
    const char *path = argv[0];
    pid_t pid;
    int wstatus;

    pid = fork(); // プロセスをフォーク
    if (pid < 0) {
        fatal_error("fork"); // フォークに失敗
    } else if (pid == 0) {
        // 子プロセス
        if (strchr(path, '/') == NULL) {
            path = search_path(path); // コマンドのフルパスを検索
        }
        validate_access(path, argv[0]); // パスが有効かチェック
        execve(path, argv, environ); // コマンドを実行
        fatal_error("execve"); // execveが失敗した場合
    } else {
        // 親プロセス
        wait(&wstatus); // 子プロセスの終了を待つ
        return WEXITSTATUS(wstatus); // 子プロセスの終了ステータスを返す
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s command [args...]\n", argv[0]);
        return EXIT_FAILURE;
    }
    return exec_command(argv + 1);
}
