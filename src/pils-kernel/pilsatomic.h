/* This file is public domain */
#ifndef _PILS_PILSATOMIC_H_
#define _PILS_PILSATOMIC_H_
#include "datamodel.h"

#define PILS_INTERLOCKED_INCREMENT(x) __sync_add_and_fetch(&(x), 1)
#define PILS_INTERLOCKED_DECREMENT(x) __sync_add_and_fetch(&(x), -1)
#define PILS_INTERLOCKED_INCREMENT_RETURN PILS_INTERLOCKED_INCREMENT
#define PILS_INTERLOCKED_DECREMENT_RETURN PILS_INTERLOCKED_DECREMENT

#endif

