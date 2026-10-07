#include "nitro/types.h"

#pragma opt_propagation off

BOOL TryLinkNodes_020b63c4(s8 *nodeValues, s8 (*links)[4], int first, int second) {
    BOOL linked = FALSE;
    int span;

    if (first > second) {
        int swap = first;
        first = second;
        second = swap;
    }
    if (nodeValues[first] < 0 || nodeValues[second] < 0 || first == second ||
        (span = second - first) > 3 - (first & 1)) {
        return FALSE;
    }
    if (span == 2) {
        links[second][3] = first;
        links[first][1] = second;
        linked = TRUE;
    } else if ((first & 1) == 0 && span == 1) {
        links[second][0] = first;
        links[first][2] = second;
        linked = TRUE;
    } else if ((first == 1 && nodeValues[0] < 0) ||
               (first == 3 && nodeValues[2] < 0 && nodeValues[5] >= 0 && links[0][1] < 0)) {
        links[second][3] = first;
        links[first][0] = second;
        linked = TRUE;
    } else if ((first == 1 && nodeValues[3] < 0 && links[5][3] < 0) ||
               (first == 3 && nodeValues[5] < 0)) {
        links[second][2] = first;
        links[first][1] = second;
        linked = TRUE;
    } else if ((first == 0 && nodeValues[1] < 0) ||
               (first == 2 && nodeValues[3] < 0 && nodeValues[4] >= 0 && links[1][1] < 0)) {
        links[second][3] = first;
        links[first][2] = second;
        linked = TRUE;
    } else if ((first == 0 && nodeValues[2] < 0 && links[4][3] < 0) ||
               (first == 2 && nodeValues[4] < 0)) {
        links[second][0] = first;
        links[first][1] = second;
        linked = TRUE;
    }
    return linked;
}
