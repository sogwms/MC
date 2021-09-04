#ifndef __MC_CORE_H__
#define __MC_CORE_H__

#include <stdint.h>

typedef struct mc {
    uint16_t sta;
}mc_t;

#define __MC_GET_INS(type, name) ((type *)(name))

#define MC_INIT(mct) ((mc_t *)(mct))->sta = 0

#define MC_BEGIN(mct) char __mc_yield_flag__ = 1; switch (mct->sta) { case 0:

#define MC_END(mct) MC_INIT(mct); default: break; }

#define __MC_MARK(mct, value)  mct->sta = value; case value: 

#endif


