#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "lfsr.h"

void lfsr_calculate(uint16_t *reg) {
    /* YOUR CODE HERE */
    uint16_t zero = ((*reg)&(1<<0))>>0;
    uint16_t two = ((*reg)&(1<<2))>>2;
    uint16_t three = ((*reg)&(1<<3))>>3;
    uint16_t five = ((*reg)&(1<<5))>>5;

    *reg = *reg>>1;

    uint16_t msb = zero^two^three^five;

    (*reg) = (*reg)|(msb<<15);
    (*reg) = (*reg)&((~0)^(((~msb)&1)<<15));
}

