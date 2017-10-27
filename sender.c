#include <stdbool.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

#define SLEEP_TIME 4000000

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		fprintf(stderr, "Usage ./Signal_Sender 'pgrep Signal_Receiver'\n");
	}
	
	unsigned pid = atoi(argv[1]);

	printf("pid=%u\n",pid);
    usleep(SLEEP_TIME);

    printf("Send SIGHUP\n");
    kill(pid,SIGHUP);
    usleep(SLEEP_TIME);

    printf("Send SIGUSR1\n");
    kill(pid,SIGUSR1);
    usleep(SLEEP_TIME);

    printf("Send SIGUSR2\n");
    kill(pid,SIGUSR2);
    usleep(SLEEP_TIME);

    printf("Send SIGINT\n");
    kill(pid,SIGINT);
    usleep(SLEEP_TIME);

    printf("Send SIGTERM\n");
    kill(pid,SIGTERM);
    usleep(SLEEP_TIME);

    printf("Send SIGKILL\n");
    kill(pid,SIGKILL);
    usleep(SLEEP_TIME);

	return 0;
}
