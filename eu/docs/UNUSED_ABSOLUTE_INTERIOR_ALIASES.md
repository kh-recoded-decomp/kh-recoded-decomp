# Retiring unused absolute interior aliases

This block removes redundant metadata for eleven existing interior labels. It does not assign new field names, allocate storage or change an instruction. Each numeric label already lies inside one active canonical object, and the current linked graph has no ELF consumer of its absolute export.

The review reads all 12,330 inputs of the final arm9 link, not every object left in the build directory. Every input is present, and all active Ninja dependency records are VALID. The thirty audited aliases each have exactly one size-zero ABS definition in SdkLinkerSymbols.o and no undefined or allocated definition in any active input. Their sixty active source-token references are the existing .global/.equ pairs. There are no active macro-left-hand-side references to rewrite, and the active linker script names none of these aliases. ROOT and US sources remain intact.

## Supported retirements

| Bank | Removed numeric alias | Existing canonical owner | Byte offset | Owner size |
|---|---|---|---|---:|
| main | data_0205291a | sTexStartAddrTable | 0x2 | 96 |
| main | data_0205291c | sTexStartAddrTable | 0x4 | 96 |
| main | data_02053d80 | gSinFx12Table | 0x800 | 8192 |
| main | data_0205fe34 | gSavedCameraState | 0xc | 148 |
| main | data_0205fe8c | gSavedCameraState | 0x64 | 148 |
| ov001 | data_ov001_020a0378 | gStageHeapConfigs | 0x4 | 24 |
| ov001 | data_ov001_020a037c | gStageHeapConfigs | 0x8 | 24 |
| ov015 | data_ov015_0207a313 | gWirelessThemeData | 0x3 | 252 |
| ov101 | data_ov101_020c1ea0 | gSecondaryListSlotTemplates | 0x108 | 480 |
| ov101 | data_ov101_020c2b18 | gListPortraitLayouts | 0xb7c | 14720 |
| ov101 | data_ov101_020c3500 | gListPortraitLayouts | 0x1564 | 14720 |

Each owner is an active ELF OBJECT definition. Its source edge, symbol extent, section alignment and matching delinks range are recorded in the plan. Symbol size and whole-section size are kept separate: gListPortraitLayouts occupies 14,720 bytes inside its 14,724-byte delink section. Interior aliases do not create another allocation. The existing canonical source files keep their paths and declarations.

The patch removes eleven numeric symbol entries and only their twenty-two .global/.equ lines from libs/nitro/data/SdkLinkerSymbols.s. Its other directives, labels and allocated data remain byte-for-byte in the source. The expected object change is the loss of eleven size-zero ABS exports; allocated sections, alignment, all other symbol layouts and relocation values must remain identical. The whole ELF file hash is expected to differ because its symbol table changes.

## Equivalent native pointer representations

Eleven existing load records require an explicit canonical base plus addend. Their source address, kind and complete target-module spelling stay unchanged. Every old and proposed effective target is compared with all four bytes of the original BK9P NDS word, without masking or Thumb-bit normalization.

| Source bank and address | Target bank | Removed target | Canonical target and addend | Original word |
|---|---|---|---|---|
| main:0x02008058 | main | data_0205291a | sTexStartAddrTable + 0x2 | 0x0205291a |
| main:0x0200805c | main | data_0205291c | sTexStartAddrTable + 0x4 | 0x0205291c |
| ov032:0x020bd254 | main | data_02053d80 | gSinFx12Table + 0x800 | 0x02053d80 |
| main:0x02028b04 | main | data_0205fe34 | gSavedCameraState + 0xc | 0x0205fe34 |
| main:0x02028bc0 | main | data_0205fe34 | gSavedCameraState + 0xc | 0x0205fe34 |
| main:0x02028c28 | main | data_0205fe34 | gSavedCameraState + 0xc | 0x0205fe34 |
| main:0x02028b24 | main | data_0205fe8c | gSavedCameraState + 0x64 | 0x0205fe8c |
| main:0x02028dbc | main | data_0205fe8c | gSavedCameraState + 0x64 | 0x0205fe8c |
| ov001:0x02099888 | ov001 | data_ov001_020a0378 | gStageHeapConfigs + 0x4 | 0x020a0378 |
| ov001:0x0209988c | ov001 | data_ov001_020a037c | gStageHeapConfigs + 0x8 | 0x020a037c |
| ov015:0x02076344 | ov015 | data_ov015_0207a313 | gWirelessThemeData + 0x3 | 0x0207a313 |

The unchanged check_linked_target function from tools/rebuild_index.py accepts all twenty-two old/proposed checks. It rejects all twenty-two addend changes of minus or plus one, and all 352 individual bit mutations of the original pointer words. No reconstruction or official verifier is altered. The original per-module exact-address resolver is also used; no nearest-lower-symbol heuristic is introduced.

The historical function index is preserved, including its twenty references that still use numeric alias spellings. A name-only index refresh is not part of this block. The explicit base/addend form belongs to the native configuration and keeps the original resolved pointer value.

## Retained ambiguous references

Nineteen of the thirty aliases remain intact in the recommended patch. They occur in relocation records naming several overlay banks. A physical containing allocation and an equal RAM address do not prove which bank owns a runtime reference. No overlay list is narrowed, no call is reclassified as data and no such reference is converted to a single-bank canonical owner.

| Bank | Retained alias | Canonical physical allocation in that bank |
|---|---|---|
| ov015 | data_ov015_0207f0f9 | gWirelessScanBuffer |
| ov015 | data_ov015_0207f151 | gWirelessScanBuffer |
| ov015 | data_ov015_0207f211 | gWirelessScanBuffer |
| ov015 | data_ov015_0207f235 | gWirelessScanBuffer |
| ov015 | data_ov015_0207f26d | gWirelessScanBuffer |
| ov101 | data_ov101_020c1bc8 | gPrimaryListSlotTemplates |
| ov101 | data_ov101_020c1c60 | gListEntryTextIndices |
| ov101 | data_ov101_020c1e61 | gSecondaryListSlotTemplates |
| ov101 | data_ov101_020c2360 | gListPortraitLayouts |
| ov101 | data_ov101_020c2368 | gListPortraitLayouts |
| ov101 | data_ov101_020c2380 | gListPortraitLayouts |
| ov101 | data_ov101_020c2cc5 | gListPortraitLayouts |
| ov101 | data_ov101_020c2d41 | gListPortraitLayouts |
| ov101 | data_ov101_020c322d | gListPortraitLayouts |
| ov101 | data_ov101_020c3275 | gListPortraitLayouts |
| ov101 | data_ov101_020c4014 | gListPortraitLayouts |
| ov101 | data_ov101_020c4160 | gListPortraitLayouts |
| ov101 | data_ov101_020c4c60 | gListPortraitLayouts |
| ov101 | data_ov101_020c4fe0 | gListPortraitLayouts |

The sixteen additional aliases with active undefined-symbol consumers were excluded from the start and remain unchanged. Same-address references whose module list does not include the alias bank also remain unchanged; for example, overlay 046 references to gCameraManager do not become references to an interior view of overlay 101 data.

## Review artifacts and integration checks

abs_only11_supported_retirement_plan_v1.json locks the nine proposed files by their original and proposed SHA-256 hashes. retire_supported11_abs_aliases.patch and the proposed tree contain only those metadata changes. ACTIVE_GRAPH_ABS_ONLY30_AUDIT_V1.json records all active inputs, source/dependency evidence and canonical ELF definitions. The plan records exact bank-qualified relocation lines, owner extents and original ROM bytes.

This is a read-only research result. No compiler, configure command or official gate was run. Integration must use the locked source versions, retain the ambiguous and consumer-backed aliases, and validate allocated object bytes, alignment, remaining symbol layouts, relocation values and all 108 module hashes. Removing unused metadata is not semantic recovery of an unknown field.

<!-- VALIDATION_PENDING: official integration receipt. -->

## Official integration

All eight affected official function checks pass both before and after the metadata change. All 15 complete C objects preserve allocated bytes/alignment, every symbol layout and all relocation records. The SDK symbol object preserves its allocated sections, ARM ABI metadata, all remaining symbols and relocation information; only the eleven explicitly listed size-zero ABS exports disappear. Its complete ELF hash is consequently expected to change.

A fresh gate passes 108/108 native modules with every module hash unchanged. The function index is byte-identical to its snapshot, preserving the twenty historical alias spellings and their address resolution. Neither the official verifier nor its comparison policy is changed. Twenty real-ELF fixture checks also test the narrow symbol-removal adapter and reject unrelated bytes, symbols, attributes, alignment or relocation changes.

No new assembly is introduced and no instruction is removed. These are metadata normalizations, not new C functions or recovered field meanings. The retained-label ledger now has 81 identities; native DATA allocation bytes and C/library coverage remain unchanged.

## Active owners and checks

- [Existing SDK alias facade](../libs/nitro/data/SdkLinkerSymbols.s).
- [Retained DATA ledger](EU_PENDING_DATA_LABELS.md).

Canonical allocations:

- [gSinFx12Table](../src/data/math/gSinFx12Table.c).
- [gSavedCameraState](../src/data/sdk/gSavedCameraState.c).
- [sTexStartAddrTable](../src/data/sdk/sTexStartAddrTable.c).
- [gStageHeapConfigs](../src/overlays/ov001/data/tables/gStageHeapConfigs.c).
- [gWirelessThemeData](../src/overlays/ov015/data/tables/gWirelessThemeData.c).
- [gListPortraitLayouts](../src/overlays/ov101/data/tables/gListPortraitLayouts.c).
- [gSecondaryListSlotTemplates](../src/overlays/ov101/data/tables/gSecondaryListSlotTemplates.c).

Run these existing official checks from `eu/`:

```sh
python tools/verify_idx.py libs/nitro/gx/calls/GX_BeginLoadTex.c GX_BeginLoadTex
python tools/verify_idx.py src/overlays/ov032/calls/QuatFromRotatedAxisAngle.c QuatFromRotatedAxisAngle --thumb
python tools/verify_idx.py src/calls/BeginOrthographicCamera.c BeginOrthographicCamera
python tools/verify_idx.py src/calls/RestoreSavedCamera.c RestoreSavedCamera
python tools/verify_idx.py src/calls/GetSavedCameraPosition.c GetSavedCameraPosition
python tools/verify_idx.py src/calls/ProjectWorldPositionWithSavedCamera.c ProjectWorldPositionWithSavedCamera
python tools/verify_idx.py src/overlays/ov001/calls/CreateStageManager.c CreateStageManager --thumb
python tools/verify_idx.py src/overlays/ov015/calls/SetupPanelBoard.c SetupPanelBoard
bash tools/gate.sh
```
