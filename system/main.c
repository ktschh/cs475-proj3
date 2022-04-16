/*  main.c  - main */

#include <xinu.h>
#include <stdio.h>
#include <stdlib.h>

#define N 5	//number of philosophers and forks

//TODO - locks must be declared and initialized here
mutex_t forks[N] = {0,0,0,0,0};
mutex_t print_lock = FALSE;


/**
 * Delay for a random amount of time
 * @param alpha delay factor
 */
void	holdup(int32 alpha)
{
	long delay = rand() * alpha;
	while (delay-- > 0)
		;	//no op
}

/**
 * Eat for a random amount of time
 */
void	eat()
{
	holdup(10000);
}

/**
 * Think for a random amount of time
 */
void	think()
{
	holdup(1000);
}



/**
 * Philosopher's code
 * @param phil_id philosopher's id
 */
void	philosopher(uint32 phil_id)
{
    srand(phil_id);
	uint32 left = phil_id;
    uint32 right;
	if (phil_id == 4)
    {
        right = 0;
    }
    else
    {
        right = phil_id+1;
    }

	while (TRUE)
	{
		//TODO
        int number = rand() % 100;
		//think 70% of the time
        if (number < 70)
        {
            mutex_lock(&print_lock);
            kprintf("Philosopher %u thinking: zzzzzZZZz\n", phil_id);
            mutex_unlock(&print_lock);
            think();
        }
		//eat 30% of the time
        else 
        {
                //check left fork
                if (forks[left] == TRUE)
                {
                    continue;
                }
                else
                {
                    mutex_lock(&forks[left]);
                    if (forks[right] == TRUE)
                    {
                        mutex_unlock(&forks[left]);
                        continue;
                    }
                    else
                    {
                        mutex_lock(&forks[right]);

                        mutex_lock(&print_lock);
                        kprintf("Philosopher %u eating: nom nom nom\n", phil_id);
                        mutex_unlock(&print_lock);

                        eat();
                        mutex_unlock(&forks[right]);
                        mutex_unlock(&forks[left]);
                    }
                }
        }
	}
}

int	main(uint32 argc, uint32 *argv)
{
	//do not change
	ready(create((void*) philosopher, INITSTK, 15, "Ph1", 1, 0), FALSE);
	ready(create((void*) philosopher, INITSTK, 15, "Ph2", 1, 1), FALSE);
	ready(create((void*) philosopher, INITSTK, 15, "Ph3", 1, 2), FALSE);
	ready(create((void*) philosopher, INITSTK, 15, "Ph4", 1, 3), FALSE);
	ready(create((void*) philosopher, INITSTK, 15, "Ph5", 1, 4), FALSE);

	return 0;
}
