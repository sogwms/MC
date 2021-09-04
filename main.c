#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <stdbool.h>

#include "mc.h"


static mc_sem_t g_sem;

int task3(uint16_t sta)
{
    static char *task = "task1";

    switch (sta) {
        case 0:
        case 1:
            printf("%s case 1\n", task);
            break;
        case 2:
            printf("%s case 2\n", task);
            break;
        default:
            printf("invalid\n");
    }
}

static int sem = false;

int task1(mc_t *mct)
{
    static int cnt = 0;

    printf("task 1\n");

    MC_BEGIN(mct);
    while (1) {
        printf("entered task 1\n");

        MC_SEM_RELEASE(mct, &g_sem);
        // MC_WAIT_UNTIL(mct, sem == false);
        sem = true;
        printf("task 1 running\n");
        printf("produce %d\n", cnt++);
        MC_YIELD(mct);
    }
    MC_END(mct)

    return 0;
}

int task2(mc_t *mct)
{
    static int cnt = 0;

    printf("task 2\n");

    MC_BEGIN(mct);
    while (1) {

        printf("entered task 2\n");

        MC_SEM_TAKE(mct, &g_sem);
        // MC_WAIT_UNTIL(mct, sem == true);
        sem = false;
        printf("task 2 running\n");
        printf("consumer %d\n", cnt++);
    }
    MC_END(mct)

    return 0;
}

int main(void) 
{
    mc_t c1, c2;

    MC_INIT(&c1);
    MC_INIT(&c2);
    MC_SEM_INIT(&g_sem);

    while (1) {
        task2(&c2);
        task1(&c1);
        sleep(2);
    }

}
