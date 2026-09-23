/* Computes a fixed-point direction angle with 0 along the positive horizontal component and a quarter-turn along positive vertical. Components use 1/65536-turn units. Evidence: axis special cases and quadrant branches in src/calls/FX_Atan2.c. Uncertainty: Caller-specific coordinate convention is not established. Recovered from Days source src/calls/FX_Atan2.c; CC0, commit ab832f38b943c15f461228968a89002e1a99c03e. */
extern int FX_Inv(int numerator, int denominator);
extern const short atan_lookup_table[130];

unsigned short FixedPointAtan2_020062bc(int vertical_component, int horizontal_component)
{
    int numerator;
    int denominator;
    int base_angle;
    int add_table_angle;

    if (vertical_component > 0) {
        if (horizontal_component > 0) {
            if (horizontal_component > vertical_component) {
                numerator = vertical_component;
                denominator = horizontal_component;
                base_angle = 0;
                add_table_angle = 1;
            } else if (horizontal_component < vertical_component) {
                numerator = horizontal_component;
                denominator = vertical_component;
                base_angle = 0x4000;
                add_table_angle = 0;
            } else {
                return 0x2000;
            }
        } else if (horizontal_component < 0) {
            int abs_horizontal = -horizontal_component;

            if (abs_horizontal < vertical_component) {
                numerator = abs_horizontal;
                denominator = vertical_component;
                base_angle = 0x4000;
                add_table_angle = 1;
            } else if (abs_horizontal > vertical_component) {
                numerator = vertical_component;
                denominator = abs_horizontal;
                base_angle = 0x8000;
                add_table_angle = 0;
            } else {
                return 0x6000;
            }
        } else {
            return 0x4000;
        }
    } else if (vertical_component < 0) {
        int abs_vertical = -vertical_component;

        if (horizontal_component < 0) {
            int abs_horizontal = -horizontal_component;

            if (abs_horizontal > abs_vertical) {
                numerator = abs_vertical;
                denominator = abs_horizontal;
                base_angle = -0x8000;
                add_table_angle = 1;
            } else if (abs_horizontal < abs_vertical) {
                numerator = abs_horizontal;
                denominator = abs_vertical;
                base_angle = -0x4000;
                add_table_angle = 0;
            } else {
                return 0xa000;
            }
        } else if (horizontal_component > 0) {
            if (horizontal_component < abs_vertical) {
                numerator = horizontal_component;
                denominator = abs_vertical;
                base_angle = -0x4000;
                add_table_angle = 1;
            } else if (horizontal_component > abs_vertical) {
                numerator = abs_vertical;
                denominator = horizontal_component;
                base_angle = 0;
                add_table_angle = 0;
            } else {
                return 0xe000;
            }
        } else {
            return 0xc000;
        }
    } else {
        if (horizontal_component >= 0) {
            return 0;
        }
        return 0x8000;
    }

    if (denominator == 0) {
        return 0;
    }
    if (add_table_angle) {
        return (unsigned short)(base_angle + atan_lookup_table[FX_Inv(numerator, denominator) >> 5]);
    }
    return (unsigned short)(base_angle - atan_lookup_table[FX_Inv(numerator, denominator) >> 5]);
}
