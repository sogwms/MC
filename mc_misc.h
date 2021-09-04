#ifndef __MC_MISC_H__
#define __MC_MISC_H__

#include "./mc_core.h"

#define MC_WAIT_UNTIL(mct, expression) \
    do {\
        __MC_MARK(mct, __LINE__);\
        if (!(expression)) { \
            return 1;\
        }\
    }while(0)

#define MC_YIELD(mct) \
    do { \
        __mc_yield_flag__ = 0; \
        __MC_MARK(mct, __LINE__); \
        if (__mc_yield_flag__ == 0) { \
            return 1; \
        } \
    }while(0)


#endif
