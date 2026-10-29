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
or additional masks. There is not yet an executable behavior model for this
callback's filesystem, graphics, upload and scene-handler interactions. The
matching comparison alone does not verify those external implementations.

```sh
python tools/verify_idx.py src/nonmatching/RunSceneLoadStep.c func_ov045_020be730 --thumb --object-symbol func_ov045_020be730
```
