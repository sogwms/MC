#ifndef __MC_SEM_H__
#define __MC_SEM_H__

#include "./mc_core.h"

typedef struct mc_sem {
    int8_t count;
}mc_sem_t;

#define MC_SEM_INIT(mc_sem) ((mc_sem_t *)(mc_sem))->count = 0
#define MC_SEM_TAKE(mct, mc_sem)	\
  do {						\
    MC_WAIT_UNTIL(mct, __MC_GET_INS(mc_sem_t, mc_sem)->count > 0);		\
    --__MC_GET_INS(mc_sem_t, mc_sem)->count;				\
  } while(0)
#define MC_SEM_RELEASE(mct, mc_sem)  ++__MC_GET_INS(mc_sem_t, mc_sem)->count

#endif
