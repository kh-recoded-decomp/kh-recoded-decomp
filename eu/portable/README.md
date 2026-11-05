# Portable library references

This directory contains ordinary C implementations intended as reference code
for the people who later build a host port. It is separate from the byte-exact
DS build: `tools/configure.py` does not discover these files, and they do not
increase matched-C progress. The original verified library implementations
remain the inputs to that build until a C implementation passes both the
per-function byte check and the complete linked-module gate.

## Available code

| Source | Original routines | Native differential verification |
|---|---|---|
| `nitro/matrix.c` | Four identity initializers, two 4x3/4x4 conversions, X/Y 4x3 rotations and the 36-byte clear | 9 routines, 4,636 cases against the ROM instructions and existing independent models |

See [portable MI/MTX contracts](../docs/library/portable_mtx.md) for exact inputs,
outputs, overlap rules, arithmetic and the verification command.

The `KH_` function names distinguish these host interfaces from the DS register
interfaces. A port must adapt declarations and callers together; linking these
files alone does not replace the game's entire NitroSDK dependency.

The portable source has no assembly, register bindings, compiler-specific
arithmetic, hardware addresses or runtime dependencies beyond C99 exact-width
integer types. The optional `KH_PORTABLE_TEST_DLL` definition exports its
functions for the Windows test loader; it does not change their computation.

Start with the [porting handoff guide](../docs/PORTING_GUIDE.md) for the remaining
platform boundaries and the distinction between byte and behavior verification.
