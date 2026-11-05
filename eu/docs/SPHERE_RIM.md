# Sphere sweep against a circular rim

`src/calls/SweepSphereAgainstRim.c` reconstructs the EU ARM function at `0x02047198`
(1480 bytes; formerly `func_02047198`). Its C body comes from the matching candidate supplied by the user
in `func_02047198_MATCH_VERIFICADO.zip`. The production unit uses the existing
`CollisionSphere` definition and the repository's `SolveQuartic` symbol.

## Inputs and outputs

The routine tests the moving sphere center against a circular rim expanded by
the caller's effective sphere radius. Existing capped-cylinder and
cylinder-against-cylinder callers use this operation for their endpoint rims.

| Argument | Meaning |
|---|---|
| `sphere` | Supplies the initial center; this routine never reads its radius field. |
| `direction` | Unit sweep direction supplied by the caller, in world coordinates. |
| `rimCenter` | Center of the circle. |
| `rimRadius` | Circle radius, in fixed-point units. |
| `sphereRadius` | Effective sphere radius, supplied separately by the caller. |
| `rimAxis` | Circle's normal axis; the surrounding geometry code supplies a unit axis. |
| `candidateDistances` | Caller-owned writable buffer of at least 12 `fx32` entries. |
| `outNormal` | Receives the contact normal on a hit; untouched on a miss. |

The result is the minimum of all 12 solver entries. `0x7fffffff` means no hit.
This routine does not discard negative distances or restrict them to a movement
interval; preserve that distinction when adapting the surrounding sweep code.
The existing callers use separate stack buffers for roots and the normal.
No allocation or retained pointer is introduced here.

The cylinder-against-cylinder caller can pass an endpoint vector as the first
argument. Only the 12-byte center prefix is consumed. A host port should choose
one consistent center-only or sphere-based API and adapt all callers; the
shared address representation in the DS code does not make different C pointer
types interchangeable.

## Computation

The initial center is translated relative to the rim center. A basis is built
from `rimAxis`, and both that offset and the sweep direction are transformed
into it. The polynomial then uses the cyclic component order `(y, z, x)`.
Component squares and component products form the cubic, quadratic, linear and
constant coefficients passed to the monic quartic solver.

`SolveQuartic` uses Ferrari's method and writes three groups of four candidate
distances. Its missing-root sentinel is the same `0x7fffffff` value used here.
The minimum-selection loop reads the complete buffer; it does not stop at a
missing entry.

On a hit, the function computes the position along the sweep relative to the
rim center, obtains its radial direction through `GetUnitRejectionFromAxis`,
and subtracts the rim radius along that direction. If this last vector is
exactly zero in all three components, the original hit position supplies the
normal instead. Both paths use `NormalizeIfShort`; replacing that helper with a
generic normalization routine would change its small-vector behavior.

## Fixed-point arithmetic and matching

`fx32` is a signed 32-bit value with 12 fractional bits; `0x1000` represents one.
`fx64` and `s64` in this unit are signed 64-bit integers, also shifted by 12 for
these products. They do not imply a different fixed-point scale.

The two multiplication helpers have different contracts:

```c
FX_Mul(a, b)            /* (fx32)(((s64)a * b + 0x800) >> 12) */
MultiplyUnrounded(a, b) /*         ((s64)a * b         ) >> 12  */
```

Each product is shifted individually before summation. The unrounded helper
keeps all 64 shifted result bits. Narrowing its result to `fx32`, combining
products before shifting, or introducing a shared rounding bias changes the
coefficient arithmetic.

The constant coefficient subtracts `offsetSquares.x`, then `.y`, then `.z`
from one mutable `remaining` value. The three resulting products are retained
as separate `s64` terms. Together with the declaration and operand order in the
accepted source, this reproduces the original instruction schedule, register
allocation and private stack spills. These locals represent arithmetic values;
there are no artificial parameters, volatile spills or assembly in this unit.

For byte matching, preserve that expression grouping and source order. A host
port can give these operations a different implementation, but must explicitly
preserve arithmetic right shifts, word truncation and target overflow behavior.
Ordinary signed C overflow is undefined, and right-shifting a negative signed
value is implementation-defined in C99. Matching this compiler's ARM output
does not establish portable behavior under another compiler's defaults.

## Calling convention and dependencies

The public function uses r0-r3 for `sphere`, `direction`, `rimCenter` and
`rimRadius`, followed by the four remaining arguments on the caller's stack.
The solver's recovered signature is:

```c
void SolveQuartic(fx32 cubic, fx32 quadratic, fx32 linear,
                  s64 constant, fx32 *roots);
```

In this CodeWarrior ARM interface, the constant's low word occupies r3, its
high word occupies the first stack word, and the roots pointer occupies the
next stack word. Do not infer an extra parameter from that split 64-bit value.
Several vector helpers return structures through CodeWarrior's hidden result
pointer. A port should use consistent declarations for their definitions and
callers, including any explicit-output-pointer adapters.

The routine performs no direct hardware access. Its vector, normalization and
quartic-solver dependencies still need their own host implementations; this
function alone is not a complete collision-system port.

## Verification

The production source selects `dsi/1.1` in `config/arm9/file_compilers.json`:
Metrowerks ARM 4.0 build 1018, ARM mode, C99, with the normal project flags.
From `eu/`, reproduce the official function check and linked-module gate:

```sh
python tools/verify_idx.py src/calls/SweepSphereAgainstRim.c SweepSphereAgainstRim
bash tools/gate.sh
```

Acceptance requires `MATCH` for all 1480 bytes and 15 references, plus all 108
linked modules equal to the ROM. The comparison must use this repository's EU
ROM-derived index, rather than relying on the supplied package's own target or
verification reports.
