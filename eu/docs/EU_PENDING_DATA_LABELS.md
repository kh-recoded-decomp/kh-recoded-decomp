# Retained EU DATA labels: ownership and missing proof

The DATA naming review covers 941 distinct module/address identities: 179 in
overlays 000-020, 370 in main/ITCM/DTCM and overlays 021-040, and 392 in overlays
041-104. It has 835 supported numeric-label assignments and the 106
retained identities recorded below. All 106 have been reviewed; retention is
an explicit evidence or alias/configuration boundary.

All 835 supported numeric-label assignments in this review are now integrated,
leaving exactly 106 retained numeric DATA labels. The current configuration's
complete retained-label set was checked against all 106 records below.
Evidence was originally collected at commit
`1ebd8885dfa0ba01df24ba0540a980339abbfa6b`; source paths and the named logical
owners have been rechecked at publication. No semantic name is invented for
any retained label in this ledger.

| Review cohort | Reviewed identities | Supported naming | Retained |
|---|---:|---:|---:|
| Overlays 000-020 | 179 | 151 | 28 |
| Main/ITCM/DTCM and overlays 021-040 | 370 | 317 | 53 |
| Overlays 041-104 | 392 | 367 | 25 |
| Total | 941 | 835 | 106 |

## Reading the records

An identity is always module plus address: overlays with the same RAM address
are separate records. Physical definitions, containing objects and logical
owners are different extents. Ranges are half-open. An interior label has no
new allocation merely because it appears in symbols.txt. A source file's
configured range is not automatically a single object or a structure extent.
Logical owners spanning several native fragments are identified explicitly.

An unknown field is not unused data. A zero BSS definition is storage evidence,
not cartridge-stored zero bytes. Missing direct references do not exclude
computed accesses, decoded pointers or runtime copies. Pointer-shaped values,
neighboring names and matching addresses in another loaded bank are not enough
to choose an owner. In particular, a foreign Thumb callback does not identify
an odd-address zero DATA object in a different overlay.

The function backlog remains separate in [field functions](EU_PENDING_FIELD_FUNCTIONS.md),
[engine/scene functions](EU_PENDING_ENGINE_SCENE_FUNCTIONS.md) and
[callback functions](EU_PENDING_CALLBACK_FUNCTIONS.md). This DATA ledger does
not rename functions or replace those function-review ledgers.

## Why labels remain numeric

| Retention class | Identities |
|---|---:|
| Interior/member metadata alias; no separate allocation | 57 |
| Existing canonical identity; alias merge remains | 4 |
| Storage exists; operational role unproved | 18 |
| Stat-field meaning unproved | 2 |
| Physical objects have overlapping execution views | 5 |
| Physical fragment of a proved logical owner | 4 |
| Address passed in an argument the callee does not read | 1 |
| Foreign-bank binding remains unresolved | 12 |
| Own storage opaque; observed reference selects foreign code | 3 |

The first two classes contain 61 metadata aliases or already canonical
identities; these are not 61 unexplained extra allocations. Four additional
labels are physical fragments of the proved wireless data-sharing state.
Foreign-bank rows retain their own physical storage and the unresolved binding
instead of borrowing the other bank's meaning. Every row below states the
remaining proof needed; there is no count-driven requirement to rename it.

## Identity index

| Module/address | Retained label | Retention class |
|---|---|---|
| [main:0205291a](#main0205291a) | `data_0205291a` | Interior/member metadata alias; no separate allocation |
| [main:0205291c](#main0205291c) | `data_0205291c` | Interior/member metadata alias; no separate allocation |
| [main:02053109](#main02053109) | `data_02053109` | Interior/member metadata alias; no separate allocation |
| [main:0205310a](#main0205310a) | `data_0205310a` | Interior/member metadata alias; no separate allocation |
| [main:0205310b](#main0205310b) | `data_0205310b` | Interior/member metadata alias; no separate allocation |
| [main:02053640](#main02053640) | `data_02053640` | Interior/member metadata alias; no separate allocation |
| [main:020536c0](#main020536c0) | `data_020536c0` | Interior/member metadata alias; no separate allocation |
| [main:02053740](#main02053740) | `data_02053740` | Interior/member metadata alias; no separate allocation |
| [main:02053780](#main02053780) | `data_02053780` | Interior/member metadata alias; no separate allocation |
| [main:02053800](#main02053800) | `data_02053800` | Interior/member metadata alias; no separate allocation |
| [main:02053900](#main02053900) | `data_02053900` | Interior/member metadata alias; no separate allocation |
| [main:02053980](#main02053980) | `data_02053980` | Interior/member metadata alias; no separate allocation |
| [main:020539c0](#main020539c0) | `data_020539c0` | Interior/member metadata alias; no separate allocation |
| [main:02053ac0](#main02053ac0) | `data_02053ac0` | Interior/member metadata alias; no separate allocation |
| [main:02053b40](#main02053b40) | `data_02053b40` | Interior/member metadata alias; no separate allocation |
| [main:02053b80](#main02053b80) | `data_02053b80` | Interior/member metadata alias; no separate allocation |
| [main:02053d80](#main02053d80) | `data_02053d80` | Interior/member metadata alias; no separate allocation |
| [main:02056ae0](#main02056ae0) | `data_02056ae0` | Existing canonical identity; alias merge remains |
| [main:0205fe34](#main0205fe34) | `data_0205fe34` | Interior/member metadata alias; no separate allocation |
| [main:0205fe8c](#main0205fe8c) | `data_0205fe8c` | Interior/member metadata alias; no separate allocation |
| [main:0205fea8](#main0205fea8) | `data_0205fea8` | Interior/member metadata alias; no separate allocation |
| [main:0205febc](#main0205febc) | `data_0205febc` | Storage exists; operational role unproved |
| [main:02060764](#main02060764) | `data_02060764` | Storage exists; operational role unproved |
| [main:020609c0](#main020609c0) | `data_020609c0` | Storage exists; operational role unproved |
| [main:02060f22](#main02060f22) | `data_02060f22` | Stat-field meaning unproved |
| [main:02060f23](#main02060f23) | `data_02060f23` | Stat-field meaning unproved |
| [dtcm:027e0134](#dtcm027e0134) | `data_027e0134` | Physical objects have overlapping execution views |
| [dtcm:027e0148](#dtcm027e0148) | `data_027e0148` | Physical objects have overlapping execution views |
| [dtcm:027e0160](#dtcm027e0160) | `data_027e0160` | Physical objects have overlapping execution views |
| [dtcm:027e0164](#dtcm027e0164) | `data_027e0164` | Physical objects have overlapping execution views |
| [dtcm:027e016c](#dtcm027e016c) | `data_027e016c` | Physical objects have overlapping execution views |
| [ov001:0209edf4](#ov0010209edf4) | `data_ov001_0209edf4` | Interior/member metadata alias; no separate allocation |
| [ov001:0209edf8](#ov0010209edf8) | `data_ov001_0209edf8` | Interior/member metadata alias; no separate allocation |
| [ov001:020a0101](#ov001020a0101) | `data_ov001_020a0101` | Interior/member metadata alias; no separate allocation |
| [ov001:020a0303](#ov001020a0303) | `data_ov001_020a0303` | Interior/member metadata alias; no separate allocation |
| [ov001:020a0378](#ov001020a0378) | `data_ov001_020a0378` | Interior/member metadata alias; no separate allocation |
| [ov001:020a037c](#ov001020a037c) | `data_ov001_020a037c` | Interior/member metadata alias; no separate allocation |
| [ov001:020a0505](#ov001020a0505) | `data_ov001_020a0505` | Interior/member metadata alias; no separate allocation |
| [ov003:020650c0](#ov003020650c0) | `data_ov003_020650c0` | Storage exists; operational role unproved |
| [ov004:02064575](#ov00402064575) | `data_ov004_02064575` | Interior/member metadata alias; no separate allocation |
| [ov004:0206459d](#ov0040206459d) | `data_ov004_0206459d` | Storage exists; operational role unproved |
| [ov013:020749f4](#ov013020749f4) | `data_ov013_020749f4` | Interior/member metadata alias; no separate allocation |
| [ov013:02074a74](#ov01302074a74) | `data_ov013_02074a74` | Interior/member metadata alias; no separate allocation |
| [ov015:0207a313](#ov0150207a313) | `data_ov015_0207a313` | Interior/member metadata alias; no separate allocation |
| [ov015:0207a40f](#ov0150207a40f) | `data_ov015_0207a40f` | Interior/member metadata alias; no separate allocation |
| [ov015:0207f0f9](#ov0150207f0f9) | `data_ov015_0207f0f9` | Interior/member metadata alias; no separate allocation |
| [ov015:0207f151](#ov0150207f151) | `data_ov015_0207f151` | Interior/member metadata alias; no separate allocation |
| [ov015:0207f211](#ov0150207f211) | `data_ov015_0207f211` | Interior/member metadata alias; no separate allocation |
| [ov015:0207f235](#ov0150207f235) | `data_ov015_0207f235` | Interior/member metadata alias; no separate allocation |
| [ov015:0207f26d](#ov0150207f26d) | `data_ov015_0207f26d` | Interior/member metadata alias; no separate allocation |
| [ov015:02080000](#ov01502080000) | `data_ov015_02080000` | Physical fragment of a proved logical owner |
| [ov015:02080202](#ov01502080202) | `data_ov015_02080202` | Physical fragment of a proved logical owner |
| [ov015:0208020e](#ov0150208020e) | `data_ov015_0208020e` | Physical fragment of a proved logical owner |
| [ov015:02080303](#ov01502080303) | `data_ov015_02080303` | Physical fragment of a proved logical owner |
| [ov015:020803e0](#ov015020803e0) | `data_ov015_020803e0` | Storage exists; operational role unproved |
| [ov015:02080404](#ov01502080404) | `data_ov015_02080404` | Storage exists; operational role unproved |
| [ov015:02080504](#ov01502080504) | `data_ov015_02080504` | Storage exists; operational role unproved |
| [ov015:02080605](#ov01502080605) | `data_ov015_02080605` | Storage exists; operational role unproved |
| [ov015:02080606](#ov01502080606) | `data_ov015_02080606` | Storage exists; operational role unproved |
| [ov021:020b560c](#ov021020b560c) | `data_ov021_020b560c` | Address passed in an argument the callee does not read |
| [ov021:020b5620](#ov021020b5620) | `data_ov021_020b5620` | Existing canonical identity; alias merge remains |
| [ov021:020b56c4](#ov021020b56c4) | `data_ov021_020b56c4` | Existing canonical identity; alias merge remains |
| [ov021:020b56dc](#ov021020b56dc) | `data_ov021_020b56dc` | Existing canonical identity; alias merge remains |
| [ov030:020bd004](#ov030020bd004) | `data_ov030_020bd004` | Storage exists; operational role unproved |
| [ov031:020bc815](#ov031020bc815) | `data_ov031_020bc815` | Storage exists; operational role unproved |
| [ov033:020baafc](#ov033020baafc) | `data_ov033_020baafc` | Storage exists; operational role unproved |
| [ov034:020beae0](#ov034020beae0) | `data_ov034_020beae0` | Foreign-bank binding remains unresolved |
| [ov034:020bee80](#ov034020bee80) | `data_ov034_020bee80` | Foreign-bank binding remains unresolved |
| [ov034:020bf6a0](#ov034020bf6a0) | `data_ov034_020bf6a0` | Foreign-bank binding remains unresolved |
| [ov034:020bfca0](#ov034020bfca0) | `data_ov034_020bfca0` | Foreign-bank binding remains unresolved |
| [ov036:020c33b0](#ov036020c33b0) | `data_ov036_020c33b0` | Storage exists; operational role unproved |
| [ov036:020c36b8](#ov036020c36b8) | `data_ov036_020c36b8` | Storage exists; operational role unproved |
| [ov036:020c36c0](#ov036020c36c0) | `data_ov036_020c36c0` | Storage exists; operational role unproved |
| [ov036:020c4014](#ov036020c4014) | `data_ov036_020c4014` | Foreign-bank binding remains unresolved |
| [ov036:020c4160](#ov036020c4160) | `data_ov036_020c4160` | Foreign-bank binding remains unresolved |
| [ov036:020c4c60](#ov036020c4c60) | `data_ov036_020c4c60` | Foreign-bank binding remains unresolved |
| [ov036:020c4fe0](#ov036020c4fe0) | `data_ov036_020c4fe0` | Foreign-bank binding remains unresolved |
| [ov036:020c59a0](#ov036020c59a0) | `data_ov036_020c59a0` | Foreign-bank binding remains unresolved |
| [ov036:020c5cc0](#ov036020c5cc0) | `data_ov036_020c5cc0` | Foreign-bank binding remains unresolved |
| [ov036:020c5da0](#ov036020c5da0) | `data_ov036_020c5da0` | Foreign-bank binding remains unresolved |
| [ov036:020c7da0](#ov036020c7da0) | `data_ov036_020c7da0` | Foreign-bank binding remains unresolved |
| [ov041:020cf700](#ov041020cf700) | `data_ov041_020cf700` | Storage exists; operational role unproved |
| [ov055:020d3f3d](#ov055020d3f3d) | `data_ov055_020d3f3d` | Own storage opaque; observed reference selects foreign code |
| [ov061:020d8569](#ov061020d8569) | `data_ov061_020d8569` | Own storage opaque; observed reference selects foreign code |
| [ov062:020d8569](#ov062020d8569) | `data_ov062_020d8569` | Own storage opaque; observed reference selects foreign code |
| [ov076:020cd404](#ov076020cd404) | `data_ov076_020cd404` | Interior/member metadata alias; no separate allocation |
| [ov077:020ca3a4](#ov077020ca3a4) | `data_ov077_020ca3a4` | Interior/member metadata alias; no separate allocation |
| [ov091:020c2a30](#ov091020c2a30) | `data_ov091_020c2a30` | Storage exists; operational role unproved |
| [ov101:020c1bc8](#ov101020c1bc8) | `data_ov101_020c1bc8` | Interior/member metadata alias; no separate allocation |
| [ov101:020c1c60](#ov101020c1c60) | `data_ov101_020c1c60` | Interior/member metadata alias; no separate allocation |
| [ov101:020c1e61](#ov101020c1e61) | `data_ov101_020c1e61` | Interior/member metadata alias; no separate allocation |
| [ov101:020c1ea0](#ov101020c1ea0) | `data_ov101_020c1ea0` | Interior/member metadata alias; no separate allocation |
| [ov101:020c2360](#ov101020c2360) | `data_ov101_020c2360` | Interior/member metadata alias; no separate allocation |
| [ov101:020c2368](#ov101020c2368) | `data_ov101_020c2368` | Interior/member metadata alias; no separate allocation |
| [ov101:020c2380](#ov101020c2380) | `data_ov101_020c2380` | Interior/member metadata alias; no separate allocation |
| [ov101:020c2b18](#ov101020c2b18) | `data_ov101_020c2b18` | Interior/member metadata alias; no separate allocation |
| [ov101:020c2cc5](#ov101020c2cc5) | `data_ov101_020c2cc5` | Interior/member metadata alias; no separate allocation |
| [ov101:020c2d41](#ov101020c2d41) | `data_ov101_020c2d41` | Interior/member metadata alias; no separate allocation |
| [ov101:020c322d](#ov101020c322d) | `data_ov101_020c322d` | Interior/member metadata alias; no separate allocation |
| [ov101:020c3275](#ov101020c3275) | `data_ov101_020c3275` | Interior/member metadata alias; no separate allocation |
| [ov101:020c3500](#ov101020c3500) | `data_ov101_020c3500` | Interior/member metadata alias; no separate allocation |
| [ov101:020c4014](#ov101020c4014) | `data_ov101_020c4014` | Interior/member metadata alias; no separate allocation |
| [ov101:020c4160](#ov101020c4160) | `data_ov101_020c4160` | Interior/member metadata alias; no separate allocation |
| [ov101:020c4c60](#ov101020c4c60) | `data_ov101_020c4c60` | Interior/member metadata alias; no separate allocation |
| [ov101:020c4fe0](#ov101020c4fe0) | `data_ov101_020c4fe0` | Interior/member metadata alias; no separate allocation |
| [ov104:020d3744](#ov104020d3744) | `data_ov104_020d3744` | Interior/member metadata alias; no separate allocation |

## Overlays 000-020: 28 retained labels

### ov001:0209edf4

`data_ov001_0209edf4`: Interior/member metadata alias; no separate allocation.

No additional C/ELF allocation is proved for this numeric label. `gHudGaugeTable`; containing object [0x0209edec, 0x0209ee14), 40 B; label offset +0x8.

**Evidence:** Interior address gHudGaugeTable +8: layouts[0].size, within the active 40 -byte table. No direct active C use of this alias is established.

**Retained because:** A numeric alias is not a separate data owner; removing or changing its representation requires relocation evidence.

**Next proof:** Inspect symbol/relocation requirements, then use the existing named member or an explicit offset alias without changing table bytes.

**Sources:** [eu/src/overlays/ov001/data/tables/gHudGaugeTable.c](../src/overlays/ov001/data/tables/gHudGaugeTable.c).

### ov001:0209edf8

`data_ov001_0209edf8`: Interior/member metadata alias; no separate allocation.

No additional C/ELF allocation is proved for this numeric label. `gHudGaugeTable`; containing object [0x0209edec, 0x0209ee14), 40 B; label offset +0xc.

**Evidence:** Interior address gHudGaugeTable +0xc: layouts[0].cellCount, within the active 40 -byte table.

**Retained because:** No independent owner or direct alias use is established.

**Next proof:** Audit relocations; reference the existing typed member or retain the explicit alias where required.

**Sources:** [eu/src/overlays/ov001/data/tables/gHudGaugeTable.c](../src/overlays/ov001/data/tables/gHudGaugeTable.c).

### ov001:020a0101

`data_ov001_020a0101`: Interior/member metadata alias; no separate allocation.

No additional C/ELF allocation is proved for this numeric label. `gGroupEntries`; containing object [0x0209f62c, 0x020a0250), 3108 B; label offset +0xad5.

**Evidence:** Interior byte in the 259-entry gGroupEntries array, whose entry stride is12. The offset from base 0209f62c is 0xad5 = entry231 +1, inside the high byte of that entry's s16 id.

**Retained because:** Only an absolute/linker alias and pointer-shaped word in an ov034 table reference this address; no independent field owner is proved.

**Next proof:** Verify whether the ov034 word is a genuine relocation/pointer or an integer pattern before removing or expressing the alias as an offset.

**Sources:** [eu/src/overlays/ov001/data/tables/gGroupEntries.c](../src/overlays/ov001/data/tables/gGroupEntries.c), [eu/libs/nitro/data/SdkLinkerSymbols.s](../libs/nitro/data/SdkLinkerSymbols.s), [eu/src/ov034/data/Data_ov034_020be980.c](../src/ov034/data/Data_ov034_020be980.c).

### ov001:020a0303

`data_ov001_020a0303`: Interior/member metadata alias; no separate allocation.

No additional C/ELF allocation is proved for this numeric label. `sOv001_TraTg_020a02fc`; containing object [0x020a02fc, 0x020a0304), 8 B; label offset +0x7.

**Evidence:** Byte+7 inside the eight-byte tra_tg string storage at 020a02fc; it is zero padding after the string terminator.

**Retained because:** No independent read or owner is established.

**Next proof:** Check linker alias/relocation requirements before consolidating the name under the existing string owner.

**Sources:** [eu/src/overlays/ov001/data/strings/Strings_ov001_020a02fc.c](../src/overlays/ov001/data/strings/Strings_ov001_020a02fc.c).

### ov001:020a0378

`data_ov001_020a0378`: Interior/member metadata alias; no separate allocation.

No additional C/ELF allocation is proved for this numeric label. `gStageHeapConfigs`; containing object [0x020a0374, 0x020a038c), 24 B; label offset +0x4.

**Evidence:** gStageHeapConfigs[0].heapSize at base+4, in the two12 -byte config records.

**Retained because:** No independent owner; no direct alias consumer established.

**Next proof:** Prefer the existing member when source consumers are identified; preserve aliases required by native linking.

**Sources:** [eu/src/overlays/ov001/data/tables/gStageHeapConfigs.c](../src/overlays/ov001/data/tables/gStageHeapConfigs.c), [eu/libs/nitro/data/SdkLinkerSymbols.s](../libs/nitro/data/SdkLinkerSymbols.s).

### ov001:020a037c

`data_ov001_020a037c`: Interior/member metadata alias; no separate allocation.

No additional C/ELF allocation is proved for this numeric label. `gStageHeapConfigs`; containing object [0x020a0374, 0x020a038c), 24 B; label offset +0x8.

**Evidence:** gStageHeapConfigs[0].eventCount at base+8.

**Retained because:** No independent owner; no direct alias consumer established.

**Next proof:** Audit relocations and retain as a field-offset alias if required.

**Sources:** [eu/src/overlays/ov001/data/tables/gStageHeapConfigs.c](../src/overlays/ov001/data/tables/gStageHeapConfigs.c), [eu/libs/nitro/data/SdkLinkerSymbols.s](../libs/nitro/data/SdkLinkerSymbols.s).

### ov001:020a0505

`data_ov001_020a0505`: Interior/member metadata alias; no separate allocation.

No additional C/ELF allocation is proved for this numeric label. `gModelDictionaryNameScratch`; containing object [0x020a0504, 0x020a0514), 16 B; label offset +0x1.

**Evidence:** Byte+1 within the 16 -byte model dictionary-name scratch at 020a0504, cleared and filled by FindModelResourceIndexByName.

**Retained because:** No independent owner or active named reference established.

**Next proof:** Inspect relocation requirements; represent as an interior alias only if needed, without inventing a second buffer.

**Sources:** [eu/src/overlays/ov001/data/bss/Bss_ov001_020a0500.c](../src/overlays/ov001/data/bss/Bss_ov001_020a0500.c).

### ov003:020650c0

`data_ov003_020650c0`: Storage exists; operational role unproved.

Physical definition [0x020650c0, 0x020650c4), 4 B (data). No canonical owner is established.

**Evidence:** One u32 initialized 0xffffffff; MovieScene_Shutdown writes-1. No additional active read/write consumer was found.

**Retained because:** The reset/sentinel alone does not identify an index, task handle, flag or playback state.

**Next proof:** Find a native reader or relocation outside the current direct C references; only then assign an operational name.

**Sources:** [eu/src/ov003/data/Data_ov003_020650c0.c](../src/ov003/data/Data_ov003_020650c0.c), [eu/src/overlays/ov003/calls/MovieScene_Shutdown.c](../src/overlays/ov003/calls/MovieScene_Shutdown.c).

### ov004:02064575

`data_ov004_02064575`: Interior/member metadata alias; no separate allocation.

No additional C/ELF allocation is proved for this numeric label. `sOv004_SfSffont8Nftr_02064564`; containing object [0x02064564, 0x02064578), 20 B; label offset +0x11.

**Evidence:** Byte+17 inside the 20 -byte sf/sffont_8.nftr path storage at 02064564, in its zero tail.

**Retained because:** No independent active owner/reference is established.

**Next proof:** Check alias requirements and keep the containing named string as owner.

**Sources:** [eu/src/overlays/ov004/data/strings/Strings_ov004_02064564.c](../src/overlays/ov004/data/strings/Strings_ov004_02064564.c).

### ov004:0206459d

`data_ov004_0206459d`: Storage exists; operational role unproved.

Physical definition [0x0206459d, 0x020645a0), 3 B (data). No canonical owner is established.

**Evidence:** Three explicit zero bytes immediately after the 29 -byte /sf/sf.z storage, ending at 020645a0. No active consumer beyond the definition was found.

**Retained because:** This may be alignment/preserved data, but a standalone payload role is not established.

**Next proof:** Inspect original section alignment and relocations; classify as padding only if native boundary evidence supports that.

**Sources:** [eu/src/ov004/data/Data_ov004_0206459d.c](../src/ov004/data/Data_ov004_0206459d.c).

### ov013:020749f4

`data_ov013_020749f4`: Interior/member metadata alias; no separate allocation.

No additional C/ELF allocation is proved for this numeric label. `gRecordSelectionBgConfig`; containing object [0x020749f4, 0x02074a08), 20 B; label offset +0x0.

**Evidence:** Same configured address as gRecordSelectionBgConfig; the active definition already uses that descriptive name.

**Retained because:** The numerical alias can be required for legacy references; it is not an unknown data owner.

**Next proof:** Audit alias users and linker requirements; use the existing descriptive identity, without adding a third name.

**Sources:** [eu/src/overlays/ov013/data/tables/gRecordSelectionBgConfig.c](../src/overlays/ov013/data/tables/gRecordSelectionBgConfig.c), [eu/libs/nitro/data/SdkLinkerSymbols.s](../libs/nitro/data/SdkLinkerSymbols.s), [eu/src/overlays/ov013/calls/InitRecordResultScreen.c](../src/overlays/ov013/calls/InitRecordResultScreen.c).

### ov013:02074a74

`data_ov013_02074a74`: Interior/member metadata alias; no separate allocation.

No additional C/ELF allocation is proved for this numeric label. `gRecordSelectionObjConfig`; containing object [0x02074a74, 0x02074a8c), 24 B; label offset +0x0.

**Evidence:** Same configured address as gRecordSelectionObjConfig; the active definition already uses that descriptive name.

**Retained because:** The numerical alias can be required for legacy references; it is not an unknown data owner.

**Next proof:** Audit alias users and linker requirements; use the existing descriptive identity.

**Sources:** [eu/src/overlays/ov013/data/tables/gRecordSelectionObjConfig.c](../src/overlays/ov013/data/tables/gRecordSelectionObjConfig.c), [eu/libs/nitro/data/SdkLinkerSymbols.s](../libs/nitro/data/SdkLinkerSymbols.s), [eu/src/overlays/ov013/calls/InitRecordResultScreen.c](../src/overlays/ov013/calls/InitRecordResultScreen.c).

### ov015:0207a313

`data_ov015_0207a313`: Interior/member metadata alias; no separate allocation.

No additional C/ELF allocation is proved for this numeric label. `gWirelessThemeData`; containing object [0x0207a310, 0x0207a40c), 252 B; label offset +0x3.

**Evidence:** gWirelessThemeData+3: charIndex of themes[0], immediately after the two-byte header and first theme bgIndex.

**Retained because:** The alias has an absolute SDK/linker entry but no separate owner or direct C consumer.

**Next proof:** Verify alias/relocation needs and express the existing member address if needed, without changing the packed25 -byte theme stride.

**Sources:** [eu/src/overlays/ov015/data/tables/gWirelessThemeData.c](../src/overlays/ov015/data/tables/gWirelessThemeData.c), [eu/libs/nitro/data/SdkLinkerSymbols.s](../libs/nitro/data/SdkLinkerSymbols.s).

### ov015:0207a40f

`data_ov015_0207a40f`: Interior/member metadata alias; no separate allocation.

No additional C/ELF allocation is proved for this numeric label. `gWirelessSlotStyles`; containing object [0x0207a40c, 0x0207a548), 316 B; label offset +0x3.

**Evidence:** gWirelessSlotStyles+3: parameters02[1] in the first four-byte style. SetupResultPanel views this address as a strided textId column and indexes by player/partner rank.

**Retained because:** The rank-text column aliases the style records; it is not a separate array allocation, and the remaining style field meanings are incomplete.

**Next proof:** Document/use an explicit column alias or a correct shared view after comparing relocations; do not split or duplicate the underlying table.

**Sources:** [eu/src/overlays/ov015/data/tables/gWirelessSlotStyles.c](../src/overlays/ov015/data/tables/gWirelessSlotStyles.c), [eu/libs/nitro/data/SdkLinkerSymbols.s](../libs/nitro/data/SdkLinkerSymbols.s), [eu/src/overlays/ov015/calls/SetupResultPanel.c](../src/overlays/ov015/calls/SetupResultPanel.c).

### ov015:0207f0f9

`data_ov015_0207f0f9`: Interior/member metadata alias; no separate allocation.

No additional C/ELF allocation is proved for this numeric label. `gWirelessScanBuffer`; containing object [0x0207efa0, 0x0207f3a0), 1024 B; label offset +0x159.

**Evidence:** Interior byte at gWirelessScanBuffer +0x159, within its 0x400 -byte static buffer. Native scan callback invalidates the whole 0x400 -byte buffer.

**Retained because:** No independent field/owner is proved for this arbitrary interior address.

**Next proof:** Audit ambiguous relocation/integer references and preserve required offset aliases; do not invent a second scan buffer.

**Sources:** [eu/src/overlays/ov015/data/bss/gWirelessScanBuffer.c](../src/overlays/ov015/data/bss/gWirelessScanBuffer.c), [eu/libs/nitro/data/SdkLinkerSymbols.s](../libs/nitro/data/SdkLinkerSymbols.s).

### ov015:0207f151

`data_ov015_0207f151`: Interior/member metadata alias; no separate allocation.

No additional C/ELF allocation is proved for this numeric label. `gWirelessScanBuffer`; containing object [0x0207efa0, 0x0207f3a0), 1024 B; label offset +0x1b1.

**Evidence:** Interior byte at gWirelessScanBuffer +0x1b1, within its 0x400 -byte static buffer. Native scan callback invalidates the whole 0x400 -byte buffer.

**Retained because:** No independent field/owner is proved for this arbitrary interior address.

**Next proof:** Audit ambiguous relocation/integer references and preserve required offset aliases; do not invent a second scan buffer.

**Sources:** [eu/src/overlays/ov015/data/bss/gWirelessScanBuffer.c](../src/overlays/ov015/data/bss/gWirelessScanBuffer.c), [eu/libs/nitro/data/SdkLinkerSymbols.s](../libs/nitro/data/SdkLinkerSymbols.s).

### ov015:0207f211

`data_ov015_0207f211`: Interior/member metadata alias; no separate allocation.

No additional C/ELF allocation is proved for this numeric label. `gWirelessScanBuffer`; containing object [0x0207efa0, 0x0207f3a0), 1024 B; label offset +0x271.

**Evidence:** Interior byte at gWirelessScanBuffer +0x271, within its 0x400 -byte static buffer. Native scan callback invalidates the whole 0x400 -byte buffer.

**Retained because:** No independent field/owner is proved for this arbitrary interior address.

**Next proof:** Audit ambiguous relocation/integer references and preserve required offset aliases; do not invent a second scan buffer.

**Sources:** [eu/src/overlays/ov015/data/bss/gWirelessScanBuffer.c](../src/overlays/ov015/data/bss/gWirelessScanBuffer.c), [eu/libs/nitro/data/SdkLinkerSymbols.s](../libs/nitro/data/SdkLinkerSymbols.s).

### ov015:0207f235

`data_ov015_0207f235`: Interior/member metadata alias; no separate allocation.

No additional C/ELF allocation is proved for this numeric label. `gWirelessScanBuffer`; containing object [0x0207efa0, 0x0207f3a0), 1024 B; label offset +0x295.

**Evidence:** Interior byte at gWirelessScanBuffer +0x295, within its 0x400 -byte static buffer. Native scan callback invalidates the whole 0x400 -byte buffer.

**Retained because:** No independent field/owner is proved for this arbitrary interior address.

**Next proof:** Audit ambiguous relocation/integer references and preserve required offset aliases; do not invent a second scan buffer.

**Sources:** [eu/src/overlays/ov015/data/bss/gWirelessScanBuffer.c](../src/overlays/ov015/data/bss/gWirelessScanBuffer.c), [eu/libs/nitro/data/SdkLinkerSymbols.s](../libs/nitro/data/SdkLinkerSymbols.s).

### ov015:0207f26d

`data_ov015_0207f26d`: Interior/member metadata alias; no separate allocation.

No additional C/ELF allocation is proved for this numeric label. `gWirelessScanBuffer`; containing object [0x0207efa0, 0x0207f3a0), 1024 B; label offset +0x2cd.

**Evidence:** Interior byte at gWirelessScanBuffer +0x2cd, within its 0x400 -byte static buffer. Native scan callback invalidates the whole 0x400 -byte buffer.

**Retained because:** No independent field/owner is proved for this arbitrary interior address.

**Next proof:** Audit ambiguous relocation/integer references and preserve required offset aliases; do not invent a second scan buffer.

**Sources:** [eu/src/overlays/ov015/data/bss/gWirelessScanBuffer.c](../src/overlays/ov015/data/bss/gWirelessScanBuffer.c), [eu/libs/nitro/data/SdkLinkerSymbols.s](../libs/nitro/data/SdkLinkerSymbols.s).

### ov015:02080000

`data_ov015_02080000`: Physical fragment of a proved logical owner.

Physical definition [0x02080000, 0x02080202), 514 B (bss). `gWirelessDataSharingStorage`; WM data-sharing logical state spans five physical definitions; logical span across physical definitions [0x0207fbc0, 0x020803e0), 2080 B; label offset +0x440; only 1088 B belong to its first physical definition.

**Evidence:** 514 -byte physical BSS fragment at data-sharing base 0207fbc0 +0x440. Native WM_StartDataSharing clears 0x820 bytes from that base; this fragment lies wholly in that state range ending 020803e0.

**Retained because:** No independent allocation or per-fragment semantic field is established; old boundaries slice the shared SDK state.

**Next proof:** Use the proved 2080 -byte logical owner in porting documentation. Any consolidation must preserve zero BSS size, symbol-offset aliases, relocations and native accesses; avoid artificial names for the fragments.

**Sources:** [eu/src/overlays/ov015/data/bss/Bss_ov015_02080000.c](../src/overlays/ov015/data/bss/Bss_ov015_02080000.c), [eu/src/overlays/ov015/data/bss/Bss_ov015_0207fbc0.c](../src/overlays/ov015/data/bss/Bss_ov015_0207fbc0.c).

### ov015:02080202

`data_ov015_02080202`: Physical fragment of a proved logical owner.

Physical definition [0x02080202, 0x0208020e), 12 B (bss). `gWirelessDataSharingStorage`; WM data-sharing logical state spans five physical definitions; logical span across physical definitions [0x0207fbc0, 0x020803e0), 2080 B; label offset +0x642; only 1088 B belong to its first physical definition.

**Evidence:** 12 -byte physical BSS fragment at data-sharing base 0207fbc0 +0x642. Native WM_StartDataSharing clears 0x820 bytes from that base; this fragment lies wholly in that state range ending 020803e0.

**Retained because:** No independent allocation or per-fragment semantic field is established; old boundaries slice the shared SDK state.

**Next proof:** Use the proved 2080 -byte logical owner in porting documentation. Any consolidation must preserve zero BSS size, symbol-offset aliases, relocations and native accesses; avoid artificial names for the fragments.

**Sources:** [eu/src/overlays/ov015/data/bss/Bss_ov015_02080202.c](../src/overlays/ov015/data/bss/Bss_ov015_02080202.c), [eu/src/overlays/ov015/data/bss/Bss_ov015_0207fbc0.c](../src/overlays/ov015/data/bss/Bss_ov015_0207fbc0.c).

### ov015:0208020e

`data_ov015_0208020e`: Physical fragment of a proved logical owner.

Physical definition [0x0208020e, 0x02080303), 245 B (bss). `gWirelessDataSharingStorage`; WM data-sharing logical state spans five physical definitions; logical span across physical definitions [0x0207fbc0, 0x020803e0), 2080 B; label offset +0x64e; only 1088 B belong to its first physical definition.

**Evidence:** 245 -byte physical BSS fragment at data-sharing base 0207fbc0 +0x64e. Native WM_StartDataSharing clears 0x820 bytes from that base; this fragment lies wholly in that state range ending 020803e0.

**Retained because:** No independent allocation or per-fragment semantic field is established; old boundaries slice the shared SDK state.

**Next proof:** Use the proved 2080 -byte logical owner in porting documentation. Any consolidation must preserve zero BSS size, symbol-offset aliases, relocations and native accesses; avoid artificial names for the fragments.

**Sources:** [eu/src/overlays/ov015/data/bss/Bss_ov015_0208020e.c](../src/overlays/ov015/data/bss/Bss_ov015_0208020e.c), [eu/src/overlays/ov015/data/bss/Bss_ov015_0207fbc0.c](../src/overlays/ov015/data/bss/Bss_ov015_0207fbc0.c).

### ov015:02080303

`data_ov015_02080303`: Physical fragment of a proved logical owner.

Physical definition [0x02080303, 0x020803e0), 221 B (bss). `gWirelessDataSharingStorage`; WM data-sharing logical state spans five physical definitions; logical span across physical definitions [0x0207fbc0, 0x020803e0), 2080 B; label offset +0x743; only 1088 B belong to its first physical definition.

**Evidence:** 221 -byte physical BSS fragment at data-sharing base 0207fbc0 +0x743. Native WM_StartDataSharing clears 0x820 bytes from that base; this fragment lies wholly in that state range ending 020803e0.

**Retained because:** No independent allocation or per-fragment semantic field is established; old boundaries slice the shared SDK state.

**Next proof:** Use the proved 2080 -byte logical owner in porting documentation. Any consolidation must preserve zero BSS size, symbol-offset aliases, relocations and native accesses; avoid artificial names for the fragments.

**Sources:** [eu/src/overlays/ov015/data/bss/Bss_ov015_02080303.c](../src/overlays/ov015/data/bss/Bss_ov015_02080303.c), [eu/src/ov034/data/Data_ov034_020bfca0.c](../src/ov034/data/Data_ov034_020bfca0.c), [eu/src/overlays/ov015/data/bss/Bss_ov015_0207fbc0.c](../src/overlays/ov015/data/bss/Bss_ov015_0207fbc0.c).

### ov015:020803e0

`data_ov015_020803e0`: Storage exists; operational role unproved.

Physical definition [0x020803e0, 0x02080404), 36 B (bss). No canonical owner is established.

**Evidence:** 36 -byte zero-initialized physical BSS definition. No direct active function consumer was found; some addresses occur as pointer-shaped values in ov034 data tables.

**Retained because:** A pointer-shaped integer or zero block alone does not prove a wireless owner, independent allocation or field role.

**Next proof:** Inspect original relocation classification and native pointer consumers for the ov034 entries; determine whether these are actual addresses or integer/colour patterns before assigning an owner.

**Sources:** [eu/src/overlays/ov015/data/bss/Bss_ov015_020803e0.c](../src/overlays/ov015/data/bss/Bss_ov015_020803e0.c).

### ov015:02080404

`data_ov015_02080404`: Storage exists; operational role unproved.

Physical definition [0x02080404, 0x02080504), 256 B (bss). No canonical owner is established.

**Evidence:** 256 -byte zero-initialized physical BSS definition. No direct active function consumer was found; some addresses occur as pointer-shaped values in ov034 data tables.

**Retained because:** A pointer-shaped integer or zero block alone does not prove a wireless owner, independent allocation or field role.

**Next proof:** Inspect original relocation classification and native pointer consumers for the ov034 entries; determine whether these are actual addresses or integer/colour patterns before assigning an owner.

**Sources:** [eu/src/overlays/ov015/data/bss/Bss_ov015_020803e0.c](../src/overlays/ov015/data/bss/Bss_ov015_020803e0.c), [eu/src/ov034/data/Data_ov034_020c056c.c](../src/ov034/data/Data_ov034_020c056c.c).

### ov015:02080504

`data_ov015_02080504`: Storage exists; operational role unproved.

Physical definition [0x02080504, 0x02080605), 257 B (bss). No canonical owner is established.

**Evidence:** 257 -byte zero-initialized physical BSS definition. No direct active function consumer was found; some addresses occur as pointer-shaped values in ov034 data tables.

**Retained because:** A pointer-shaped integer or zero block alone does not prove a wireless owner, independent allocation or field role.

**Next proof:** Inspect original relocation classification and native pointer consumers for the ov034 entries; determine whether these are actual addresses or integer/colour patterns before assigning an owner.

**Sources:** [eu/src/overlays/ov015/data/bss/Bss_ov015_02080504.c](../src/overlays/ov015/data/bss/Bss_ov015_02080504.c), [eu/src/ov034/data/Data_ov034_020bfca0.c](../src/ov034/data/Data_ov034_020bfca0.c).

### ov015:02080605

`data_ov015_02080605`: Storage exists; operational role unproved.

Physical definition [0x02080605, 0x02080606), 1 B (bss). No canonical owner is established.

**Evidence:** 1 -byte zero-initialized physical BSS definition. No direct active function consumer was found; some addresses occur as pointer-shaped values in ov034 data tables.

**Retained because:** A pointer-shaped integer or zero block alone does not prove a wireless owner, independent allocation or field role.

**Next proof:** Inspect original relocation classification and native pointer consumers for the ov034 entries; determine whether these are actual addresses or integer/colour patterns before assigning an owner.

**Sources:** [eu/src/overlays/ov015/data/bss/Bss_ov015_02080605.c](../src/overlays/ov015/data/bss/Bss_ov015_02080605.c), [eu/src/ov034/data/Data_ov034_020bfca0.c](../src/ov034/data/Data_ov034_020bfca0.c).

### ov015:02080606

`data_ov015_02080606`: Storage exists; operational role unproved.

Physical definition [0x02080606, 0x020812e0), 3290 B (bss). No canonical owner is established.

**Evidence:** 3290 -byte zero-initialized physical BSS definition. No direct active function consumer was found; some addresses occur as pointer-shaped values in ov034 data tables.

**Retained because:** A pointer-shaped integer or zero block alone does not prove a wireless owner, independent allocation or field role.

**Next proof:** Inspect original relocation classification and native pointer consumers for the ov034 entries; determine whether these are actual addresses or integer/colour patterns before assigning an owner.

**Sources:** [eu/src/overlays/ov015/data/bss/Bss_ov015_02080606.c](../src/overlays/ov015/data/bss/Bss_ov015_02080606.c), [eu/src/ov034/data/Data_ov034_020c056c.c](../src/ov034/data/Data_ov034_020c056c.c).

## Main/DTCM and overlays 021-040: 53 retained labels

### main:0205291a

`data_0205291a`: Interior/member metadata alias; no separate allocation.

No additional C/ELF allocation is proved for this numeric label. `sTexStartAddrTable`; containing object [0x02052918, 0x02052978), 96 B; label offset +0x2.

**Evidence and retained boundary:** The defining object contains the named backing allocation, not an independently allocated numeric symbol. Its address falls inside that allocation.

**Next proof:** An interior field of the texture-bank mapping table. Read exact uses of this halfword address before choosing a field/view name.

**Sources:** [eu/src/data/sdk/sTexStartAddrTable.c](../src/data/sdk/sTexStartAddrTable.c).

### main:0205291c

`data_0205291c`: Interior/member metadata alias; no separate allocation.

No additional C/ELF allocation is proved for this numeric label. `sTexStartAddrTable`; containing object [0x02052918, 0x02052978), 96 B; label offset +0x4.

**Evidence and retained boundary:** The defining object contains the named backing allocation, not an independently allocated numeric symbol. Its address falls inside that allocation.

**Next proof:** An interior field of the texture-bank mapping table. Confirm page-count reads versus pointer-base addends.

**Sources:** [eu/src/data/sdk/sTexStartAddrTable.c](../src/data/sdk/sTexStartAddrTable.c).

### main:02053109

`data_02053109`: Interior/member metadata alias; no separate allocation.

No additional C/ELF allocation is proved for this numeric label. `pivotUtil_`; containing object [0x02053108, 0x0205312c), 36 B; label offset +0x1.

**Evidence and retained boundary:** The defining object contains the named backing allocation, not an independently allocated numeric symbol. Its address falls inside that allocation.

**Next proof:** One-byte offset into the joint-animation pivot-index utility table. Trace consumer indexing rather than naming another allocated table.

**Sources:** [eu/libs/nns/g3d/data/g3d_nsbca_pivot_table.c](../libs/nns/g3d/data/g3d_nsbca_pivot_table.c).

### main:0205310a

`data_0205310a`: Interior/member metadata alias; no separate allocation.

No additional C/ELF allocation is proved for this numeric label. `pivotUtil_`; containing object [0x02053108, 0x0205312c), 36 B; label offset +0x2.

**Evidence and retained boundary:** The defining object contains the named backing allocation, not an independently allocated numeric symbol. Its address falls inside that allocation.

**Next proof:** Two-byte offset into the same pivot-index utility table; prove the specific indexed column.

**Sources:** [eu/libs/nns/g3d/data/g3d_nsbca_pivot_table.c](../libs/nns/g3d/data/g3d_nsbca_pivot_table.c).

### main:0205310b

`data_0205310b`: Interior/member metadata alias; no separate allocation.

No additional C/ELF allocation is proved for this numeric label. `pivotUtil_`; containing object [0x02053108, 0x0205312c), 36 B; label offset +0x3.

**Evidence and retained boundary:** The defining object contains the named backing allocation, not an independently allocated numeric symbol. Its address falls inside that allocation.

**Next proof:** Three-byte offset into the same pivot-index utility table; prove the specific indexed column.

**Sources:** [eu/libs/nns/g3d/data/g3d_nsbca_pivot_table.c](../libs/nns/g3d/data/g3d_nsbca_pivot_table.c).

### main:02053640

`data_02053640`: Interior/member metadata alias; no separate allocation.

No additional C/ELF allocation is proved for this numeric label. `gSinFx12Table`; containing object [0x02053580, 0x02055580), 8192 B; label offset +0xc0.

**Evidence and retained boundary:** The defining object contains the named backing allocation, not an independently allocated numeric symbol. Its address falls inside that allocation.

**Next proof:** An interior address in the 8192 -byte sine table. Resolve consumer index/stride and absolute .equ aliases before choosing a semantic view name; never allocate another table.

**Sources:** [eu/src/data/math/gSinFx12Table.c](../src/data/math/gSinFx12Table.c).

### main:020536c0

`data_020536c0`: Interior/member metadata alias; no separate allocation.

No additional C/ELF allocation is proved for this numeric label. `gSinFx12Table`; containing object [0x02053580, 0x02055580), 8192 B; label offset +0x140.

**Evidence and retained boundary:** The defining object contains the named backing allocation, not an independently allocated numeric symbol. Its address falls inside that allocation.

**Next proof:** An interior address in the 8192 -byte sine table. Resolve consumer index/stride and absolute .equ aliases before choosing a semantic view name; never allocate another table.

**Sources:** [eu/src/data/math/gSinFx12Table.c](../src/data/math/gSinFx12Table.c).

### main:02053740

`data_02053740`: Interior/member metadata alias; no separate allocation.

No additional C/ELF allocation is proved for this numeric label. `gSinFx12Table`; containing object [0x02053580, 0x02055580), 8192 B; label offset +0x1c0.

**Evidence and retained boundary:** The defining object contains the named backing allocation, not an independently allocated numeric symbol. Its address falls inside that allocation.

**Next proof:** An interior address in the 8192 -byte sine table. Resolve consumer index/stride and absolute .equ aliases before choosing a semantic view name; never allocate another table.

**Sources:** [eu/src/data/math/gSinFx12Table.c](../src/data/math/gSinFx12Table.c).

### main:02053780

`data_02053780`: Interior/member metadata alias; no separate allocation.

No additional C/ELF allocation is proved for this numeric label. `gSinFx12Table`; containing object [0x02053580, 0x02055580), 8192 B; label offset +0x200.

**Evidence and retained boundary:** The defining object contains the named backing allocation, not an independently allocated numeric symbol. Its address falls inside that allocation.

**Next proof:** An interior address in the 8192 -byte sine table. Resolve consumer index/stride and absolute .equ aliases before choosing a semantic view name; never allocate another table.

**Sources:** [eu/src/data/math/gSinFx12Table.c](../src/data/math/gSinFx12Table.c).

### main:02053800

`data_02053800`: Interior/member metadata alias; no separate allocation.

No additional C/ELF allocation is proved for this numeric label. `gSinFx12Table`; containing object [0x02053580, 0x02055580), 8192 B; label offset +0x280.

**Evidence and retained boundary:** The defining object contains the named backing allocation, not an independently allocated numeric symbol. Its address falls inside that allocation.

**Next proof:** An interior address in the 8192 -byte sine table. Resolve consumer index/stride and absolute .equ aliases before choosing a semantic view name; never allocate another table.

**Sources:** [eu/src/data/math/gSinFx12Table.c](../src/data/math/gSinFx12Table.c).

### main:02053900

`data_02053900`: Interior/member metadata alias; no separate allocation.

No additional C/ELF allocation is proved for this numeric label. `gSinFx12Table`; containing object [0x02053580, 0x02055580), 8192 B; label offset +0x380.

**Evidence and retained boundary:** The defining object contains the named backing allocation, not an independently allocated numeric symbol. Its address falls inside that allocation.

**Next proof:** An interior address in the 8192 -byte sine table. Resolve consumer index/stride and absolute .equ aliases before choosing a semantic view name; never allocate another table.

**Sources:** [eu/src/data/math/gSinFx12Table.c](../src/data/math/gSinFx12Table.c).

### main:02053980

`data_02053980`: Interior/member metadata alias; no separate allocation.

No additional C/ELF allocation is proved for this numeric label. `gSinFx12Table`; containing object [0x02053580, 0x02055580), 8192 B; label offset +0x400.

**Evidence and retained boundary:** The defining object contains the named backing allocation, not an independently allocated numeric symbol. Its address falls inside that allocation.

**Next proof:** An interior address in the 8192 -byte sine table. Resolve consumer index/stride and absolute .equ aliases before choosing a semantic view name; never allocate another table.

**Sources:** [eu/src/data/math/gSinFx12Table.c](../src/data/math/gSinFx12Table.c).

### main:020539c0

`data_020539c0`: Interior/member metadata alias; no separate allocation.

No additional C/ELF allocation is proved for this numeric label. `gSinFx12Table`; containing object [0x02053580, 0x02055580), 8192 B; label offset +0x440.

**Evidence and retained boundary:** The defining object contains the named backing allocation, not an independently allocated numeric symbol. Its address falls inside that allocation.

**Next proof:** An interior address in the 8192 -byte sine table. Resolve consumer index/stride and absolute .equ aliases before choosing a semantic view name; never allocate another table.

**Sources:** [eu/src/data/math/gSinFx12Table.c](../src/data/math/gSinFx12Table.c).

### main:02053ac0

`data_02053ac0`: Interior/member metadata alias; no separate allocation.

No additional C/ELF allocation is proved for this numeric label. `gSinFx12Table`; containing object [0x02053580, 0x02055580), 8192 B; label offset +0x540.

**Evidence and retained boundary:** The defining object contains the named backing allocation, not an independently allocated numeric symbol. Its address falls inside that allocation.

**Next proof:** An interior address in the 8192 -byte sine table. Resolve consumer index/stride and absolute .equ aliases before choosing a semantic view name; never allocate another table.

**Sources:** [eu/src/data/math/gSinFx12Table.c](../src/data/math/gSinFx12Table.c).

### main:02053b40

`data_02053b40`: Interior/member metadata alias; no separate allocation.

No additional C/ELF allocation is proved for this numeric label. `gSinFx12Table`; containing object [0x02053580, 0x02055580), 8192 B; label offset +0x5c0.

**Evidence and retained boundary:** The defining object contains the named backing allocation, not an independently allocated numeric symbol. Its address falls inside that allocation.

**Next proof:** An interior address in the 8192 -byte sine table. Resolve consumer index/stride and absolute .equ aliases before choosing a semantic view name; never allocate another table.

**Sources:** [eu/src/data/math/gSinFx12Table.c](../src/data/math/gSinFx12Table.c).

### main:02053b80

`data_02053b80`: Interior/member metadata alias; no separate allocation.

No additional C/ELF allocation is proved for this numeric label. `gSinFx12Table`; containing object [0x02053580, 0x02055580), 8192 B; label offset +0x600.

**Evidence and retained boundary:** The defining object contains the named backing allocation, not an independently allocated numeric symbol. Its address falls inside that allocation.

**Next proof:** An interior address in the 8192 -byte sine table. Resolve consumer index/stride and absolute .equ aliases before choosing a semantic view name; never allocate another table.

**Sources:** [eu/src/data/math/gSinFx12Table.c](../src/data/math/gSinFx12Table.c).

### main:02053d80

`data_02053d80`: Interior/member metadata alias; no separate allocation.

No additional C/ELF allocation is proved for this numeric label. `gSinFx12Table`; containing object [0x02053580, 0x02055580), 8192 B; label offset +0x800.

**Evidence and retained boundary:** The defining object contains the named backing allocation, not an independently allocated numeric symbol. Its address falls inside that allocation.

**Next proof:** An interior address in the 8192 -byte sine table. Resolve consumer index/stride and absolute .equ aliases before choosing a semantic view name; never allocate another table.

**Sources:** [eu/src/data/math/gSinFx12Table.c](../src/data/math/gSinFx12Table.c).

### main:02056ae0

`data_02056ae0`: Existing canonical identity; alias merge remains.

No additional C/ELF allocation is proved for this numeric label. `gTextTagColors`; containing object [0x02056ae0, 0x02056ae8), 8 B; label offset +0x0.

**Evidence and retained boundary:** Pinned C already defines this descriptive name; pinned symbols.txt also contains both names at the same bank/address. The numeric name has no separate ELF allocation.

**Next proof:** Audit every source/object relocation and absolute alias reference; canonicalize or document the duplicate config label without introducing another symbol, collision or allocation.

**Sources:** [eu/src/data/bss/Bss_main_02056ae0.c](../src/data/bss/Bss_main_02056ae0.c).

### main:0205fe34

`data_0205fe34`: Interior/member metadata alias; no separate allocation.

No additional C/ELF allocation is proved for this numeric label. `gSavedCameraState`; containing object [0x0205fe28, 0x0205febc), 148 B; label offset +0xc.

**Evidence and retained boundary:** The defining object contains the named backing allocation, not an independently allocated numeric symbol. Its address falls inside that allocation.

**Next proof:** A view inside the named owner; audit actual SDK writers/readers before inheriting the Camera label.

**Sources:** [eu/src/data/sdk/gSavedCameraState.c](../src/data/sdk/gSavedCameraState.c).

### main:0205fe8c

`data_0205fe8c`: Interior/member metadata alias; no separate allocation.

No additional C/ELF allocation is proved for this numeric label. `gSavedCameraState`; containing object [0x0205fe28, 0x0205febc), 148 B; label offset +0x64.

**Evidence and retained boundary:** The defining object contains the named backing allocation, not an independently allocated numeric symbol. Its address falls inside that allocation.

**Next proof:** A view inside the named owner; audit the specific offset and register-bank consumer.

**Sources:** [eu/src/data/sdk/gSavedCameraState.c](../src/data/sdk/gSavedCameraState.c).

### main:0205fea8

`data_0205fea8`: Interior/member metadata alias; no separate allocation.

No additional C/ELF allocation is proved for this numeric label. `gSavedCameraState`; containing object [0x0205fe28, 0x0205febc), 148 B; label offset +0x80.

**Evidence and retained boundary:** The defining object contains the named backing allocation, not an independently allocated numeric symbol. Its address falls inside that allocation.

**Next proof:** A view inside the named owner; audit the specific offset and register-bank consumer.

**Sources:** [eu/src/data/sdk/gSavedCameraState.c](../src/data/sdk/gSavedCameraState.c).

### main:0205febc

`data_0205febc`: Storage exists; operational role unproved.

Physical definition [0x0205febc, 0x0205fec4), 8 B (bss). No canonical owner is established.

**Evidence and retained boundary:** Eight-byte zero-initialized allocation between the 148 -byte SavedCameraState and the 256 -byte runtime category counters. No complete address or address|1 word was found in any of108 original domains. The neighboring known native allocations do not themselves establish this role.

**Next proof:** Audit computed accesses rooted before 0205febc and original initialization/reset spans; require a field read/write or an independently demonstrated structure extent before choosing an owner/field name. Preserve it as opaque BSS; no unused-data claim.

**Sources:** [eu/src/data/bss/Bss_main_0205febc.c](../src/data/bss/Bss_main_0205febc.c).

### main:02060764

`data_02060764`: Storage exists; operational role unproved.

Physical definition [0x02060764, 0x0206076c), 8 B (bss). No canonical owner is established.

**Evidence and retained boundary:** Eight-byte state view; func_0202d620 checks pointer word+4 and, when non-NULL, stores its argument to pointed object+0x600. Its only complete-base literal is in that setter; a separate all-domain search for 02060768/address|1 finds none. No pointer initialization or target consumer is demonstrated.

**Next proof:** Find the writer of the pointer slot 02060768 through a base/alias passed to a constructor, or prove the target+0x600 reader. The initial global BSS clear is not a semantic writer. Do not name the target/model/gameplay role from a single store.

**Sources:** [eu/src/data/bss/Bss_main_02060764.c](../src/data/bss/Bss_main_02060764.c).

### main:020609c0

`data_020609c0`: Storage exists; operational role unproved.

Physical definition [0x020609c0, 0x02060a50), 144 B (bss). No canonical owner is established.

**Evidence and retained boundary:** 144 -byte allocation cleared by InitPlayerData as three48 -byte records. The only complete-base literal is in that initializer. No live field reader or writer beyond the clear has been established.

**Next proof:** Trace aliases produced by the initializer/callers and neighboring record bases; establish at least one read or nonzero field write. Do not infer party-slot/player statistics contents solely from a private PlayerSlot typedef.

**Sources:** [eu/src/data/bss/Bss_main_020608e4.c](../src/data/bss/Bss_main_020608e4.c).

### main:02060f22

`data_02060f22`: Stat-field meaning unproved.

Physical definition [0x02060f22, 0x02060f23), 1 B (bss). No canonical owner is established.

**Evidence and retained boundary:** Output+6 is consistently called strength/attack, but no independent game-role proof has been recorded for this byte alias.

**Next proof:** Trace an actual damage or status-label consumer at stats+6; do not inherit a legacy typedef as sole proof.

**Sources:** [eu/src/data/bss/Bss_main_02060f22.c](../src/data/bss/Bss_main_02060f22.c).

### main:02060f23

`data_02060f23`: Stat-field meaning unproved.

Physical definition [0x02060f23, 0x02060f24), 1 B (bss). No canonical owner is established.

**Evidence and retained boundary:** Output+8 is named magic in ComputePlayerStats and defense in Matrix/selection views.

**Next proof:** Trace native damage arithmetic and real menu text/label indexing to determine output+8 and+a roles before assigning a specific attribute name.

**Sources:** [eu/src/data/bss/Bss_main_02060f23.c](../src/data/bss/Bss_main_02060f23.c).

### dtcm:027e0134

`data_027e0134`: Physical objects have overlapping execution views.

Physical definition [0x027e0134, 0x027e0148), 20 B (bss). No canonical owner is established.

**Evidence and retained boundary:** 20 -byte native symbol. InitMoverFromParams has a larger CollHitRecord view: model 0, face 4, wallFace 8, unknown 0xc, target 0x10; nearestTime+0x24 lands 0158 in the neighboring 24 -byte ContactPlane object, and contacts+0x44 lands 0178 in the later 128 -byte storage.

**Next proof:** Audit original ROM loads/stores for the larger views and all consumers; establish when scratch roles overlap and which result fields remain live across callbacks before selecting per-view names or a shared union contract. Preserve all five native symbols and exact sizes meanwhile.

**Sources:** [eu/src/data/dtcm/bss/Bss_dtcm_027e0134.c](../src/data/dtcm/bss/Bss_dtcm_027e0134.c).

### dtcm:027e0148

`data_027e0148`: Physical objects have overlapping execution views.

Physical definition [0x027e0148, 0x027e0160), 24 B (bss). No canonical owner is established.

**Evidence and retained boundary:** 24 -byte native ContactPlane copy in RecordContactPlane: distance 0, normal 4, time 0x10 and surfaceType 0x14. InitMoverFromParams writes its 0158 time word as nearestTime via the larger 0134 view. Roles depend on execution phase.

**Next proof:** Audit original ROM loads/stores for the larger views and all consumers; establish when scratch roles overlap and which result fields remain live across callbacks before selecting per-view names or a shared union contract. Preserve all five native symbols and exact sizes meanwhile.

**Sources:** [eu/src/data/dtcm/bss/Bss_dtcm_027e0134.c](../src/data/dtcm/bss/Bss_dtcm_027e0134.c).

### dtcm:027e0160

`data_027e0160`: Physical objects have overlapping execution views.

Physical definition [0x027e0160, 0x027e0164), 4 B (bss). No canonical owner is established.

**Evidence and retained boundary:** 4 -byte native symbol used as the base of a 12 -byte VecFx32 in ResolveCollisionTreeContacts; vector Y/Z extend into the separate 0164 object. Magnitude/normalize/scale/add use the whole vector.

**Next proof:** Audit original ROM loads/stores for the larger views and all consumers; establish when scratch roles overlap and which result fields remain live across callbacks before selecting per-view names or a shared union contract. Preserve all five native symbols and exact sizes meanwhile.

**Sources:** [eu/src/data/dtcm/bss/Bss_dtcm_027e0160.c](../src/data/dtcm/bss/Bss_dtcm_027e0160.c).

### dtcm:027e0164

`data_027e0164`: Physical objects have overlapping execution views.

Physical definition [0x027e0164, 0x027e016c), 8 B (bss). No canonical owner is established.

**Evidence and retained boundary:** 8 -byte native symbol. FindQuadTreeContact and TestMoverAgainstModelTree pass this address as an InitPlaneContact output template. That writer places normal halfwords at+0x14/+0x16/+0x18, distance+0x1c and handle+0x80, all inside the following 128 -byte object. Its first 8 bytes also hold the Y/Z of the 0160 vector view.

**Next proof:** Audit original ROM loads/stores for the larger views and all consumers; establish when scratch roles overlap and which result fields remain live across callbacks before selecting per-view names or a shared union contract. Preserve all five native symbols and exact sizes meanwhile.

**Sources:** [eu/src/data/dtcm/bss/Bss_dtcm_027e0160.c](../src/data/dtcm/bss/Bss_dtcm_027e0160.c).

### dtcm:027e016c

`data_027e016c`: Physical objects have overlapping execution views.

Physical definition [0x027e016c, 0x027e01ec), 128 B (bss). No canonical owner is established.

**Evidence and retained boundary:** 128 -byte native symbol has no direct nondeclaration token use in the collected sources, but it is reached by proven ranges: InitPlaneContact output rooted 8 bytes earlier writes through+0x80, and the 0134 query view writes contacts at 0178 inside this storage. Direct-token absence does not imply unused storage.

**Next proof:** Audit original ROM loads/stores for the larger views and all consumers; establish when scratch roles overlap and which result fields remain live across callbacks before selecting per-view names or a shared union contract. Preserve all five native symbols and exact sizes meanwhile.

**Sources:** [eu/src/data/dtcm/bss/Bss_dtcm_027e0160.c](../src/data/dtcm/bss/Bss_dtcm_027e0160.c).

### ov021:020b560c

`data_ov021_020b560c`: Address passed in an argument the callee does not read.

Physical definition [0x020b560c, 0x020b5620), 20 B (data). No canonical owner is established.

**Evidence and retained boundary:** Twenty initialized zero bytes are passed as third argument by ScriptCmd_StopActorMotion to AttachActorToStageNode(actor,0,address,0). The real callee signature names argument3 nodeName, but stageActorId==0 clears the binding fields/flag and returns before reading nodeName. This call therefore does not prove motion parameters or a node name stored in the object.

**Next proof:** Look for a nonzero stageActorId call using this address, or a computed pointer from nearby DATA that actually reads its bytes. Establish a live consumer before assigning a role. If none can be proven, retain numeric storage and the explicit unused-argument contract without claiming unused allocation.

**Sources:** [eu/src/ov021/data/Data_ov021_020b560c.c](../src/ov021/data/Data_ov021_020b560c.c).

### ov021:020b5620

`data_ov021_020b5620`: Existing canonical identity; alias merge remains.

No additional C/ELF allocation is proved for this numeric label. `gActiveFieldButtonEntryIndex`; containing object [0x020b5620, 0x020b5624), 4 B; label offset +0x0.

**Evidence and retained boundary:** Pinned C already defines this descriptive name; pinned symbols.txt also contains both names at the same bank/address. The numeric name has no separate ELF allocation.

**Next proof:** Audit every source/object relocation and absolute alias reference; canonicalize or document the duplicate config label without introducing another symbol, collision or allocation.

**Sources:** [eu/src/overlays/ov021/data/bss/Bss_ov021_020b5620.c](../src/overlays/ov021/data/bss/Bss_ov021_020b5620.c).

### ov021:020b56c4

`data_ov021_020b56c4`: Existing canonical identity; alias merge remains.

No additional C/ELF allocation is proved for this numeric label. `gActiveFieldContext`; containing object [0x020b56c4, 0x020b56d0), 12 B; label offset +0x0.

**Evidence and retained boundary:** Pinned config contains both this numeric label and gActiveFieldContext at 020b56c4. RunScriptThread treats this 12 -byte allocation as event/link/actor pointers; the named alias and numeric definition coexist in the accepted sources.

**Next proof:** Audit EU macros, all object references and alias definitions before merging the numeric token into the existing descriptive name. Do not introduce a second descriptive name or bypass the occupied-name preflight.

**Sources:** [eu/src/overlays/ov021/data/bss/Bss_ov021_020b56c0.c](../src/overlays/ov021/data/bss/Bss_ov021_020b56c0.c).

### ov021:020b56dc

`data_ov021_020b56dc`: Existing canonical identity; alias merge remains.

No additional C/ELF allocation is proved for this numeric label. `gScriptHandlerTable`; containing object [0x020b56dc, 0x020b575c), 128 B; label offset +0x0.

**Evidence and retained boundary:** Pinned C already defines this descriptive name; pinned symbols.txt also contains both names at the same bank/address. The numeric name has no separate ELF allocation.

**Next proof:** Audit every source/object relocation and absolute alias reference; canonicalize or document the duplicate config label without introducing another symbol, collision or allocation.

**Sources:** [eu/src/overlays/ov021/data/bss/Bss_ov021_020b56d0.c](../src/overlays/ov021/data/bss/Bss_ov021_020b56d0.c).

### ov030:020bd004

`data_ov030_020bd004`: Storage exists; operational role unproved.

Physical definition [0x020bd004, 0x020bd020), 28 B (data). No canonical owner is established.

**Evidence and retained boundary:** Twenty-eight initialized zero bytes follow the 19-pointer scene-state table and precede BSS. The full-address and address|1 scan finds no literal in any domain; no computed reader within this fragment has been demonstrated.

**Next proof:** Bound all writes to the scene-state selector and all table-index consumers from the preceding table base. Determine whether the seven words are reachable handler slots, reserved storage or padding before naming; do not add NULL callbacks or delete the bytes.

**Sources:** [eu/src/ov030/data/Data_ov030_020bd004.c](../src/ov030/data/Data_ov030_020bd004.c).

### ov031:020bc815

`data_ov031_020bc815`: Storage exists; operational role unproved.

Physical definition [0x020bc815, 0x020bc820), 11 B (data). No canonical owner is established.

**Evidence and retained boundary:** Eleven initialized zero bytes follow the packed state table and its17 -byte zero suffix. The only raw 020bc815 word occurs in ov053, where 020bc814 is a Thumb function, Entity_ChangeSpecialState; this does not establish a reader in ov031.

**Next proof:** Bound native ov031 state-table indexing and any copied span from 020bc7b8, then identify a live reader/writer of the eleven physical bytes. The foreign function pointer is a separate bank-qualified code identity, not this DATA tail.

**Sources:** [eu/src/ov031/data/Data_ov031_020bc815.c](../src/ov031/data/Data_ov031_020bc815.c).

### ov033:020baafc

`data_ov033_020baafc`: Storage exists; operational role unproved.

Physical definition [0x020baafc, 0x020bab00), 4 B (bss). No canonical owner is established.

**Evidence and retained boundary:** Four-byte BSS tail after the 28 -byte native state block. The only raw reference is an ov001 call literal whose target is InstallOv029SceneHandlers in overlay029. No own-bank semantic access is demonstrated.

**Next proof:** Audit InitResumeModeContext/ShutdownResumeModeContext and every indexed span from 020baae0; if any reaches+0x1c, recover its field contract. Preserve the foreign029 callback binding separately; never assign callback semantics to this zero word.

**Sources:** [eu/src/overlays/ov033/data/bss/Bss_ov033_020baafc.c](../src/overlays/ov033/data/bss/Bss_ov033_020baafc.c).

### ov034:020beae0

`data_ov034_020beae0`: Foreign-bank binding remains unresolved.

Physical definition [0x020beae0, 0x020beb2c), 76 B (data). `gResultsStageItemTriplesPrefix` (named owner; logical span distinct from the physical definition); results-stage item-ID triples; logical span across physical definitions [0x020bea78, 0x020beb2c), 180 B; label offset +0x68; only 104 B belong to its first physical definition.

**Evidence and retained boundary:** The physical 76 -byte fragment continues the 104 -byte item-triple prefix at 020bea78; the two slices together end exactly at the separately referenced reward-pair base 020beb2c. SetupStageParams and InitResultsScene index three-byte item-ID rows by stage kind; a ROM stage kind59 reads the final row at base+177.

**Next proof:** Separate the foreign ov039 descriptor references by their loaded overlay IDs before renaming this token. Preserve the native 76 -byte fragment and do not inherit those descriptors or relabel the item IDs as colors.

**Sources:** [eu/src/ov034/data/Data_ov034_020beae0.c](../src/ov034/data/Data_ov034_020beae0.c), [eu/src/overlays/ov034/calls/SetupStageParams.c](../src/overlays/ov034/calls/SetupStageParams.c), [eu/src/overlays/ov034/calls/InitResultsScene.c](../src/overlays/ov034/calls/InitResultsScene.c), [eu/src/ov034/data/Data_ov034_020bea78.c](../src/ov034/data/Data_ov034_020bea78.c).

### ov034:020bee80

`data_ov034_020bee80`: Foreign-bank binding remains unresolved.

Physical definition [0x020bee80, 0x020bf6a0), 2080 B (data). No canonical owner is established.

**Evidence and retained boundary:** All complete-address/address|1 words found by this bounded scan occur in other overlay banks. The ov039 occurrences are registry fields whose own overlay ID establishes the logical descriptor bank; that ID does not name this physical blob/BSS object.

**Next proof:** Audit SetupStageParams and InitResultsScene indexed spans, original array/record bounds and any asset offset tables to identify the own-bank data role.

**Sources:** [eu/src/ov034/data/Data_ov034_020bee80.c](../src/ov034/data/Data_ov034_020bee80.c).

### ov034:020bf6a0

`data_ov034_020bf6a0`: Foreign-bank binding remains unresolved.

Physical definition [0x020bf6a0, 0x020bf990), 752 B (data). No canonical owner is established.

**Evidence and retained boundary:** All complete-address/address|1 words found by this bounded scan occur in other overlay banks. The ov039 occurrences are registry fields whose own overlay ID establishes the logical descriptor bank; that ID does not name this physical blob/BSS object.

**Next proof:** Audit SetupStageParams and InitResultsScene indexed spans, original array/record bounds and any asset offset tables to identify the own-bank data role.

**Sources:** [eu/src/ov034/data/Data_ov034_020bf6a0.c](../src/ov034/data/Data_ov034_020bf6a0.c).

### ov034:020bfca0

`data_ov034_020bfca0`: Foreign-bank binding remains unresolved.

Physical definition [0x020bfca0, 0x020bfda5), 261 B (data). `gResultsStageEntriesPrefix` (named owner; logical span distinct from the physical definition); results-stage entry stream; logical span across physical definitions [0x020bf990, 0x020c0ea8), 5400 B; label offset +0x310; only 2 B belong to its first physical definition.

**Evidence and retained boundary:** This261 -byte physical fragment lies at offset 0x310 of the 135-record40 -byte stage stream rooted at 020bf990. It splits records19..26; all27 group sentinels and the stream end 020c0ea8 are independently checked in ROM. Its ov039 same-address descriptor reference has another overlay owner.

**Next proof:** Keep the foreign primary-menu registry binding separate. Correct that alias to the actual loaded descriptor before a global token replacement. A stage-stream fragment name can then be applied without changing packed native relocation words.

**Sources:** [eu/src/ov034/data/Data_ov034_020bfca0.c](../src/ov034/data/Data_ov034_020bfca0.c), [eu/src/overlays/ov034/calls/SetupStageParams.c](../src/overlays/ov034/calls/SetupStageParams.c), [eu/src/overlays/ov034/calls/InitResultsScene.c](../src/overlays/ov034/calls/InitResultsScene.c), [eu/src/ov034/data/Data_ov034_020bf990.c](../src/ov034/data/Data_ov034_020bf990.c).

### ov036:020c33b0

`data_ov036_020c33b0`: Storage exists; operational role unproved.

Physical definition [0x020c33b0, 0x020c33b8), 8 B (rodata). No canonical owner is established.

**Evidence and retained boundary:** Two RO words {22,23}, indexed by screen and stored by OpenQueuedTextWindow at TextWindow+0x28. The local paletteBase name is unverified. The complete raw literal occurs only in that own-bank initializer.

**Next proof:** Identify the exact reader of TextWindow+0x28 across each active window type, including private/raw-offset views and draw callbacks. Trace the value to its actual API before calling it a palette, tile-table or layer ID.

**Sources:** [eu/src/ov036/data/Rodata_ov036_020c33b0.c](../src/ov036/data/Rodata_ov036_020c33b0.c).

### ov036:020c36b8

`data_ov036_020c36b8`: Storage exists; operational role unproved.

Physical definition [0x020c36b8, 0x020c36c0), 8 B (rodata). No canonical owner is established.

**Evidence and retained boundary:** Eight RO bytes {128,96}. OpenMessageTextWindowAlt copies them to a stack size view, sets request.size to that view and calls QueueMessageWindowKind3; the latter overwrites request.size with NULL before queuing. The all-domain scan finds only this wrapper literal.

**Next proof:** Find an independent reader or a route that preserves the size pointer before inferring an active geometry/default-window role. The native copy is real and must remain, but it does not affect the demonstrated queued request.

**Sources:** [eu/src/ov036/data/Rodata_ov036_020c36b8.c](../src/ov036/data/Rodata_ov036_020c36b8.c).

### ov036:020c36c0

`data_ov036_020c36c0`: Storage exists; operational role unproved.

Physical definition [0x020c36c0, 0x020c36c8), 8 B (rodata). No canonical owner is established.

**Evidence and retained boundary:** Eight RO bytes {128,96}. OpenMessageTextWindow copies the view and calls QueueMessageWindowKind2, which replaces request.size with NULL before QueueMessageWindow. The all-domain scan finds only the native wrapper literal.

**Next proof:** Require another reader or an independently proved intended template contract; do not call these active window dimensions merely from the copied fields. Preserve the bytes and native wrapper instructions.

**Sources:** [eu/src/ov036/data/Rodata_ov036_020c36c0.c](../src/ov036/data/Rodata_ov036_020c36c0.c).

### ov036:020c4014

`data_ov036_020c4014`: Foreign-bank binding remains unresolved.

Physical definition [0x020c4014, 0x020c4160), 332 B (bss). `gTextWindowStaticWorkPrefix` (named owner; logical span distinct from the physical definition); static text-window work; logical span across physical definitions [0x020c3950, 0x020ca204), 26804 B; label offset +0x6c4; only 1732 B belong to its first physical definition.

**Evidence and retained boundary:** The initialized gTextWindowResourceTable pointer targets 020c3950. Its constructor clears 0x68b4 bytes, through 020ca203 inclusive; the entire physical allocation falls inside that static text-window owner. Foreign ov039 descriptor references do not identify individual text-work fields.

**Next proof:** Repair each foreign registry/callback alias by its demonstrated overlay ID and active lifetime in a separate change. Then a storage-fragment name may describe the known text-window owner; recover readers/writers before assigning any field, callback, menu or resource role.

**Sources:** [eu/src/overlays/ov036/data/bss/Bss_ov036_020c4014.c](../src/overlays/ov036/data/bss/Bss_ov036_020c4014.c), [eu/src/overlays/ov036/data/tables/gTextWindowResourceTable.c](../src/overlays/ov036/data/tables/gTextWindowResourceTable.c), [eu/src/overlays/ov036/calls/InitTextWindowTask.c](../src/overlays/ov036/calls/InitTextWindowTask.c), [eu/src/overlays/ov036/data/bss/Bss_ov036_020c394c.c](../src/overlays/ov036/data/bss/Bss_ov036_020c394c.c).

### ov036:020c4160

`data_ov036_020c4160`: Foreign-bank binding remains unresolved.

Physical definition [0x020c4160, 0x020c4c60), 2816 B (bss). `gTextWindowStaticWorkPrefix` (named owner; logical span distinct from the physical definition); static text-window work; logical span across physical definitions [0x020c3950, 0x020ca204), 26804 B; label offset +0x810; only 1732 B belong to its first physical definition.

**Evidence and retained boundary:** The initialized gTextWindowResourceTable pointer targets 020c3950. Its constructor clears 0x68b4 bytes, through 020ca203 inclusive; the entire physical allocation falls inside that static text-window owner. Foreign ov039 descriptor references do not identify individual text-work fields.

**Next proof:** Repair each foreign registry/callback alias by its demonstrated overlay ID and active lifetime in a separate change. Then a storage-fragment name may describe the known text-window owner; recover readers/writers before assigning any field, callback, menu or resource role.

**Sources:** [eu/src/overlays/ov036/data/bss/Bss_ov036_020c4014.c](../src/overlays/ov036/data/bss/Bss_ov036_020c4014.c), [eu/src/overlays/ov036/data/tables/gTextWindowResourceTable.c](../src/overlays/ov036/data/tables/gTextWindowResourceTable.c), [eu/src/overlays/ov036/calls/InitTextWindowTask.c](../src/overlays/ov036/calls/InitTextWindowTask.c), [eu/src/overlays/ov036/data/bss/Bss_ov036_020c394c.c](../src/overlays/ov036/data/bss/Bss_ov036_020c394c.c).

### ov036:020c4c60

`data_ov036_020c4c60`: Foreign-bank binding remains unresolved.

Physical definition [0x020c4c60, 0x020c4fe0), 896 B (bss). `gTextWindowStaticWorkPrefix` (named owner; logical span distinct from the physical definition); static text-window work; logical span across physical definitions [0x020c3950, 0x020ca204), 26804 B; label offset +0x1310; only 1732 B belong to its first physical definition.

**Evidence and retained boundary:** The initialized gTextWindowResourceTable pointer targets 020c3950. Its constructor clears 0x68b4 bytes, through 020ca203 inclusive; the entire physical allocation falls inside that static text-window owner. Foreign ov039 descriptor references do not identify individual text-work fields.

**Next proof:** Repair each foreign registry/callback alias by its demonstrated overlay ID and active lifetime in a separate change. Then a storage-fragment name may describe the known text-window owner; recover readers/writers before assigning any field, callback, menu or resource role.

**Sources:** [eu/src/overlays/ov036/data/bss/Bss_ov036_020c4c60.c](../src/overlays/ov036/data/bss/Bss_ov036_020c4c60.c), [eu/src/overlays/ov036/data/tables/gTextWindowResourceTable.c](../src/overlays/ov036/data/tables/gTextWindowResourceTable.c), [eu/src/overlays/ov036/calls/InitTextWindowTask.c](../src/overlays/ov036/calls/InitTextWindowTask.c), [eu/src/overlays/ov036/data/bss/Bss_ov036_020c394c.c](../src/overlays/ov036/data/bss/Bss_ov036_020c394c.c).

### ov036:020c4fe0

`data_ov036_020c4fe0`: Foreign-bank binding remains unresolved.

Physical definition [0x020c4fe0, 0x020c59a0), 2496 B (bss). `gTextWindowStaticWorkPrefix` (named owner; logical span distinct from the physical definition); static text-window work; logical span across physical definitions [0x020c3950, 0x020ca204), 26804 B; label offset +0x1690; only 1732 B belong to its first physical definition.

**Evidence and retained boundary:** The initialized gTextWindowResourceTable pointer targets 020c3950. Its constructor clears 0x68b4 bytes, through 020ca203 inclusive; the entire physical allocation falls inside that static text-window owner. Foreign ov039 descriptor references do not identify individual text-work fields.

**Next proof:** Repair each foreign registry/callback alias by its demonstrated overlay ID and active lifetime in a separate change. Then a storage-fragment name may describe the known text-window owner; recover readers/writers before assigning any field, callback, menu or resource role.

**Sources:** [eu/src/overlays/ov036/data/bss/Bss_ov036_020c4c60.c](../src/overlays/ov036/data/bss/Bss_ov036_020c4c60.c), [eu/src/overlays/ov036/data/tables/gTextWindowResourceTable.c](../src/overlays/ov036/data/tables/gTextWindowResourceTable.c), [eu/src/overlays/ov036/calls/InitTextWindowTask.c](../src/overlays/ov036/calls/InitTextWindowTask.c), [eu/src/overlays/ov036/data/bss/Bss_ov036_020c394c.c](../src/overlays/ov036/data/bss/Bss_ov036_020c394c.c).

### ov036:020c59a0

`data_ov036_020c59a0`: Foreign-bank binding remains unresolved.

Physical definition [0x020c59a0, 0x020c5cc0), 800 B (bss). `gTextWindowStaticWorkPrefix` (named owner; logical span distinct from the physical definition); static text-window work; logical span across physical definitions [0x020c3950, 0x020ca204), 26804 B; label offset +0x2050; only 1732 B belong to its first physical definition.

**Evidence and retained boundary:** The initialized gTextWindowResourceTable pointer targets 020c3950. Its constructor clears 0x68b4 bytes, through 020ca203 inclusive; the entire physical allocation falls inside that static text-window owner. Foreign ov039 descriptor references do not identify individual text-work fields.

**Next proof:** Repair each foreign registry/callback alias by its demonstrated overlay ID and active lifetime in a separate change. Then a storage-fragment name may describe the known text-window owner; recover readers/writers before assigning any field, callback, menu or resource role.

**Sources:** [eu/src/overlays/ov036/data/bss/Bss_ov036_020c59a0.c](../src/overlays/ov036/data/bss/Bss_ov036_020c59a0.c), [eu/src/overlays/ov036/data/tables/gTextWindowResourceTable.c](../src/overlays/ov036/data/tables/gTextWindowResourceTable.c), [eu/src/overlays/ov036/calls/InitTextWindowTask.c](../src/overlays/ov036/calls/InitTextWindowTask.c), [eu/src/overlays/ov036/data/bss/Bss_ov036_020c394c.c](../src/overlays/ov036/data/bss/Bss_ov036_020c394c.c).

### ov036:020c5cc0

`data_ov036_020c5cc0`: Foreign-bank binding remains unresolved.

Physical definition [0x020c5cc0, 0x020c5da0), 224 B (bss). `gTextWindowStaticWorkPrefix` (named owner; logical span distinct from the physical definition); static text-window work; logical span across physical definitions [0x020c3950, 0x020ca204), 26804 B; label offset +0x2370; only 1732 B belong to its first physical definition.

**Evidence and retained boundary:** The initialized gTextWindowResourceTable pointer targets 020c3950. Its constructor clears 0x68b4 bytes, through 020ca203 inclusive; the entire physical allocation falls inside that static text-window owner. Foreign ov039 descriptor references do not identify individual text-work fields.

**Next proof:** Repair each foreign registry/callback alias by its demonstrated overlay ID and active lifetime in a separate change. Then a storage-fragment name may describe the known text-window owner; recover readers/writers before assigning any field, callback, menu or resource role.

**Sources:** [eu/src/overlays/ov036/data/bss/Bss_ov036_020c5cc0.c](../src/overlays/ov036/data/bss/Bss_ov036_020c5cc0.c), [eu/src/overlays/ov036/data/tables/gTextWindowResourceTable.c](../src/overlays/ov036/data/tables/gTextWindowResourceTable.c), [eu/src/overlays/ov036/calls/InitTextWindowTask.c](../src/overlays/ov036/calls/InitTextWindowTask.c), [eu/src/overlays/ov036/data/bss/Bss_ov036_020c394c.c](../src/overlays/ov036/data/bss/Bss_ov036_020c394c.c).

### ov036:020c5da0

`data_ov036_020c5da0`: Foreign-bank binding remains unresolved.

Physical definition [0x020c5da0, 0x020c7da0), 8192 B (bss). `gTextWindowStaticWorkPrefix` (named owner; logical span distinct from the physical definition); static text-window work; logical span across physical definitions [0x020c3950, 0x020ca204), 26804 B; label offset +0x2450; only 1732 B belong to its first physical definition.

**Evidence and retained boundary:** The initialized gTextWindowResourceTable pointer targets 020c3950. Its constructor clears 0x68b4 bytes, through 020ca203 inclusive; the entire physical allocation falls inside that static text-window owner. Foreign ov039 descriptor references do not identify individual text-work fields.

**Next proof:** Repair each foreign registry/callback alias by its demonstrated overlay ID and active lifetime in a separate change. Then a storage-fragment name may describe the known text-window owner; recover readers/writers before assigning any field, callback, menu or resource role.

**Sources:** [eu/src/overlays/ov036/data/bss/Bss_ov036_020c5cc0.c](../src/overlays/ov036/data/bss/Bss_ov036_020c5cc0.c), [eu/src/overlays/ov036/data/tables/gTextWindowResourceTable.c](../src/overlays/ov036/data/tables/gTextWindowResourceTable.c), [eu/src/overlays/ov036/calls/InitTextWindowTask.c](../src/overlays/ov036/calls/InitTextWindowTask.c), [eu/src/overlays/ov036/data/bss/Bss_ov036_020c394c.c](../src/overlays/ov036/data/bss/Bss_ov036_020c394c.c).

### ov036:020c7da0

`data_ov036_020c7da0`: Foreign-bank binding remains unresolved.

Physical definition [0x020c7da0, 0x020ca204), 9316 B (bss). `gTextWindowStaticWorkPrefix` (named owner; logical span distinct from the physical definition); static text-window work; logical span across physical definitions [0x020c3950, 0x020ca204), 26804 B; label offset +0x4450; only 1732 B belong to its first physical definition.

**Evidence and retained boundary:** The initialized gTextWindowResourceTable pointer targets 020c3950. Its constructor clears 0x68b4 bytes, through 020ca203 inclusive; the entire physical allocation falls inside that static text-window owner. Foreign ov039 descriptor references do not identify individual text-work fields.

**Next proof:** Repair each foreign registry/callback alias by its demonstrated overlay ID and active lifetime in a separate change. Then a storage-fragment name may describe the known text-window owner; recover readers/writers before assigning any field, callback, menu or resource role.

**Sources:** [eu/src/overlays/ov036/data/bss/Bss_ov036_020c5cc0.c](../src/overlays/ov036/data/bss/Bss_ov036_020c5cc0.c), [eu/src/overlays/ov036/data/tables/gTextWindowResourceTable.c](../src/overlays/ov036/data/tables/gTextWindowResourceTable.c), [eu/src/overlays/ov036/calls/InitTextWindowTask.c](../src/overlays/ov036/calls/InitTextWindowTask.c), [eu/src/overlays/ov036/data/bss/Bss_ov036_020c394c.c](../src/overlays/ov036/data/bss/Bss_ov036_020c394c.c).

## Overlays 041-104: 25 retained labels

### ov041:020cf700

`data_ov041_020cf700`: Storage exists; operational role unproved.

Physical definition [0x020cf700, 0x020cf710), 16 B (data(any)). No canonical owner is established.

**Evidence:** Four initialized u32 words {0x102,0,0x1ccd,1}; no consumer role is established.

**Retained because:** No matching-bank consumer, writer, relocation or exact raw address-word reference proves a descriptive storage role.

**Next proof:** Identify an own-bank access through address arithmetic/base+offset or a decoded/copied data use, then connect its operation and native range. Do not assign a role from values or adjacent tables alone.

**Sources:** [eu/src/overlays/ov041/data/Rodata_ov041_020cf6ac.c](../src/overlays/ov041/data/Rodata_ov041_020cf6ac.c).

### ov055:020d3f3d

`data_ov055_020d3f3d`: Own storage opaque; observed reference selects foreign code.

Physical definition [0x020d3f3d, 0x020d3f40), 3 B (bss). No canonical owner is established.

**Evidence:** Independent 3 -byte NOBITS object. No own-bank reader/writer established. The one raw word is a literal at ov021:020ad380 inside CreateScriptedEffectTask.

**Retained because:** The current constructor wrapper maps its pointer to UpdateSlotGroupEntries in ov056; metadata056 places that Thumb function at 020d3f3c. This foreign056 callback does not identify the physical 055 BSS object.

**Next proof:** Find an own-bank 055 data reader/writer or registered partial view. Do not repeat the resolved foreign056 callback hypothesis or name zero bytes as padding.

**Sources:** [eu/src/overlays/ov055/data/bss/Bss_ov055_020d3f3d.c](../src/overlays/ov055/data/bss/Bss_ov055_020d3f3d.c), [eu/src/overlays/ov021/calls/CreateScriptedEffectTask.c](../src/overlays/ov021/calls/CreateScriptedEffectTask.c).

### ov061:020d8569

`data_ov061_020d8569`: Own storage opaque; observed reference selects foreign code.

Physical definition [0x020d8569, 0x020d8580), 23 B (data(any)). No canonical owner is established.

**Evidence:** Independent 23 -byte all-zero DATA object with active source/ELF extent. Same address word occurs only at ov021:020b5054.

**Retained because:** The registry consumer loads overlay66; that word selects Thumb CreateOv066SceneObject at 066:020d8568, not these061/062 zero objects. No own-bank semantic consumer is established.

**Next proof:** Find own-bank data reader/writer or a caller whose selected overlay is061/062. The foreign066function alias must not supply a data name.

**Sources:** [eu/src/ov061/data/Data_ov061_020d8569.c](../src/ov061/data/Data_ov061_020d8569.c).

### ov062:020d8569

`data_ov062_020d8569`: Own storage opaque; observed reference selects foreign code.

Physical definition [0x020d8569, 0x020d8580), 23 B (data(any)). No canonical owner is established.

**Evidence:** Independent 23 -byte all-zero DATA object with active source/ELF extent. Same address word occurs only at ov021:020b5054.

**Retained because:** The registry consumer loads overlay66; that word selects Thumb CreateOv066SceneObject at 066:020d8568, not these061/062 zero objects. No own-bank semantic consumer is established.

**Next proof:** Find own-bank data reader/writer or a caller whose selected overlay is061/062. The foreign066function alias must not supply a data name.

**Sources:** [eu/src/ov062/data/Data_ov062_020d8569.c](../src/ov062/data/Data_ov062_020d8569.c).

### ov076:020cd404

`data_ov076_020cd404`: Interior/member metadata alias; no separate allocation.

No additional C/ELF allocation is proved for this numeric label. `gSlotMenuSharedState`; Shared menu state; colors[2] at +4; containing object [0x020cd400, 0x020cd40c), 12 B; label offset +0x4.

**Evidence:** Compile-time colors offset==4/sizeof==12 assertions; colors0=f2/colors1=fa and tagged-text callback context=parent.colors. Init/shutdown access the first word as menu pointer.

**Retained because:** Parent+4 colors[2] of active12 -byte NOBITS struct; no independent C/ELF object. Metadata-only descriptive alias suggested, no new storage.

**Next proof:** Metadata alias naming only if existing alias mechanism supports it. Do not generate C storage, change grouping or rebind address/addend. Main owner is renamed in the separate34-object plan.

**Sources:** [eu/src/overlays/ov076/calls/SlotMenu_DrawHintText.c](../src/overlays/ov076/calls/SlotMenu_DrawHintText.c).

### ov077:020ca3a4

`data_ov077_020ca3a4`: Interior/member metadata alias; no separate allocation.

No additional C/ELF allocation is proved for this numeric label. `gItemScreenSharedState`; Shared menu state; colors[2] at +4; containing object [0x020ca3a0, 0x020ca3ac), 12 B; label offset +0x4.

**Evidence:** Compile-time colors offset==4/sizeof==12 assertions; colors0=f2/colors1=fa and tagged-text callback context=parent.colors. Init/shutdown access the first word as menu pointer.

**Retained because:** Parent+4 colors[2] of active12 -byte NOBITS struct; no independent C/ELF object. Metadata-only descriptive alias suggested, no new storage.

**Next proof:** Metadata alias naming only if existing alias mechanism supports it. Do not generate C storage, change grouping or rebind address/addend. Main owner is renamed in the separate34-object plan.

**Sources:** [eu/src/overlays/ov077/calls/ItemScreen_DrawHintText.c](../src/overlays/ov077/calls/ItemScreen_DrawHintText.c).

### ov091:020c2a30

`data_ov091_020c2a30`: Storage exists; operational role unproved.

Physical definition [0x020c2a30, 0x020c2a34), 4 B (data(any)). No canonical owner is established.

**Evidence:** One const zero u32 word; no consumer role is established.

**Retained because:** No matching-bank consumer, writer, relocation or exact raw address-word reference proves a descriptive storage role.

**Next proof:** Identify an own-bank access through address arithmetic/base+offset or a decoded/copied data use, then connect its operation and native range. Do not assign a role from values or adjacent tables alone.

**Sources:** [eu/src/overlays/ov091/data/Rodata_ov091_020c2a30.c](../src/overlays/ov091/data/Rodata_ov091_020c2a30.c).

### ov101:020c1bc8

`data_ov101_020c1bc8`: Interior/member metadata alias; no separate allocation.

No additional C/ELF allocation is proved for this numeric label. `gPrimaryListSlotTemplates`; containing object [0x020c1b38, 0x020c1c58), 288 B; label offset +0x90.

**Evidence:** Interior at gPrimaryListSlotTemplates +0x90; record index 6, byte offset 0x0. No independent C/ELF storage definition.

**Retained because:** Interior to an existing named ELF object; no independent C definition. Preserve alias/address and physical array.

**Next proof:** Audit bank-qualified relocation/alias requirements and any actual field consumer before expressing a member/offset alias. Preserve the existing parent array and exact address; do not generate another allocation.

**Sources:** [eu/src/overlays/ov101/data/tables/gPrimaryListSlotTemplates.c](../src/overlays/ov101/data/tables/gPrimaryListSlotTemplates.c), [eu/src/overlays/ov101/ListSlotTemplate.h](../src/overlays/ov101/ListSlotTemplate.h).

### ov101:020c1c60

`data_ov101_020c1c60`: Interior/member metadata alias; no separate allocation.

No additional C/ELF allocation is proved for this numeric label. `gListEntryTextIndices`; containing object [0x020c1c58, 0x020c1d98), 320 B; label offset +0x8.

**Evidence:** Interior at gListEntryTextIndices +0x8; record index 1, byte offset 0x0. No independent C/ELF storage definition.

**Retained because:** Interior to an existing named ELF object; no independent C definition. Preserve alias/address and physical array.

**Next proof:** Audit bank-qualified relocation/alias requirements and any actual field consumer before expressing a member/offset alias. Preserve the existing parent array and exact address; do not generate another allocation.

**Sources:** [eu/src/overlays/ov101/data/tables/gListEntryTextIndices.c](../src/overlays/ov101/data/tables/gListEntryTextIndices.c), [eu/src/overlays/ov101/ListMenuData.h](../src/overlays/ov101/ListMenuData.h).

### ov101:020c1e61

`data_ov101_020c1e61`: Interior/member metadata alias; no separate allocation.

No additional C/ELF allocation is proved for this numeric label. `gSecondaryListSlotTemplates`; containing object [0x020c1d98, 0x020c1f78), 480 B; label offset +0xc9.

**Evidence:** Interior at gSecondaryListSlotTemplates +0xc9; record index 8, byte offset 0x9. No independent C/ELF storage definition.

**Retained because:** Interior to an existing named ELF object; no independent C definition. Preserve alias/address and physical array.

**Next proof:** Audit bank-qualified relocation/alias requirements and any actual field consumer before expressing a member/offset alias. Preserve the existing parent array and exact address; do not generate another allocation.

**Sources:** [eu/src/overlays/ov101/data/tables/gSecondaryListSlotTemplates.c](../src/overlays/ov101/data/tables/gSecondaryListSlotTemplates.c), [eu/src/overlays/ov101/ListSlotTemplate.h](../src/overlays/ov101/ListSlotTemplate.h).

### ov101:020c1ea0

`data_ov101_020c1ea0`: Interior/member metadata alias; no separate allocation.

No additional C/ELF allocation is proved for this numeric label. `gSecondaryListSlotTemplates`; containing object [0x020c1d98, 0x020c1f78), 480 B; label offset +0x108.

**Evidence:** Interior at gSecondaryListSlotTemplates +0x108; record index 11, byte offset 0x0. No independent C/ELF storage definition.

**Retained because:** Interior to an existing named ELF object; no independent C definition. Preserve alias/address and physical array.

**Next proof:** Audit bank-qualified relocation/alias requirements and any actual field consumer before expressing a member/offset alias. Preserve the existing parent array and exact address; do not generate another allocation.

**Sources:** [eu/src/overlays/ov101/data/tables/gSecondaryListSlotTemplates.c](../src/overlays/ov101/data/tables/gSecondaryListSlotTemplates.c), [eu/src/overlays/ov101/ListSlotTemplate.h](../src/overlays/ov101/ListSlotTemplate.h).

### ov101:020c2360

`data_ov101_020c2360`: Interior/member metadata alias; no separate allocation.

No additional C/ELF allocation is proved for this numeric label. `gListPortraitLayouts`; containing object [0x020c1f9c, 0x020c591c), 14720 B; label offset +0x3c4.

**Evidence:** Interior at gListPortraitLayouts +0x3c4; record index 2, byte offset 0xe4. No independent C/ELF storage definition.

**Retained because:** Interior to an existing named ELF object; no independent C definition. Preserve alias/address and physical array.

**Next proof:** Audit bank-qualified relocation/alias requirements and any actual field consumer before expressing a member/offset alias. Preserve the existing parent array and exact address; do not generate another allocation.

**Sources:** [eu/src/overlays/ov101/data/tables/gListPortraitLayouts.c](../src/overlays/ov101/data/tables/gListPortraitLayouts.c), [eu/src/overlays/ov101/ListPortraitLayout.h](../src/overlays/ov101/ListPortraitLayout.h).

### ov101:020c2368

`data_ov101_020c2368`: Interior/member metadata alias; no separate allocation.

No additional C/ELF allocation is proved for this numeric label. `gListPortraitLayouts`; containing object [0x020c1f9c, 0x020c591c), 14720 B; label offset +0x3cc.

**Evidence:** Interior at gListPortraitLayouts +0x3cc; record index 2, byte offset 0xec. No independent C/ELF storage definition.

**Retained because:** Interior to an existing named ELF object; no independent C definition. Preserve alias/address and physical array.

**Next proof:** Audit bank-qualified relocation/alias requirements and any actual field consumer before expressing a member/offset alias. Preserve the existing parent array and exact address; do not generate another allocation.

**Sources:** [eu/src/overlays/ov101/data/tables/gListPortraitLayouts.c](../src/overlays/ov101/data/tables/gListPortraitLayouts.c), [eu/src/overlays/ov101/ListPortraitLayout.h](../src/overlays/ov101/ListPortraitLayout.h).

### ov101:020c2380

`data_ov101_020c2380`: Interior/member metadata alias; no separate allocation.

No additional C/ELF allocation is proved for this numeric label. `gListPortraitLayouts`; containing object [0x020c1f9c, 0x020c591c), 14720 B; label offset +0x3e4.

**Evidence:** Interior at gListPortraitLayouts +0x3e4; record index 2, byte offset 0x104. No independent C/ELF storage definition.

**Retained because:** Interior to an existing named ELF object; no independent C definition. Preserve alias/address and physical array.

**Next proof:** Audit bank-qualified relocation/alias requirements and any actual field consumer before expressing a member/offset alias. Preserve the existing parent array and exact address; do not generate another allocation.

**Sources:** [eu/src/overlays/ov101/data/tables/gListPortraitLayouts.c](../src/overlays/ov101/data/tables/gListPortraitLayouts.c), [eu/src/overlays/ov101/ListPortraitLayout.h](../src/overlays/ov101/ListPortraitLayout.h).

### ov101:020c2b18

`data_ov101_020c2b18`: Interior/member metadata alias; no separate allocation.

No additional C/ELF allocation is proved for this numeric label. `gListPortraitLayouts`; containing object [0x020c1f9c, 0x020c591c), 14720 B; label offset +0xb7c.

**Evidence:** Interior at gListPortraitLayouts +0xb7c; record index 7, byte offset 0x16c. No independent C/ELF storage definition.

**Retained because:** Interior to an existing named ELF object; no independent C definition. Preserve alias/address and physical array.

**Next proof:** Audit bank-qualified relocation/alias requirements and any actual field consumer before expressing a member/offset alias. Preserve the existing parent array and exact address; do not generate another allocation.

**Sources:** [eu/src/overlays/ov101/data/tables/gListPortraitLayouts.c](../src/overlays/ov101/data/tables/gListPortraitLayouts.c), [eu/src/overlays/ov101/ListPortraitLayout.h](../src/overlays/ov101/ListPortraitLayout.h).

### ov101:020c2cc5

`data_ov101_020c2cc5`: Interior/member metadata alias; no separate allocation.

No additional C/ELF allocation is proved for this numeric label. `gListPortraitLayouts`; containing object [0x020c1f9c, 0x020c591c), 14720 B; label offset +0xd29.

**Evidence:** Interior at gListPortraitLayouts +0xd29; record index 9, byte offset 0x39. No independent C/ELF storage definition.

**Retained because:** Interior to an existing named ELF object; no independent C definition. Preserve alias/address and physical array.

**Next proof:** Audit bank-qualified relocation/alias requirements and any actual field consumer before expressing a member/offset alias. Preserve the existing parent array and exact address; do not generate another allocation.

**Sources:** [eu/src/overlays/ov101/data/tables/gListPortraitLayouts.c](../src/overlays/ov101/data/tables/gListPortraitLayouts.c), [eu/src/overlays/ov101/ListPortraitLayout.h](../src/overlays/ov101/ListPortraitLayout.h).

### ov101:020c2d41

`data_ov101_020c2d41`: Interior/member metadata alias; no separate allocation.

No additional C/ELF allocation is proved for this numeric label. `gListPortraitLayouts`; containing object [0x020c1f9c, 0x020c591c), 14720 B; label offset +0xda5.

**Evidence:** Interior at gListPortraitLayouts +0xda5; record index 9, byte offset 0xb5. No independent C/ELF storage definition.

**Retained because:** Interior to an existing named ELF object; no independent C definition. Preserve alias/address and physical array.

**Next proof:** Audit bank-qualified relocation/alias requirements and any actual field consumer before expressing a member/offset alias. Preserve the existing parent array and exact address; do not generate another allocation.

**Sources:** [eu/src/overlays/ov101/data/tables/gListPortraitLayouts.c](../src/overlays/ov101/data/tables/gListPortraitLayouts.c), [eu/src/overlays/ov101/ListPortraitLayout.h](../src/overlays/ov101/ListPortraitLayout.h).

### ov101:020c322d

`data_ov101_020c322d`: Interior/member metadata alias; no separate allocation.

No additional C/ELF allocation is proved for this numeric label. `gListPortraitLayouts`; containing object [0x020c1f9c, 0x020c591c), 14720 B; label offset +0x1291.

**Evidence:** Interior at gListPortraitLayouts +0x1291; record index 12, byte offset 0x151. No independent C/ELF storage definition.

**Retained because:** Interior to an existing named ELF object; no independent C definition. Preserve alias/address and physical array.

**Next proof:** Audit bank-qualified relocation/alias requirements and any actual field consumer before expressing a member/offset alias. Preserve the existing parent array and exact address; do not generate another allocation.

**Sources:** [eu/src/overlays/ov101/data/tables/gListPortraitLayouts.c](../src/overlays/ov101/data/tables/gListPortraitLayouts.c), [eu/src/overlays/ov101/ListPortraitLayout.h](../src/overlays/ov101/ListPortraitLayout.h).

### ov101:020c3275

`data_ov101_020c3275`: Interior/member metadata alias; no separate allocation.

No additional C/ELF allocation is proved for this numeric label. `gListPortraitLayouts`; containing object [0x020c1f9c, 0x020c591c), 14720 B; label offset +0x12d9.

**Evidence:** Interior at gListPortraitLayouts +0x12d9; record index 13, byte offset 0x29. No independent C/ELF storage definition.

**Retained because:** Interior to an existing named ELF object; no independent C definition. Preserve alias/address and physical array.

**Next proof:** Audit bank-qualified relocation/alias requirements and any actual field consumer before expressing a member/offset alias. Preserve the existing parent array and exact address; do not generate another allocation.

**Sources:** [eu/src/overlays/ov101/data/tables/gListPortraitLayouts.c](../src/overlays/ov101/data/tables/gListPortraitLayouts.c), [eu/src/overlays/ov101/ListPortraitLayout.h](../src/overlays/ov101/ListPortraitLayout.h).

### ov101:020c3500

`data_ov101_020c3500`: Interior/member metadata alias; no separate allocation.

No additional C/ELF allocation is proved for this numeric label. `gListPortraitLayouts`; containing object [0x020c1f9c, 0x020c591c), 14720 B; label offset +0x1564.

**Evidence:** Interior at gListPortraitLayouts +0x1564; record index 14, byte offset 0x144. No independent C/ELF storage definition.

**Retained because:** Interior to an existing named ELF object; no independent C definition. Preserve alias/address and physical array.

**Next proof:** Audit bank-qualified relocation/alias requirements and any actual field consumer before expressing a member/offset alias. Preserve the existing parent array and exact address; do not generate another allocation.

**Sources:** [eu/src/overlays/ov101/data/tables/gListPortraitLayouts.c](../src/overlays/ov101/data/tables/gListPortraitLayouts.c), [eu/src/overlays/ov101/ListPortraitLayout.h](../src/overlays/ov101/ListPortraitLayout.h).

### ov101:020c4014

`data_ov101_020c4014`: Interior/member metadata alias; no separate allocation.

No additional C/ELF allocation is proved for this numeric label. `gListPortraitLayouts`; containing object [0x020c1f9c, 0x020c591c), 14720 B; label offset +0x2078.

**Evidence:** Interior at gListPortraitLayouts +0x2078; record index 22, byte offset 0xd8. No independent C/ELF storage definition.

**Retained because:** Interior to an existing named ELF object; no independent C definition. Preserve alias/address and physical array.

**Next proof:** Audit bank-qualified relocation/alias requirements and any actual field consumer before expressing a member/offset alias. Preserve the existing parent array and exact address; do not generate another allocation.

**Sources:** [eu/src/overlays/ov101/data/tables/gListPortraitLayouts.c](../src/overlays/ov101/data/tables/gListPortraitLayouts.c), [eu/src/overlays/ov101/ListPortraitLayout.h](../src/overlays/ov101/ListPortraitLayout.h).

### ov101:020c4160

`data_ov101_020c4160`: Interior/member metadata alias; no separate allocation.

No additional C/ELF allocation is proved for this numeric label. `gListPortraitLayouts`; containing object [0x020c1f9c, 0x020c591c), 14720 B; label offset +0x21c4.

**Evidence:** Interior at gListPortraitLayouts +0x21c4; record index 23, byte offset 0xb4. No independent C/ELF storage definition.

**Retained because:** Interior to an existing named ELF object; no independent C definition. Preserve alias/address and physical array.

**Next proof:** Audit bank-qualified relocation/alias requirements and any actual field consumer before expressing a member/offset alias. Preserve the existing parent array and exact address; do not generate another allocation.

**Sources:** [eu/src/overlays/ov101/data/tables/gListPortraitLayouts.c](../src/overlays/ov101/data/tables/gListPortraitLayouts.c), [eu/src/overlays/ov101/ListPortraitLayout.h](../src/overlays/ov101/ListPortraitLayout.h).

### ov101:020c4c60

`data_ov101_020c4c60`: Interior/member metadata alias; no separate allocation.

No additional C/ELF allocation is proved for this numeric label. `gListPortraitLayouts`; containing object [0x020c1f9c, 0x020c591c), 14720 B; label offset +0x2cc4.

**Evidence:** Interior at gListPortraitLayouts +0x2cc4; record index 31, byte offset 0x34. No independent C/ELF storage definition.

**Retained because:** Interior to an existing named ELF object; no independent C definition. Preserve alias/address and physical array.

**Next proof:** Audit bank-qualified relocation/alias requirements and any actual field consumer before expressing a member/offset alias. Preserve the existing parent array and exact address; do not generate another allocation.

**Sources:** [eu/src/overlays/ov101/data/tables/gListPortraitLayouts.c](../src/overlays/ov101/data/tables/gListPortraitLayouts.c), [eu/src/overlays/ov101/ListPortraitLayout.h](../src/overlays/ov101/ListPortraitLayout.h).

### ov101:020c4fe0

`data_ov101_020c4fe0`: Interior/member metadata alias; no separate allocation.

No additional C/ELF allocation is proved for this numeric label. `gListPortraitLayouts`; containing object [0x020c1f9c, 0x020c591c), 14720 B; label offset +0x3044.

**Evidence:** Interior at gListPortraitLayouts +0x3044; record index 33, byte offset 0xd4. No independent C/ELF storage definition.

**Retained because:** Interior to an existing named ELF object; no independent C definition. Preserve alias/address and physical array.

**Next proof:** Audit bank-qualified relocation/alias requirements and any actual field consumer before expressing a member/offset alias. Preserve the existing parent array and exact address; do not generate another allocation.

**Sources:** [eu/src/overlays/ov101/data/tables/gListPortraitLayouts.c](../src/overlays/ov101/data/tables/gListPortraitLayouts.c), [eu/src/overlays/ov101/ListPortraitLayout.h](../src/overlays/ov101/ListPortraitLayout.h).

### ov104:020d3744

`data_ov104_020d3744`: Interior/member metadata alias; no separate allocation.

No additional C/ELF allocation is proved for this numeric label. `DSProt_BSS`; containing object [0x020d3740, 0x020d3760), 32 B; label offset +0x4.

**Evidence:** Metadata label at DSProt_BSS+4, inside the existing 32 -byte NOBITS object; no independent C/ELF symbol.

**Retained because:** No own-field reader/writer is established. Existing encryption/decoder code uses DSProt_BSS as an address-encoding basis, which does not identify a field at+4.

**Next proof:** Trace a decoded instruction or owned address-arithmetic reference accessing this byte/word. Do not generate storage or call it a key/state field from proximity.

**Sources:** [eu/src/overlays/ov104/DSProt-Extra.c](../src/overlays/ov104/DSProt-Extra.c).

## Integration boundary

This ledger records evidence and missing proof. It authorizes no allocation
merge, fragment removal, bank rebinding, alias deletion or type change. Any
later source/configuration cleanup must preserve the native layout and offsets
and pass the repository's actual-path verification and official linked gate.
Existing canonical aliases should be resolved through their demonstrated owner
and relocation requirements, rather than adding another competing declaration.
