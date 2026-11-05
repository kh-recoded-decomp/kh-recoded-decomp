#include "matrix.h"

#define FX_ONE INT32_C(0x1000)

/* ARM NEG wraps INT32_MIN back to itself. Avoid signed C overflow. */
static int32_t NegateCoefficient(int32_t value)
{
    return value == INT32_MIN ? INT32_MIN : -value;
}

/* Character accesses permit equal source/destination bases in the compacting
 * conversion without aliasing two incompatible structure types. Copy the host
 * representation, so these helpers do not assume the host's byte order.
 */
static int32_t ReadCoefficient(const unsigned char *source)
{
    int32_t value;
    unsigned char *representation = (unsigned char *)&value;
    unsigned byte;
    for (byte = 0; byte < sizeof(value); ++byte)
        representation[byte] = source[byte];
    return value;
}

static void WriteCoefficient(unsigned char *destination, int32_t value)
{
    const unsigned char *representation = (const unsigned char *)&value;
    unsigned byte;
    for (byte = 0; byte < sizeof(value); ++byte)
        destination[byte] = representation[byte];
}

void KH_MTX_Identity22(KHMatrix22 *destination)
{
    unsigned row, column;
    for (row = 0; row < 2; ++row)
        for (column = 0; column < 2; ++column)
            destination->row[row][column] = row == column ? FX_ONE : 0;
}

void KH_MTX_Identity33(KHMatrix33 *destination)
{
    unsigned row, column;
    for (row = 0; row < 3; ++row)
        for (column = 0; column < 3; ++column)
            destination->row[row][column] = row == column ? FX_ONE : 0;
}

void KH_MTX_Identity43(KHMatrix43 *destination)
{
    unsigned row, column;
    for (row = 0; row < 4; ++row)
        for (column = 0; column < 3; ++column)
            destination->row[row][column] = row == column ? FX_ONE : 0;
}

void KH_MTX_Identity44(KHMatrix44 *destination)
{
    unsigned row, column;
    for (row = 0; row < 4; ++row)
        for (column = 0; column < 4; ++column)
            destination->row[row][column] = row == column ? FX_ONE : 0;
}

void KH_MTX_Copy43To44(const KHMatrix43 *source, KHMatrix44 *destination)
{
    const unsigned char *input = (const unsigned char *)source;
    unsigned char *output = (unsigned char *)destination;
    unsigned row;
    for (row = 0; row < 4; ++row) {
        /* Read the complete source row before writing its expanded row. */
        int32_t first = ReadCoefficient(input + 12 * row);
        int32_t second = ReadCoefficient(input + 12 * row + 4);
        int32_t third = ReadCoefficient(input + 12 * row + 8);
        WriteCoefficient(output + 16 * row, first);
        WriteCoefficient(output + 16 * row + 4, second);
        WriteCoefficient(output + 16 * row + 8, third);
        WriteCoefficient(output + 16 * row + 12, row == 3 ? FX_ONE : 0);
    }
}

void KH_MTX_Copy44To43(const KHMatrix44 *source, KHMatrix43 *destination)
{
    const unsigned char *input = (const unsigned char *)source;
    unsigned char *output = (unsigned char *)destination;
    unsigned row;
    for (row = 0; row < 4; ++row) {
        int32_t first = ReadCoefficient(input + 16 * row);
        int32_t second = ReadCoefficient(input + 16 * row + 4);
        int32_t third = ReadCoefficient(input + 16 * row + 8);
        WriteCoefficient(output + 12 * row, first);
        WriteCoefficient(output + 12 * row + 4, second);
        WriteCoefficient(output + 12 * row + 8, third);
    }
}

void KH_MTX_RotX43(KHMatrix43 *destination, int32_t sine, int32_t cosine)
{
    destination->row[0][0] = FX_ONE;
    destination->row[0][1] = 0;
    destination->row[0][2] = 0;
    destination->row[1][0] = 0;
    destination->row[1][1] = cosine;
    destination->row[1][2] = sine;
    destination->row[2][0] = 0;
    destination->row[2][1] = NegateCoefficient(sine);
    destination->row[2][2] = cosine;
    destination->row[3][0] = 0;
    destination->row[3][1] = 0;
    destination->row[3][2] = 0;
}

void KH_MTX_RotY43(KHMatrix43 *destination, int32_t sine, int32_t cosine)
{
    destination->row[0][0] = cosine;
    destination->row[0][1] = 0;
    destination->row[0][2] = NegateCoefficient(sine);
    destination->row[1][0] = 0;
    destination->row[1][1] = FX_ONE;
    destination->row[1][2] = 0;
    destination->row[2][0] = sine;
    destination->row[2][1] = 0;
    destination->row[2][2] = cosine;
    destination->row[3][0] = 0;
    destination->row[3][1] = 0;
    destination->row[3][2] = 0;
}

void KH_MI_Zero36B(uint32_t *destination)
{
    unsigned word;
    for (word = 0; word < 9; ++word)
        destination[word] = 0;
}
