#ifndef _TIME_COMPLEX_H_
#define _TIME_COMPLEX_H_

#include <time.h>

struct complexity
{
	clock_t s_time;
	clock_t e_time;
};

#define INIT_CLOCK_F	((clock_t)0)

typedef struct complexity complexity_t;

complexity_t t_current = {
	.s_time = INIT_CLOCK_F,
	.e_time = INIT_CLOCK_F
};

#define ALG_INTR_START()	((t_current.s_time) = clock())
#define ALG_INTR_END()		((t_current.e_time) = clock())
#define ALG_INTR_GET_DIFF()	(((double)((t_current.e_time) - (t_current.s_time))) / CLOCKS_PER_SEC)

#endif /* _TIME_COMPLEX_H_ */
