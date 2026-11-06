# Refreshing native relocation metadata

Function bytes come from the original EU modules. Compiler objects provide the
candidate to compare; they do not define the target instructions or the native
relocation map. The existing index builder now supports an explicit refresh for
reviewed native metadata changes.

## Corrected records

| Function | Native metadata correction |
|---|---|
| SpawnStageEntryActor | Four callback-pointer loads already present as native words and symbolic C references. |
| ModelRenderCallbackKindC | One Thumb BLX to ARM NNS_G3dGetCurrentMtx at 02019d14. |
| RefreshStatusMenuData | Two intraprocedural BL records removed from external relocation expectations. |
| HandleResultsInput | One intraprocedural BL record removed. |
| RefreshResultsScreen | Eight intraprocedural BL records removed. |
| DrawMatrixCellGlyph | One intraprocedural BL record removed. |
| DrawMatrixMenu | Three intraprocedural BL records removed. |
| UpdateMatrixEventAnimation | Two intraprocedural BL records removed. |

The seventeen internal BL instructions remain verbatim in the index. Their 68
bytes are now compared directly by the unchanged verifier. Local labels remain
in symbol configuration. Five genuine external references are added from the
native instructions/pointer words and their bank-qualified targets.

The separate FinishAreaSceneLoad descriptor load is bound to resident 035's
existing gBarGaugeClassDescriptor; its parent loads 040 before the child uses
that descriptor. The native pointer word stays 020bc4e8 and no storage changes.

## Explicit builder mode

Run from `eu/` after the reviewed configuration changes:

```sh
python tools/rebuild_index.py --refresh-native-relocs SpawnStageEntryActor ModelRenderCallbackKindC RefreshStatusMenuData HandleResultsInput RefreshResultsScreen DrawMatrixCellGlyph DrawMatrixMenu UpdateMatrixEventAnimation
python tools/rebuild_index.py --write --refresh-native-relocs SpawnStageEntryActor ModelRenderCallbackKindC RefreshStatusMenuData HandleResultsInput RefreshResultsScreen DrawMatrixCellGlyph DrawMatrixMenu UpdateMatrixEventAnimation
```

The first command is a dry run. The second writes only the selected entries.
Both reconstruct from extracted ROM and configuration; neither accepts candidate
objects, replacement JSON or zeroed instruction words as target data.

Every selected entry must retain exact unmasked hex, size, ARM/Thumb mode and
module. Added references must pass the builder's existing native opcode/target
checks. A removed reference must be an actual Thumb BL to a current Thumb label
strictly inside that same function and bank; real function entries and unexplained
external/data removals are rejected. Common-offset historical spellings and all
other fields are preserved. Default merge/name-refresh behavior and the original
five-disagreement guard are unchanged.

## Validation

All 37 index-builder regression tests pass, including rejected byte/opcode/target,
mode, bank, extent and selection mutations, dry-run non-writing, preservation of
nonselected entries and the original five-versus-six disagreement threshold.
The actual dry run preserves both the index contents and its modification time.
The actual write changes only the eight selected relocation lists: +5/-17.

All eight freshly compiled official function checks pass. Eight production
objects retain their complete allocated bytes/alignment, symbol layouts and
relocation records. A fresh linked gate passes all 108 modules with identical
hashes; every indexed native byte, size and mode remains unchanged.

Three pre-existing conservative builder discrepancies retain more detailed
cached relocation maps than native configuration: EntryActionMagic,
EntryActionFlurry and SpawnPlayerStageEntryActor. Their complete unmasked bytes,
sizes and modes agree with ROM. Those entries remain unchanged and their three
additional fresh official function checks pass. They are separate from this
explicit eight-function refresh.

```sh
python -m unittest discover -s tools -p test_rebuild_index.py
python tools/audit_progress.py --check-receipts
bash tools/gate.sh
```
