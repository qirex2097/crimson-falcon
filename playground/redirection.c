#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(void) {
    int fd;
    int fd_backup;
    
    // 標準出力をバックアップ
    fd_backup = dup(STDOUT_FILENO);
    if (fd_backup < 0) {
        perror("dup");
        exit(1);
    }

    // ファイルをオープン
    fd = open("ttt.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd < 0) {
        perror("ttt.txt");
        exit(1);
    }
    
    // 標準出力をファイルにリダイレクト
    if (dup2(fd, STDOUT_FILENO) < 0) {
        perror("dup2");
        exit(1);
    }

    write(1, "HELLO\n", 7);
    
    // 標準出力を元に戻す
    if (dup2(fd_backup, STDOUT_FILENO) < 0) {
        perror("dup2");
        exit(1);
    }

    close(fd_backup);
    
    printf("WORLD\n");

    return 0;
}