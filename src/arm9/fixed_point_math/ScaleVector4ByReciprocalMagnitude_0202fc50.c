extern int func_0202fbdc(int *source_vector);
extern long long func_01ff9cd0(int unknown_argument_x);

int ScaleVector4ByReciprocalMagnitude_0202fc50(int *vector, int *source_vector)
{
    int magnitude = func_0202fbdc(source_vector);

    if (magnitude != 0) {
        long long reciprocal = func_01ff9cd0(magnitude);
        vector[0] = (int)((reciprocal * vector[0] + 0x80000000LL) >> 32);
        vector[1] = (int)((reciprocal * vector[1] + 0x80000000LL) >> 32);
        vector[2] = (int)((reciprocal * vector[2] + 0x80000000LL) >> 32);
        vector[3] = (int)((reciprocal * vector[3] + 0x80000000LL) >> 32);
    } else {
        vector[0] = 0;
        vector[1] = 0;
        vector[2] = 0;
        vector[3] = 0;
    }
    return magnitude;
}
