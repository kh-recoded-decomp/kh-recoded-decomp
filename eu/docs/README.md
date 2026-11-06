# EU source and porting documentation

EU ARM9 reconstruction covers all 108 native modules byte-exact. Matching,
descriptive names, recovered layouts and portable interfaces are separate
claims. This index groups contracts by system; it does not move source files
or replace native overlay ownership.

Begin with the [source-tree map](SOURCE_LAYOUT.md), then the
[porting guide](PORTING_GUIDE.md) and [progress policy](PROGRESS_POLICY.md).
Read the EU wrapper, its shared regional body and the relevant owner/consumer
contract together.

## Systems

| Area | Native entrypoints | Contracts |
|---|---|---|
| Engine, tasks and resource services | Main/autoloads; EU wrappers in `eu/src/calls/` | [Engine services](ENGINE_SERVICE_HELPERS.md), [display lists](DISPLAY_OBJECT_LIST_UPDATE_CONTRACTS.md), [task DATA owners](SCENE_TASK_DATA_OWNERS.md), [file loader](FILE_LOADER.md), [load queue](FILE_LOAD_QUEUE.md) |
| Collision and geometry | Main/ITCM and their configured callers | [Geometry](COLLISION_GEOMETRY.md), [traversal](COLLISION_TRAVERSAL.md), [contact motion](CONTACT_MOTION.md), [sphere/rim sweep](SPHERE_RIM.md), [scene-group callbacks](SCENE_GROUP_CONTACT_CONTRACT.md) |
| Field session, actors and HUD | Common overlay 001 services and their actual scene callers | [Actor/contact ownership](FIELD_ACTOR_TARGET_PERMISSION_CONTRACTS.md), [HUD/menu/minigame](FIELD_HUD_MENU_MINIGAME_POOL_CONTRACTS.md), [resource/VM callbacks](FIELD_VM_CALLBACK_RESOURCE_CONTRACTS.md), [global storage](FIELD_SESSION_GLOBAL_DATA_CONTRACTS.md), [session buffers](SESSION_BUFFERS.md), [actor HP restoration](ACTOR_HEALTH_RESTORATION.md) |
| Scripts and commands | Main VM, overlay 001 and the separate stage-script interfaces | [Field delegates](FIELD_SCRIPT_DELEGATES.md), [stage services](STAGE_SCRIPT_CAMERA_TASK_SERVICE_CONTRACTS.md), [effect action selectors](SCRIPTED_EFFECT_ACTION_SELECTOR_CONTRACT.md), [scene/member consumers](SCENE_MEMBER_TRACKER_SCRIPT_CONTRACTS.md) |
| Field objects | Class owners in overlays 001/007-011; separate pools in 016-020 | [Class callbacks](FIELD_CLASS_CALLBACK_CONTRACTS.md), [kind/pose](FIELD_OBJECT_KIND_POSE_CONTRACTS.md), [pool requests](FIELD_POOL_REQUEST_CONTRACTS.md), [panel/state callbacks](FIELD_STATE_PANEL_CALLBACK_CONTRACTS.md) |
| Scene lifecycle | Individually identified owners in overlays 028-040 | [Field scenes](GROUP_FIELD_SCENE_CONTRACTS.md), [resume](RESUME_MODE_LIFECYCLE_CONTRACTS.md), [results](RESULTS_SCREEN_NATIVE_HELPER_CONTRACTS.md), [area scenes](AREA_SCENE_DEFINITION_FADE_GAUGE_CONTRACTS.md), [continue](CONTINUE_SCENE_LIFECYCLE_CONTRACTS.md) |
| Menus, panels and text | The descriptor's actual overlay bank and task owner | [Navigation/state](MENU_STATE_NAVIGATION_HELPERS.md), [panel/wireless slots](PANEL_WIRELESS_CALLBACK_CONTRACTS.md), [text windows](EVENT2D_PANEL_TEXT_WINDOW_CONTRACTS.md), [menu phases](MENU_PHASE_SUBOVERLAY_TEXT_CONTRACTS.md), [DATA registries](MENU_DATA_REGISTRIES_DESCRIPTORS.md) |
| Wireless | Overlay 015 helper, menu, board and connection owners | [Wireless helpers](WIRELESS_MENU_HELPER_CONTRACTS.md), [native WM boundary](library/sdk_wh.md), [reward result/interface](WIRELESS_REWARD_INTERFACE.md), [tables and state storage](WIRELESS_TABLES_STATE_STORAGE.md) |
| Movie and captions | The movie scene and decoder/caption owners have separate lifetimes | [Caption/decoder contracts](MOVIE_CAPTION_DECODER_CONTRACTS.md) |
| Cameras and model animation | The configured scene/camera bank and its callers | [Camera helpers](CAMERA_HELPER_CONTRACTS.md), [request hooks](CAMERA_REQUEST_GAUGE_HOOK_CONTRACTS.md), [saved camera](SAVED_CAMERA.md), [animation tracks](MODEL_ANIMATION_TRACKS.md), [model ownership](MODEL_RESOURCE_OWNERSHIP.md) |
| Libraries and platform adapters | Native library entrypoints and verified models | [Library boundaries](PORTING_GUIDE.md#library-boundaries), [portable references](../portable/README.md) |

Source locations in the table describe entrypoints, not a promise that each
entire overlay implements only one system. Follow the source map for actual
build ownership and regional aliases. [SYMBOL_EVIDENCE.md](SYMBOL_EVIDENCE.md)
links the complete sequence of documented naming blocks.

## Contracts by subsystem

### Field session and scene lifecycle

- [Session phase and script run mask](FIELD_SESSION_PHASE_RUN_MASK.md): the
  lifecycle dispatcher word and the distinct script flag bits.
- [Current field entry storage](FIELD_CURRENT_ENTRY_STORAGE.md) and
  [script binding indices](FIELD_SCRIPT_BINDING_INDICES.md): actual writers,
  signed getters and the limits of the native container slots.
- [Scene-entry and menu policy](FIELD_SCENE_MENU_POLICY.md),
  [results-session handoff](RESULTS_SESSION_HANDOFF.md) and
  [scene-4 exit request](FIELD_SCRIPT_SCENE4_EXIT.md): preserve request ordering,
  outcome words and numeric dispatcher identities without inventing an enum.
- [Scene-transition hooks](FIELD_SCENE_TRANSITION_HOOK.md) and
  [the actor-scene handoff](ACTOR_SCENE_FIELD_HANDOFF.md): loaded callback
  ownership, native continuations and the field entries that remain paused.

### Actors, field objects and combat

- [Class activation, LOD and command selection](FIELD_OBJECT_CLASS_ACTIVATION_LOD_COMMANDS.md)
  and [the default stage-actor descriptor](DEFAULT_STAGE_ACTOR_DESCRIPTOR.md):
  proved class layout and init/update/draw channels.
- [Default actor hooks and body sound](DEFAULT_STAGE_ACTOR_BODY_SOUND.md),
  [managed-actor and patrol policies](FIELD_ACTOR_EVENT_POLICY.md) and
  [controller release states](ACTOR_CONTROLLER_RELEASE_STATES.md): exact owners,
  masks, signed header fields and lifecycle transitions.
- [The jump-step override hook](ACTOR_JUMP_STEP_OVERRIDE.md) and
  [entry-pool drawing and actor-owner links](ENTRY_POOL_DRAW_OWNER_CONTRACTS.md):
  actual registrations, callers and callback return handling.
- [Event combat values](STAGE_EVENT_COMBAT_VALUES.md) and
  [reaction/countdown values](STAGE_EVENT_REACTION_COUNTDOWN.md): constructors,
  damage consumers, rounding and fields whose units remain bounded by evidence.

### Stage scripts and effect services

- [Stage idle callbacks](STAGE_IDLE_CALLBACK_CONTRACTS.md),
  [timed event cues](STAGE_EVENT_TIMED_CUE_GROUP.md),
  [event effect kind](STAGE_EVENT_EFFECT_KIND.md) and
  [current override ID](STAGE_CURRENT_OVERRIDE_ID.md): distinct service owners,
  callback protocols and numeric selector domains.
- [Launcher emission](CARRIED_LAUNCHER_EMISSION.md),
  [shared stage workspace](STAGE_SHARED_WORKSPACE.md) and
  [operand and marker operations](STAGE_OPERAND_MARKER_COMMANDS.md): actual
  producers and consumers, including reused workspace lifetimes.
- [Resource-ID predicate](STAGE_RESOURCE_ID_PREDICATE.md): the complete native
  membership test, without assigning an unproved gameplay resource family.

### VM commands and callback phases

- [Interface callback phases](FIELD_CALLBACK_PHASE_CONTRACTS.md) and
  [operational field callbacks and commands](FIELD_OPERATIONAL_CALLBACKS_COMMANDS.md):
  the observed draw phase, panel table slot and VM run-result protocol.
- [Field command 3 and the word-payload hook](FIELD_NOOP3_PAYLOAD.md): distinct
  nonnull no-ops, immediate buffer borrowing and erased native declarations.
- [Session byte +0x27b6 bit 5](SESSION_BYTE27B6_BIT5_SCRIPT.md): the exact byte
  store and opcode binding; the meaning of the bit remains unknown.

Opcode numbers, literal run results, bit positions and table slots are
operational contracts. They do not establish original source names, a reserved
feature or a gameplay purpose. In particular, MAIN and auxiliary run-zero
behavior must remain distinct; an empty registered callback is not automatically
equivalent to a null pointer.

### Cameras, motion and models

- [Stored field camera requests](FIELD_CAMERA_MODE_REQUEST.md): deferred byte
  application and the different native camera backends.
- [Conditional camera-offset wait](FIELD_CAMERA_OFFSET_WAIT.md) and
  [the exact HP/camera gate](FIELD_HP_CAMERA_SCRIPT_GATE.md): state 4, the shared
  collider-offset vector, wait completion and HP-dependent flag effects.
- [Motion-position callbacks](STAGE_MOTION_POSITION_CALLBACKS.md) and
  [current motion-record word 6](STAGE_MOTION_RECORD_WORD6.md): the proved native
  record extent and raw zero-based word at +0x18, without a property or unit claim.
- [Scene scroll speed](FIELD_SCRIPT_SCROLL_SPEED.md),
  [camera-goal snapping](CAMERA_GOAL_SNAP.md),
  [stage-local brightness](STAGE_BRIGHTNESS_FADE.md) and
  [model drawing gate](MODEL_SET_DRAW_GATE.md): exact state and update consumers.

### Menus, records and messages

- [Current board-node code](CURRENT_BOARD_NODE_CODE.md): the shared session
  buffer, constructors, per-node writers and signed getter.
- [Field menu/message operations](FIELD_MENU_MESSAGE_OPERATIONS.md),
  [SubScene9 request availability](SUBSCENE9_REQUEST_CONTRACT.md) and
  [common field message sprites](COMMON_FIELD_MESSAGE_SPRITE_WAIT.md): separate
  owners, message state and scheduling results.
- [Actor-scene continuation and record-panel progress](ACTOR_TASK_RECORD_PROGRESS_CONTRACTS.md):
  the native task continuation and the progress/index threshold whose clamp
  does not establish percentage units.

## Native data maps

These maps connect each native object to its actual writers and consumers.
Physical definitions, interior aliases and logical multi-fragment owners
remain distinct. Use the system group to browse; native overlay IDs and
configured source paths still establish build ownership.

### Core contexts and platform

- [Callback lists, scene task descriptors and static selection tables](NATIVE_STATIC_OWNER_TABLES12.md).
- [Card, sound-player and stage-script native DATA views](NATIVE_SDK_SCRIPT_VIEWS9.md).
- [Cartridge, heap registry and G3D cache DATA](NATIVE_CARTRIDGE_G3D17.md).
- [early overlay data contracts](EARLY_CONTEXT_CONSTANT_DATA.md).
- [Engine service DATA owners](NATIVE_ENGINE_SERVICES16.md).
- [GX VRAM assignment fields and thread-info continuation](NATIVE_VRAM_THREAD7.md).
- [IRQ callback and wireless notification DATA](NATIVE_IRQ_WIRELESS11.md).
- [Native exception-handler DATA views](NATIVE_EXCEPTION_HANDLER_VIEWS2.md).
- [Native runtime views and handoff DATA](NATIVE_NATIVE_RUNTIME_VIEWS7.md).
- [OS launcher thread, arena heap records and WM command buffers](NATIVE_OS_WIRELESS6.md).
- [Render, IRQ, sound and stage resource DATA](NATIVE_RENDER_STAGE13.md).
- [Runtime task, heap, input and profile DATA](NATIVE_RUNTIME13.md).
- [Save, model and collision DATA owners](NATIVE_SAVE_RENDER_STATE10.md).
- [Scene task descriptors, handles and work globals](SCENE_TASK_DATA_OWNERS.md).
- [Selection header, saved slots and tagged-entry DATA](NATIVE_SELECTION_SLOTS_TAGS8.md).
- [Sound command pool partitions and shared work](NATIVE_SOUND_POOL_SHARED4.md).

### Field, actors and cameras

- [Actor resources and scene parameters](ACTOR_SCENE_PARAMETER_DATA.md).
- [Battle-gauge, actor resource and effect DATA](GAUGE_ACTOR_EFFECT_DATA.md).
- [Field combat tables and hit geometry DATA](NATIVE_FIELD_COMBAT_TABLES13.md).
- [kind-4 pool trigger-hit callback table](POOL_KIND4_TRIGGER_CALLBACKS.md).
- [Level-growth table native spans and unresolved attribute columns](NATIVE_LEVEL_GROWTH_SPANS3.md).
- [ov001 service and UI state owners](FIELD_SESSION_GLOBAL_DATA_CONTRACTS.md).
- [Overlay058 scene resources and inline storage](OVERLAY058_SCENE_NATIVE_STORAGE.md).
- [Stage-command and camera storage views](STAGE_CAMERA_NATIVE_STORAGE.md).

### Menus, results and records

- [Additional menu descriptor and record-statistic DATA](MENU_DESCRIPTOR_RECORD_TABLES.md).
- [Board, group and continue-menu DATA](NATIVE_BOARD_GROUP_CONTINUE18.md).
- [Drift, actor, record-group and carousel data](DRIFT_ACTOR_RECORD_CAROUSEL_DATA.md).
- [Map and board screen configuration DATA](NATIVE_MAP_BOARD_CONFIGS9.md).
- [Matrix drawing and refresh DATA](MATRIX_DRAW_REFRESH_DATA.md).
- [Menu and field configuration DATA](NATIVE_MENU_STAGE_CONFIGS12.md).
- [Menu DATA registries, descriptors and state tables](MENU_DATA_REGISTRIES_DESCRIPTORS.md).
- [Menu layout, widget and text templates](MENU_LAYOUT_TEMPLATE_DATA.md).
- [Menu numeric and text format DATA](MENU_TEXT_FORMAT_DATA_CONTRACTS.md).
- [Menu, actor and camera global storage](LATE_SCENE_GLOBAL_STORAGE.md).
- [Menu-list and overlay display configuration DATA](NATIVE_LIST_DISPLAY_CONFIGS9.md).
- [Overlay 087 carousel and choice data](OVERLAY087_CAROUSEL_CHOICE_DATA.md).
- [Report progress data contracts](REPORT_PROGRESS_RECORD_DATA.md).
- [Report UI and popup data contracts](REPORT_UI_POPUP_NATIVE_STORAGE.md).
- [Report, page-menu and gauge DATA](REPORT_PAGE_SCENE_DATA.md).
- [Results UI and shared shop DATA](NATIVE_RESULTS_UI17.md).
- [Slot and item menu DATA contracts](SLOT_ITEM_NATIVE_TEMPLATE_DATA.md).
- [title and panel data contracts](TITLE_PANEL_DATA_CONTRACTS.md).
- [Tracker tiles, results-stage data and text/model storage](NATIVE_STAGE_TRACKER_VIEWS15.md).

### Movie and text

- [Event panel and text-window DATA contracts](NATIVE_EVENT_TEXT_WINDOW25.md).
- [Movie DATA and skip prompts](NATIVE_MOVIE20.md).

### Wireless

- [wireless menu tables and state storage](WIRELESS_TABLES_STATE_STORAGE.md).
- [wireless scan and board storage](WIRELESS_SCAN_BOARD_STORAGE.md).

### References across banks

- [Native references across overlay banks](BANK_QUALIFIED_OWNER_BINDINGS.md).

## Retained DATA identities

[All 81 retained numeric DATA labels](EU_PENDING_DATA_LABELS.md) have an explicit
owner or missing-proof record. The reviewed domain accounts for all 941
identities: 835 original supported naming assignments, 25 closed normalizations
and 81 retained labels. The normalizations comprise three canonical duplicates,
one existing backing-storage naming and twenty-one retired interior aliases.
These counts describe reviewed identities, not new C allocations or a claim
that unknown interior fields have acquired semantic names.

[Storage/view naming](CANONICAL_DATA_ALIAS_NORMALIZATION.md),
[canonical base/addend references](INTERIOR_DATA_ALIAS_NORMALIZATION.md) and
[unused absolute interior aliases](UNUSED_ABSOLUTE_INTERIOR_ALIASES.md) record
the precise representations, preserved allocations and remaining ambiguous
banks. The rejected active-field-context coalescence and the retained ov004
interpretation remain evidence limits.

## Unresolved function contracts

Seven byte-exact C functions retain numeric identities: one MAIN engine helper
and six callbacks. The [field review](EU_PENDING_FIELD_FUNCTIONS.md) has no
remaining numeric field function; its operational closures still document
unknown meanings and native interface limits.

- [One engine/helper contract](EU_PENDING_ENGINE_SCENE_FUNCTIONS.md) and
  [the optional-target evidence limit](MAIN_OPTIONAL_TARGET_EVIDENCE_LIMITS.md):
  preserve the conditional target write without inventing an owner or writer.
- [Six background/camera/other callbacks](EU_PENDING_CALLBACK_FUNCTIONS.md),
  [background callback reader limits](BACKGROUND_CALLBACK_EVIDENCE_LIMITS.md) and
  [overlay 044 reference limits](OV044_REFERENCE_EVIDENCE_LIMITS.md): distinguish
  mechanical output, registration, invocation and unresolved field roles.

These are limits on recovered meaning, not additional unmatched code. An
operationally named function can still expose an opaque word, ID range, bit or
callback ABI. Absence of a direct reference does not establish that an object
or function is unused; bank-qualified ownership and the documented search
limits remain part of the handoff.

## Validation and native reference binding

Use the [standalone relocation history](DATA_NATIVE_RELOCATION_BASELINE.md),
[native metadata refresh](NATIVE_RELOCATION_METADATA.md) and
[named callback/key references](NATIVE_CALLBACK_REFERENCE_CONTRACTS.md) for
their exact original controls and offsets. Their historical cases are distinct
from later source naming and metadata-classification work.

[Callback bank binding](NATIVE_CALLBACK_BANK_BINDING.md) follows the actual
overlay loader. [Local Thumb branch metadata](LOCAL_THUMB_BRANCH_METADATA.md)
records the separate native branch/label classification evidence. Keep these
bank and instruction facts separate from a semantic name or a looser matching
rule. The [evidence log](SYMBOL_EVIDENCE.md) retains the published naming history.

## Reading native types for a port

Use field owners, constructor/writer evidence, callback registration and real
consumers together. A native `u32` can carry an encoded DS address; an interior
label can lie inside a larger allocation; an empty callback can preserve a
residual return register. Preserve documented rounding, overflow, raw masks,
borrowed lifetimes and partial clears before selecting host types.

Shared headers should collect layouts proved for this game. Per-function
partial views, erased callback declarations and the Days reference remain
evidence to reconcile, rather than automatic host declarations. The
[porting guide](PORTING_GUIDE.md) describes platform adapters and validation.
The [source-tree map](SOURCE_LAYOUT.md) preserves native bank ownership,
regional wrappers and the active semantic index without a wholesale folder move.
