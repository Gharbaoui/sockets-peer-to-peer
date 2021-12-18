#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char **argv)
{
	
	int n = atoi(argv[1]);
	int pids[n];
	char	*name = argv[2];
	char *args[] =  {name, NULL};
	for (int i = 0 ; i < n; ++i)
	{
		pids[i] = fork();
		if (pids[i] == 0)
		{
			execve(name, args, NULL);
			exit(10);
		}
	}
	for (int i = 0 ; i < n; ++i)
		waitpid(pids[i], NULL, 0);
}
