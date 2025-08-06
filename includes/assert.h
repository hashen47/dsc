#include <stdio.h>
#include <stdlib.h>

#ifndef ASSERT_H
#define ASSERT_H

#define ASSERT_ENABLED 1

#if ASSERT_ENABLED
#define ASSERT(c, m) do { \
	if (!(c)) { \
		fprintf(stderr, "%s:%d: assertion %s failed: %s", __FILE__, __LINE__, #c, m); \
		exit(1); \
	} \
} while(0)
#else
#define ASSERT(c, m) do { \
	if ((c)) {} \
} while(0)
#endif

#endif
