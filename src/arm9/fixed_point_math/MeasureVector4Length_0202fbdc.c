/* Computes the fixed-point length of a four-component vector. Evidence: Source implementation directly performs the described operations; see src/calls/func_0202f430.c. Uncertainty: No material uncertainty for the stated operation; game-specific use may depend on callers. Recovered from Days source src/calls/func_0202f430.c; CC0, commit ab832f38b943c15f461228968a89002e1a99c03e. */
extern int FX_Sqrt(int unknown_argument_x);

int MeasureVector4Length_0202fbdc(int *vector)
{
    int component_0 = vector[0];
    int component_1 = vector[1];
    int component_2 = vector[2];
    int component_3 = vector[3];

    return FX_Sqrt((int)(((long long)component_0 * component_0 + 0x800) >> 12)
                 + (int)(((long long)component_1 * component_1 + 0x800) >> 12)
                 + (int)(((long long)component_2 * component_2 + 0x800) >> 12)
                 + (int)(((long long)component_3 * component_3 + 0x800) >> 12));
}
