# Portable MI/MTX reference implementations

`portable/nitro/matrix.c` supplies nine C99 equivalents for the matrix helpers
documented in [sdk_mtx.md](sdk_mtx.md). Their purpose is to give a future port
readable implementations and executable behavior contracts. They are not new
byte-exact C matches. The existing verified ARM/Thumb implementations remain
unchanged in the production build and in its separate library accounting.

## Mapping and ownership

| Original entry | Portable entry | Destination |
|---|---|---|
| `MTX_Identity22_` | `KH_MTX_Identity22` | 16 bytes: 2x2 identity |
| `MTX_Identity33_` | `KH_MTX_Identity33` | 36 bytes: 3x3 identity |
| `MTX_Identity43_` | `KH_MTX_Identity43` | 48 bytes: 3x3 identity and zero translation |
| `MTX_Identity44_` | `KH_MTX_Identity44` | 64 bytes: 4x4 identity |
| `MTX_Copy43To44_` | `KH_MTX_Copy43To44` | 64 bytes: expand the four 3-element rows |
| `MTX_Copy44To43_` | `KH_MTX_Copy44To43` | 48 bytes: discard the fourth column |
| `MTX_RotX43_` | `KH_MTX_RotX43` | 48 bytes: X-axis rotation and zero translation |
| `MTX_RotY43_` | `KH_MTX_RotY43` | 48 bytes: Y-axis rotation and zero translation |
| `MI_Zero36B` | `KH_MI_Zero36B` | Nine zero words |

The caller owns all buffers. Each destination must be writable, word-aligned
and large enough for the indicated output. Sources must be readable and
word-aligned. No pointer is retained, allocation performed or global state
changed. Treat these as normal-memory operations, not atomic operations or
memory-mapped I/O.

The two conversion routines take source first, destination second. Expansion
requires disjoint buffers; in-place expansion would overwrite unread rows.
Compaction also supports equal source and destination addresses. It reads each
complete row before writing that row's first three coefficients, ignores the
input fourth column without validating it, and leaves bytes after the 48-byte
output unchanged. Other partial overlaps are outside the supported contract.
Character accesses inside the conversions avoid aliasing incompatible matrix
structure types when the bases are equal.

## Coefficients and layout

The header's matrix types contain only `int32_t` row-major coefficients. Their
checked sizes are 16, 36, 48 and 64 bytes. These types contain no pointers and
do not require a 32-bit host address space. The implementation requires 8-bit
bytes and the exact-width C99 integer types supplied by `<stdint.h>`.

Coefficients use the SDK's signed 20.12 scale: `0x1000` represents one. Rotation
arguments are already the fixed-point sine and cosine, not an angle. They are
stored as supplied, with no normalization or trigonometry. The negation helper
handles `INT32_MIN` explicitly, reproducing ARM's wrapped result without signed
C overflow. Identity and clear operations do no arithmetic on input values.

The four-row, three-column layout places translation in the last row. When
expanded to 4x4, the appended column is `(0, 0, 0, 0x1000)`. Vectors use the
original row-vector convention; a renderer using column vectors needs an
explicit convention adapter.

The portable functions use host-native coefficient representations. Loading
little-endian ROM data on a big-endian host requires a serialization adapter.
They do not reproduce incidental ARM scratch-register values, condition flags,
instruction order, ITCM placement or the aligned-down behavior of invalid
unaligned pointers.

## Verification

From the shared repository root, with the local EU ROM extraction and Python
dependencies already used by the SDK verifier:

```sh
python tools/sdklib/test_portable_mtx.py
```

The tool compiles the actual checked-in C with a native free compiler at `-O2`
and with strict warnings, loads that library, and reuses the existing
`sdk_mtx.py` cases and ARM interpreter. Every case must satisfy both the
independent model and the complete 512-byte output window of the ROM routine.
The window includes guards and any source bytes outside the destination.
It checks 4,636 cases: 302 each for the four identities and clear, 297 expansion
cases, 343 compaction cases, and 1,243 cases for each rotation. Compaction
includes equal-base buffers; rotations include all pairs of the recorded edge
values, including `INT32_MIN`, plus randomized coefficients.

Use `--cc /path/to/clang` or `--cc /path/to/gcc` to select a native compiler.
Windows uses Clang and LLD to build a test DLL without the CRT; Linux can use
GCC or Clang. `--report path.json` saves source, header, compiler and native
library hashes, the command and case counts. Raw byte comparison currently
requires a little-endian test host. This is a functional differential test for
the documented inputs, not a timing test or proof over every possible memory
address. It does not issue new library receipts or change C progress.

The byte-exact gate remains `bash tools/gate.sh` from `eu/`. Its inputs and the
three recently completed EU function matches are unchanged by this portable
block.

## Byte-matching investigation

Initial GCC 12.2.1 and Clang 22.1.3 controls for the 36-byte clear, 2x2 identity
and X rotation did not reproduce the original block-store sequences. Bounded
scratch-register and cursor controls also differed. The closest 2x2 identity
under the existing ARMCC backend differed by `mov r3, r1` versus the original
`mov r3, #0`; both followed an initialization of r1 to zero, but their bytes
still differ. That candidate was not accepted as a match. No object bytes,
compiler binary, signature or production verification rule was changed.

This closes those specific controls, not every possible future C spelling.
If another compiler/source form matches, it can replace the corresponding
library entry through the normal byte and full-module gates. The portable
implementation and its differential cases remain useful independently.
