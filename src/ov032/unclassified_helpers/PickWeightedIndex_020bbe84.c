#include "nitro/types.h"

extern unsigned int random_next_scaled_0202aa04(unsigned int upperBound);

int PickWeightedIndex_020bbe84(u8 *weights, int count)
{
    int total;
    u8 *weight;
    int i;
    int roll;
    int sum;

    total = 0;
    i = 0;
    weight = weights;
    if (count > 0) {
        for (; i < count; i++) {
            total += *weight;
            weight++;
        }
    }
    roll = random_next_scaled_0202aa04(total);
    sum = 0;
    for (i = 0; i < count; i++, weights++) {
        if (*weights != 0) {
            sum += *weights;
            if (sum >= roll) {
                return i;
            }
        }
    }
    return -1;
}
