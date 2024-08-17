#include <unistd.h>

int main(void)
{
	int pfd[2];

	pipe(pfd);
	close(pfd[0]);
//	dup2(pfd[1], STDOUT_FILENO);
	close(pfd[1]);
	write(STDOUT_FILENO, "HELLO\n", 6);
	write(STDERR_FILENO, "HERE\n", 5);
}
