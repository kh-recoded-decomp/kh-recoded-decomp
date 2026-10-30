# Carousel model initialization

`LoadCarouselModels` (ov087, `0x020c6ad0`) is matching C in
`src/overlays/ov087/calls/LoadCarouselModels.c`. `InitPanelScene_020c713c`
passes the scene and either its locked resource ID or `-1`.

The definition declares a third parameter, `entry`, that neither call passes:
at the first call r2 still holds the entry count the caller has just stored, at
the second whatever an earlier call left there. It is only the loop counter and
is set to zero before use. The parameter stays because the original register
assignment requires it. mwcc numbers an incoming parameter before every local and
colours higher numbers first, so the counter is coloured last and lands in r8,
after the info pointer (r7) and the entry offset (r6), as in the ROM. Declared as
a local, the counter is numbered between those two values and they trade r6 and
r7 (ten bytes); no local spelling tried (declaration order, block scope, a
separate counter, a slot pointer, an early return, the permuter) changes that.
See "Parameters the callers do not pass" in
[PROGRESS_POLICY.md](PROGRESS_POLICY.md). A port should call it with two
arguments.

## Recovered layout and behavior

`CarouselModels.h` records only the spans needed by this function:

| Scene offset | Field |
|---|---|
| `0x08` | Signed entry count. |
| `0x14` | Center model span. |
| `0x118` | Eight entries, each an ID followed by a model; stride `0x108`. |
| `0x958` | First 14 projection words. |

Within each model span, scale is at `0xb0` and the animation table is at `0xd8`.
These are ARM32 views. The model span is `0x104` bytes and the scene prefix ends
at `0x990`; neither is a claim about a complete engine allocation. In particular,
other scene routines use a camera span of `0x218` bytes starting at `0x958`.
Do not allocate a complete scene using the prefix's size.

The function always initializes the center model, even with a zero or negative
entry count. It sets projection word 10 to `0x1c000`, loads resource 4 from bank 2,
initializes the center with resource 5, selects index 0 on tracks 0 through 4,
sets uniform fixed-point scale `0x2000`, and releases the loaded info buffer.

For each entry it normally uses the loop index as the resource ID. If the locked
ID is not `-1`, the last entry uses that ID instead. It does not sort entries,
remove duplicates or validate bounds. Positive counts must be at most eight and
selected IDs must be in `0..7`; callers must uphold these requirements.

Two original eight-word tables select the loaded info and record resources:

| Resource ID | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 |
|---|---|---|---|---|---|---|---|---|
| Info resource | 8 | 14 | 2 | 10 | 0 | 12 | 12 | 6 |
| Record resource | 9 | 15 | 3 | 11 | 1 | 13 | 13 | 7 |

Each entry follows the same load, initialize, five-track bind, scale and free
sequence as the center, with scale `0x800`. The info pointer is passed unchanged
to initialization and then freed after binding and scale writes. This describes
the caller's lifetime; it does not prove how the initializer copies or retains
the buffer's contents. A port must preserve that engine-side contract too.

`BuildSlotImageParams` produces a packed resource locator, not a path string.
The effective inputs of loader `func_0202c4a0` are the locator and kind `14`.
The shared US source still declares four words: its third is unused and its
fourth reaches the unused fourth parameter of `FileLoader_LoadAlloc`. The EU
source declares the effective two inputs. Before compiling these
services together in a portable C program, reconcile their legacy declarations
and definitions; do not carry the placeholder register parameters into a port.

The function reloads `entryCount` after external calls. A port must not silently
cache it for the entire loop if its callbacks can modify the scene.

## Executable checks and limits

`python tools/test_carousel_models.py -v`, from `eu/`, runs 93 scenarios on each
of the original ARM function, the matching CodeWarrior build, GCC 12.2.1 and Clang
22.1.3 builds. It checks zero/negative counts, counts 1 through 8, all valid
locked IDs plus `-1`, and three callback-driven count changes. It compares the
entire scene buffer and ordered call arguments, checks all five tracks and
scale-before-free ordering, poisons caller-saved registers, and verifies the
callee-saved registers and stack are restored. The resource tables are read
from the original extracted EU overlay and checked against the recovered IDs.

The projection helper executes its original instructions. Resource packing,
allocation, model initialization, animation binding and free are explicit
modeled engine boundaries. These tests validate the caller; they do not execute
the filesystem, renderer, heap or animation system. They supplement the byte
verifier and are not a library verification receipt.

The CodeWarrior `dsi/1.3p1` build is the original's 468 bytes with the same 15
relocation offsets and targets; the GCC and Clang builds are separate behavior
builds. Verify the match with:

```sh
python tools/verify_idx.py src/overlays/ov087/calls/LoadCarouselModels.c LoadCarouselModels
```
