# Joint transform and texture identity helpers

These five names come from native result layouts, GX command payloads and the
actual dispatch tables. Existing EU NNS types are reused. No algorithm, hook
order, command count or skipped write is changed.

| Previous name | Current name | Bytes, ARM |
|---|---|---:|
| `func_01ffa5b0` | `EmitBasicJointTransform` | 116 |
| `func_01ffa624` | `DecodeBasicJointScale` | 60 |
| `func_01ffe394` | `HandleSbcMatrixRestore` | 68 |
| `func_01ffacdc` | `SetMode2TextureIdentityTerms` | 36 |
| `func_01ffae58` | `SetAlternateTextureIdentityTerms` | 36 |

## Joint result layout and sends

`NNSG3dJntAnmResult` in `libs/nns/g3d/g3d_nsbca_internal.h` supplies the
established native fields: flags at 0, scale at +4, scaleEx0 at +0x10,
scaleEx1 at +0x1c, rotation matrix at +0x28 and translation at +0x4c.
`gJointAnimationResultDispatch` registers the basic sender beside the existing
alternative sender. These are rendering results, not generic integer blocks.

`EmitBasicJointTransform` branches on the identity flags:

| Translation-zero bit 4 | Rotation-zero bit 2 | Command sent |
|---|---|---|
| Clear | Clear | 0x19, twelve words starting at rotation: contiguous rotation plus translation (4x3 multiply). |
| Clear | Set | 0x1c, three translation words. |
| Set | Clear | 0x1a, nine rotation words (3x3 multiply). |
| Set | Set | No rotation/translation command. |

After that stage it **re-reads** the result flags. Unless scale-one bit 1 is
set, it sends 0x1b with the three scale words. The result pointer remains borrowed
through these calls. A port must retain the late flag read, payload order and
word counts; combining the calls or filling omitted identity data is a separate
behavior change. The twelve-word native payload spans the adjacent rotation
and translation fields; a renderer adapter should serialize that layout
explicitly instead of depending on host struct packing.

`DecodeBasicJointScale` has the existing four-slot joint-scale hook signature:
result, source scale words, unused resource-byte pointer, and SRT flags. When
SRT bit 4 is set it ORs scale-one into the result and leaves the three scale
words untouched. Otherwise it copies exactly three source words. It always ORs
0x18 into the result flags, marking the two extended-scale terms as identity,
and does not populate their arrays. It does not clear pre-existing result flags.
The unused third input belongs to the shared hook ABI; no gameplay meaning is
assigned to it.

## SBC matrix restore

`HandleSbcMatrixRestore` takes the established `NNSG3dRS` state. The command
cursor `c` is its first word and `flag` is at +8. This corrects the legacy
`text_cursor` interpretation without introducing another state structure.

It sends opcode 0x14 (`MTX_RESTORE`) with cursor byte 1 only when flag 0x200 is
clear, flag 1 is set and flag 0x100 is clear. It advances the cursor by two bytes
**even when the command is suppressed**. The command-handler table initialized
by `InitSbcHandlersAndFastDma` registers it at index 3. No command-length or
matrix-index validation is added, and 0x200 retains its numeric meaning here.

## Partial texture identity and hook ABI

The mode-2 and alternate texture-builder tables each register their own identity
entry at index 7, selected by the scale-one/rotation-zero/translation-zero flags.
The separate entrypoints are preserved even though their bodies are identical.
The table and definitions now share the actual two-argument hook shape:
`(u32 *matrix, const struct TexMtxState *state)`; the identity entry does not read
the second argument, and no cast to an incompatible one-argument function is
needed.

Each function writes only matrix word indices 0 and 5 to 0x1000, and indices
1, 4, 12 and 13 to zero. Every other word retains its previous value. This is
six 2D affine terms in native four-word row storage, **not** a complete 4x4
identity initializer or a matrix clear. The alternate table's authoring-tool
origin is not established; no Maya/3ds Max name is invented from the matching
body.

## Verification

From `eu/`:

```sh
python tools/verify_idx.py src/calls/EmitBasicJointTransform.c EmitBasicJointTransform
python tools/verify_idx.py src/calls/DecodeBasicJointScale.c DecodeBasicJointScale
python tools/verify_idx.py src/calls/HandleSbcMatrixRestore.c HandleSbcMatrixRestore
python tools/verify_idx.py src/calls/SetMode2TextureIdentityTerms.c SetMode2TextureIdentityTerms
python tools/verify_idx.py src/calls/SetAlternateTextureIdentityTerms.c SetAlternateTextureIdentityTerms
bash tools/gate.sh
```

The official verifier checks each function against the ROM-derived index.
Integration compares affected production texts, resolved relocation targets/types
and addends to the saved baseline and requires unchanged hashes across all
108 linked modules. These checks prove retained bytes; the contracts above are
supported separately by layouts, dispatch registrations, opcode definitions and
actual field accesses.
