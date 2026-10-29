# Pending scene-load callback

`func_ov045_020be730` is reconstructed in
`src/nonmatching/RunSceneLoadStep.c`. It remains outside the linked EU build and
matching-C coverage. Its work is held in the global scene pointer at
`data_ov045_020c08a0`; it does not consume an incoming palette-size value.

The incoming shared reconstruction declared `plttSize` as an argument to obtain
the original stack allocation, despite assigning it from `GetPaletteBytes`
before any use. EU keeps this quantity local and leaves the callback pending.
The shared US source is preserved. Reproducing bytes with a scratch parameter
does not establish that parameter as part of the recovered interface.

## State and backend boundaries

The callback advances a load state, returning a next scene handler when ready
or `NULL` while work remains. The handler representation is target-specific;
a port must retain actual function pointers and reconcile the scene dispatcher
types rather than storing host addresses in 32-bit integer fields.

| State | Main operation |
|---|---|
| `0` | Wait for the first file, open the mode-dependent message container. |
| `1` | Wait for that container; choose the main texture route, result route, or an immediate next handler. |
| `2` | Wait for texture data, configure backgrounds and initialize background records. |
| `3` | Initialize the text layer and twelve icon records. |
| `4` | Acquire records and advance the timed preparation. |
| `5` | Query texture sizes, allocate resource keys and advance texture/palette uploads. |
| `6` | Resolve texture/palette dictionary entries, derive image parameters and release the loaded file. |
| `7` | Complete the wait and return the result-tally handler. |
| `8` | Wait for result data and configure the result backgrounds. |
| `9` | Initialize result text, update applicable unlock records and return the name-reveal handler. |

The source retains volatile DS background/display-register accesses and the
texture/palette VRAM calls. These require a platform backend in a port. File
readiness checks, the upload substate and frame waits must retain their ordering;
replacing this callback with a synchronous bulk load would change its behavior.

The recovered work structure is a target layout view. The names do not establish
a complete allocation API or prove ownership for every pointer. In particular,
the loaded texture file is released after dictionary values and resource keys
have been consumed; a port must check the renderer's resource retention too.

## Exact comparison and remaining work

With CodeWarrior `dsi/1.3p1`, the zero-input callback emits 2,148 bytes and the
same 68 relocation offsets and targets as the original Thumb code. Four ordinary
instruction bytes differ, swapping the private palette-size and texture-key
stack slots in the resource-allocation block:

| Instruction offset | ROM stack offset | Current C stack offset |
|---|---:|---:|
| `0x394` | `0x08` | `0x0c` |
| `0x3aa` | `0x0c` | `0x08` |
| `0x3c2` | `0x08` | `0x0c` |
| `0x3de` | `0x0c` | `0x08` |

The ordinary verifier reports this mismatch; these offsets are not exceptions
or additional masks. The texture-state replay below covers state `5`; the
callback's other states and the external implementations still need separate
behavior verification. This work grants no matching-C or verified-library credit.

```sh
python tools/verify_idx.py src/nonmatching/RunSceneLoadStep.c func_ov045_020be730 --thumb --object-symbol func_ov045_020be730
```

## Executable texture-state contract

Run `python tools/test_scene_texture_load.py -v` from `eu/`. It compares 720
scenarios on each of ROM, CodeWarrior dsi/1.3p1, GCC 12.2.Rel1 and Clang 22.1.3
instruction images. These cover empty/nonempty resources, 1 KiB chunk boundaries,
allocator failures, the palette-allocation flag and upload substates
`0..6`, `100` and `99`. Incoming r0-r3 values vary; none is an input to this
zero-argument callback. The test also verifies that the relocated CodeWarrior
image differs from ROM at exactly the four stack bytes listed above, including
all resolved calls and literal-pool addresses in that comparison.

The size-query and key-assignment SDK helpers execute their actual ROM code.
So does the 66-byte `StepTextureUpload`: each invocation transfers at most
`0x400` bytes, advances the source/destination, subtracts the transferred amount
and reports whether the remainder reached zero. Tests compare complete scene
and texture buffers, ordered calls and transferred bytes, callee-saved registers,
SP and the callback's zero return value. They check ARM/Thumb state at backend
boundaries as well as arguments.

The recovered upload view starts at scene `+0x1a08`:

| Relative offset | Field |
|---|---|
| `0x0c` | Texture resource pointer. |
| `0x10` | Remaining transfer bytes. |
| `0x14` | Destination byte offset in VRAM. |
| `0x18` | Source pointer. |
| `0x1c` | Palette-transfer flag. |
| `0x20` | 16-bit upload substate. |
| `0x24` | Loaded file pointer. |

Resource sizes are stored in units of eight bytes. Allocation requests occur
in normal-texture, compressed-texture, palette order and are skipped for zero
sizes. The palette allocator receives `tex4x4Info.flag & 0x8000`, as in the
original instructions, without reducing it to `1`. Zero normal/compressed keys
leave the old keys unchanged in `NNS_G3dTexSetTexKey`; the palette key setter
stores zero too. The callback continues after a zero allocator result. This
describes observed behavior, not a claim that allocation failure is recoverable.

Normal texture completion sets its loaded flag. Compressed data and its palette
index data use separate transfers; completing the index transfer sets the
compressed loaded flag. Palette loading waits for VBlank, begins the load,
transfers the entire palette, ends the load and waits for VBlank again, even
for a zero-byte palette. It sets the palette loaded flag and upload substate
`100`; the enclosing callback then clears its timer and advances to state `6`.

One boundary remains to investigate in the surrounding engine: when upload
substate `2` prepares nonempty compressed texture data, this callback leaves the
substate at `2`; it does not assign `3` in that branch. The tests preserve that
ROM behavior. Tests starting at substates `3` and `4` check their local handling
without claiming to prove how those substates become reachable. Do not add an
unverified transition while porting this routine.

Container lookup, the two indirect allocators, VBlank and graphics transfers
are modeled boundaries; filesystem parsing, actual allocation, DMA/VRAM and
display behavior are outside this test. GCC/Clang arithmetic helpers used only
by other callback states are explicit trap boundaries and must never execute
in these scenarios. This is not a full replay of the scene state machine.
Clang currently diagnoses a redundant null test retained from the inlined
dictionary accessor in state `6`; that state is outside this replay and the
guard still affects CodeWarrior's matching output.

The temporary replay linker marks both ARM and Thumb call targets as functions.
GNU ld requires that metadata to generate interworking calls correctly; plain
absolute data symbols are insufficient. Its images remain test-only and neither
compiler objects nor matching reference bytes are modified.
