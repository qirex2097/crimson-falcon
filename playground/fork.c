#include <libc.h>

int	main()
{
	int	n = 0;
	int	nPid = fork();

	if(nPid == 0)
	{
		printf("child PID:%d\n", getpid());
	}
	else
	{
		printf("%d,%d\n",getpid(),nPid);
		wait(0);
	}
	++n;
	printf("GID:%d, PID:%d\n",getpid(), getpid());
}

