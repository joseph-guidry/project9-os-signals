#include <pthread.h>	// Header file for pthread library
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sysexits.h>
#include <unistd.h>

#include <sys/time.h>
#include <time.h>
#include <math.h>

#define	MILLISECONDS_PER_SECOND	1000
#define MAX_INT 1000000
/* Driver for PID and Prime output */
static void display_data(int start);

/* Find the next prime number */
int is_prime(int number);
int next_prime( int number);

/* Get and display date/time information */
static void display_date();

/* Waiting Timer */
void* timer(void *milliseconds);


int main(int argc, char **argv)
{
	int sflag = 2, rflag = 0, eflag = MAX_INT;
	char option;

	while ( (option = getopt(argc, argv, "ers:")) != -1)
	{
		printf("here\n");
		printf("%d: %s\n", option, optarg);
		switch(option)
		{
			case 'e':
				eflag = atoi(optarg);
				break;
			case 'r':
				break;
			case 's':
				sflag = atoi(optarg);
				break;
			default:
				exit(1);
		}
	}

	printf("Option values -e %d -r %d -s %d \n", eflag, rflag, sflag);
	int num = 5;

    printf("We are looking for prime numbers\n");
	
	pthread_t wait_thread;
	long wait_time = 800;

	for ( ; ; )
	{
		if ( pthread_create(&wait_thread, NULL, timer, (void *)wait_time) != 0 )
		{
			fprintf(stderr, "Failed to create thread\n");
			return(2);
		}
	
		if ( pthread_join(wait_thread, NULL) != 0)
		{
			fprintf(stderr, "Failed to join thread\n");
			return(3);
		}

		display_data(sflag);
		display_date();
	}
	
	/*
	if (set_signal_handlers() == -1)
	{
		perror("Could Not reassign signals\n");
	}
	*/
	
}

static void display_data(int start)
{
	int pid = (int)getpid();
	int prime = next_prime(start);
	printf("[%d] %d \n", pid, prime);
}

int next_prime(int num)
{
	int c;
	if (num == 2)
		c = 3;
	else
	{
		num += 2;
		c = is_prime(num) ? next_prime(num) : num;
	}

	return c;
}

int is_prime(int num)
{
	int i;
	int c = 0;
	for (i = 2; i < sqrt(num); i++)
	{
		if (num % i == 0)
			c++;
	}
	return c;
}

static void display_date()
{
	const unsigned char B_SIZE = 100;
	char output[B_SIZE];
	memset(&output, 0, B_SIZE);
	struct tm *tm_info;
	struct timeval tv;
	int m_second;

	gettimeofday(&tv, NULL);

	m_second = round((double)tv.tv_usec/MILLISECONDS_PER_SECOND);

	if ( m_second >= MILLISECONDS_PER_SECOND)
	{
		m_second -= MILLISECONDS_PER_SECOND;
		tv.tv_sec++;
	}

	tm_info = localtime(&tv.tv_sec);
	strftime(output, sizeof(output), "%Y:%m:%d %H:%M:%S", tm_info);
	printf("%s %0.1lf\n", output, (double)m_second/MILLISECONDS_PER_SECOND);
}

void* timer(void *milliseconds)
{
    // Returns number of clock ticks per second (platform dependent)
    clock_t t = clock();
    // Divide elapsed number of ticks by
    // CLOCKS_PER_SEC to get number of seconds
    while((double)(clock()-t)/CLOCKS_PER_SEC < (long)milliseconds*0.001){
        ;	// Just keep spinning
    }
    return NULL;
}
	
