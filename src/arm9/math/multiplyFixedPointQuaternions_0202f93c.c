/* Behavior: Combines two 3D turns into one orientation, using fixed-point quaternion math.
 * Inputs/outputs and evidence: Four component products and sums implement the Hamilton product; all fields are staged before writing the output.
 * Uncertainty: Quaternion composition is clear; callers and its exact gameplay use are not established.
 * Source: khdays-decomp/src/calls/func_0202ef54.c; CC0, commit ab832f38b943c15f461228968a89002e1a99c03e.
 */
typedef struct FixedPointQuaternion {
    int w;
    int x;
    int y;
    int z;
} FixedPointQuaternion;

static inline int truncateFixedPointProduct(long long product)
{
    return (int)product;
}

static inline int multiplyFixedPoint(int leftFactor, int rightFactor)
{
    return truncateFixedPointProduct(((long long)leftFactor * rightFactor + 0x800LL) >> 12);
}


void multiplyFixedPointQuaternions_0202f93c(FixedPointQuaternion *resultQuaternion, const FixedPointQuaternion *leftQuaternion, const FixedPointQuaternion *rightQuaternion)
{
    FixedPointQuaternion product;

    product.w = multiplyFixedPoint(leftQuaternion->w, rightQuaternion->w) - multiplyFixedPoint(leftQuaternion->x, rightQuaternion->x)
        - multiplyFixedPoint(leftQuaternion->y, rightQuaternion->y) - multiplyFixedPoint(leftQuaternion->z, rightQuaternion->z);
    product.x = multiplyFixedPoint(leftQuaternion->y, rightQuaternion->z)
        + (multiplyFixedPoint(leftQuaternion->w, rightQuaternion->x) + multiplyFixedPoint(leftQuaternion->x, rightQuaternion->w))
        - multiplyFixedPoint(leftQuaternion->z, rightQuaternion->y);
    product.y = multiplyFixedPoint(leftQuaternion->z, rightQuaternion->x)
        + (multiplyFixedPoint(leftQuaternion->w, rightQuaternion->y) + multiplyFixedPoint(leftQuaternion->y, rightQuaternion->w))
        - multiplyFixedPoint(leftQuaternion->x, rightQuaternion->z);
    product.z = multiplyFixedPoint(leftQuaternion->x, rightQuaternion->y)
        + (multiplyFixedPoint(leftQuaternion->w, rightQuaternion->z) + multiplyFixedPoint(leftQuaternion->z, rightQuaternion->w))
        - multiplyFixedPoint(leftQuaternion->y, rightQuaternion->x);

    *resultQuaternion = product;
}
