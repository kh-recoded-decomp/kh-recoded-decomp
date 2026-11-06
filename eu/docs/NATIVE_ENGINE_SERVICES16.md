# Engine service DATA owners (EU)

Review source baseline: `28dc258674c86cde06bc8456c4c7cb9087e28905`. Native source paths and physical storage remain unchanged; the integration results are recorded below.

## Native storage partitions

Several native APIs use a view anchored at one symbol to access its neighbors. The 32-bit and 64-bit RNG states remain separate 12-byte and 24-byte objects. Pad sampling has a six-byte view across held/previous and pressed storage. Brightness APIs address the mask, cached signed bytes and clamp modes from one base. Sound initialization reaches its reply ring through the preceding queue-state struct. These are evidence about addresses and consumers, not permission to merge allocations, change declarations or publish these views as portable headers.

## Inventory and contracts

### `main:020604d8` → `gSharedRandom32State`

Previous label `data_020604d8`; existing ELF size **12 bytes**. Defining source: `eu/src/data/bss/Bss_main_020604d8.c`.

12-byte BSS object: u32 current state at +0, multiplier at +4, increment at +8.

InitRandomFromEntropy initializes this three-word state independently of the adjacent 64-bit state. NextSharedRandom16Scaled computes state = multiplier*state + increment with unsigned word arithmetic; range zero returns the high 16 bits, otherwise the scaled high product is narrowed to u16.

Limits: SeedSharedRandomState and nextRandom12 use a larger legacy view anchored here that crosses into the next symbol. Rename only; do not turn that view into a claim that this ELF symbol includes the neighbor. Entropy mixing has native uninitialized local inputs; naming does not repair or endorse that implementation for a port.

Pinned EU source/consumer references:

- `eu/src/calls/InitRandomFromEntropy.c` → `src/arm9/random_number_generation/InitRandomFromEntropy_02029ad8.c`; reference line(s) 15, 48.
- `eu/src/calls/NextSharedRandom16Scaled.c`; reference line(s) 4, 6.
- `eu/src/calls/SeedSharedRandomState.c` → `src/arm9/runtime_data_utilities/SeedSharedRandomState_0202a984.c`; reference line(s) 1, 4, 5, 6, 7, 8, 9, 10, 11, 12.
- `eu/src/calls/nextRandom12.c` → `src/arm9/random_number_generation/nextRandom12_0202aa58.c`; reference line(s) 8, 12.
- `eu/src/calls/random_next_scaled.c` → `src/arm9/graphics/random_next_scaled_0202aa04.c`; reference line(s) 8, 12.
- `eu/src/data/bss/Bss_main_020604d8.c`; reference line(s) 4.

### `main:020604e4` → `gSharedRandom64State`

Previous label `data_020604e4`; existing ELF size **24 bytes**. Defining source: `eu/src/data/bss/Bss_main_020604d8.c`.

24-byte BSS object: u64 current state, multiplier and increment, each occupying eight bytes in the native representation.

InitRandomFromEntropy uses an explicit RandContext64 view and initializes multiplier 0x5d588b656c078965 and increment 0x269ec3. SeedSharedRandomState reaches these same six words as indices 3..8 from the preceding 32-bit state; nextRandom12 updates this state through its +0xc larger view.

Limits: Preserve the split 12-byte/24-byte symbols and native alignment. nextRandom12 returns the top twelve bits of the updated 64-bit state. Neither global is thread local or cryptographic.

Pinned EU source/consumer references:

- `eu/src/calls/InitRandomFromEntropy.c` → `src/arm9/random_number_generation/InitRandomFromEntropy_02029ad8.c`; reference line(s) 16, 47.
- `eu/src/data/bss/Bss_main_020604d8.c`; reference line(s) 3.

### `main:020604fc` → `gPadHeldAndPrevious`

Previous label `data_020604fc`; existing ELF size **4 bytes**. Defining source: `eu/src/data/bss/Bss_main_020604fc.c`.

4-byte BSS object: u16 held at +0 and u16 previous at +2.

Pad_Sample copies held to previous, samples hardware, stores held, and writes pressed through its six-byte PadState view. ResetPadSampleState clears held/previous and the adjacent pressed halfword. UpdateKeyRepeat and input consumers read the low held halfword.

Limits: The native six-byte view crosses into the separate pressed-storage symbol at 02060500. Keep object boundaries and all existing declarations; this is not a new portable PadState allocation.

Pinned EU source/consumer references:

- `eu/src/calls/Pad_Sample.c` → `src/arm9/input_history/Pad_Sample_0202abc8.c`; reference line(s) 9, 21, 28, 29, 30, 31.
- `eu/src/calls/ResetPadSampleState.c` → `src/arm9/core_small/func_0202aba8.c`; reference line(s) 3, 8, 9, 10.
- `eu/src/calls/UpdateKeyRepeat.c`; reference line(s) 10, 31.
- `eu/src/data/bss/Bss_main_020604fc.c`; reference line(s) 3.
- `eu/src/overlays/ov000/calls/UpdatePanelInputWithTimeout.c` → `src/ov000/panel_state/UpdatePanelInputWithTimeout_02062838.c`; reference line(s) 14, 34.
- `eu/src/overlays/ov001/calls/HandleShoulderLockOn.c` → `src/ov001/shared_engine/HandleShoulderLockOn_0206bd30.c`; reference line(s) 10, 23.
- `eu/src/overlays/ov001/calls/HandleSideTargetButtons.c`; reference line(s) 39, 56.
- `eu/src/overlays/ov013/calls/UpdatePanelScrollState.c` → `src/ov013/panel_state/UpdatePanelScrollState_02071b6c.c`; reference line(s) 65, 176.
- `eu/src/overlays/ov014/calls/UpdatePanelEditInput.c` → `src/ov014/panel_state/UpdatePanelEditInput_0206d2e8.c`; reference line(s) 84, 157.
- `eu/src/overlays/ov021/calls/RefreshInputState.c` → `src/ov021/unclassified_helpers/RefreshInputState_020a6edc.c`; reference line(s) 17, 27.
- `eu/src/overlays/ov027/calls/MoveFocusByDpad.c` → `src/ov027/resource_container/MoveFocusByDpad_020b88c0.c`; reference line(s) 34, 49.
- `eu/src/overlays/ov039/calls/HandleListKeyInput.c` → `src/ov039/input/HandleListKeyInput_020bdc28.c`; reference line(s) 21, 41.
- `eu/src/overlays/ov039/calls/UpdateOverlayFrame.c` → `src/ov039/overlay_lifecycle/UpdateOverlayFrame_020bbb6c.c`; reference line(s) 59, 99.
- `eu/src/overlays/ov041/calls/HandleCommandMenuShortcuts.c`; reference line(s) 23, 68.
- `eu/src/overlays/ov041/calls/MoveTargetCursor.c`; reference line(s) 11, 246.
- `eu/src/overlays/ov041/calls/StageStateCommandMenu.c`; reference line(s) 12, 71, 88.
- `eu/src/overlays/ov046/calls/Camera_UpdateController.c` → `src/ov046/shared_engine/Camera_UpdateController_020c0a70.c`; reference line(s) 29, 56.
- `eu/src/overlays/ov047/calls/Camera_ShouldStartManualTurn.c` → `src/ov047/camera/Camera_ShouldStartManualTurn_020c3ad8.c`; reference line(s) 16, 30.
- `eu/src/overlays/ov047/calls/Camera_UpdateFollowInput.c` → `src/ov047/camera/Camera_UpdateFollowInput_020c3b5c.c`; reference line(s) 83, 156, 194.
- `eu/src/overlays/ov047/calls/Camera_UpdateManualTurn.c` → `src/ov047/camera/Camera_UpdateManualTurn_020c4668.c`; reference line(s) 66, 80, 92, 95, 96.
- `eu/src/overlays/ov048/calls/UpdateOrbitCameraInput.c` → `src/ov048/shared_engine/UpdateOrbitCameraInput_020c3530.c`; reference line(s) 11, 28.
- `eu/src/overlays/ov073/calls/UpdateStatusMenu.c`; reference line(s) 75, 184.
- `eu/src/overlays/ov075/calls/ScrollMatrixView.c` → `src/ov075/unclassified_helpers/ScrollMatrixView_020c7be0.c`; reference line(s) 23, 68.
- `eu/src/overlays/ov075/calls/UpdateDirectionRepeat.c` → `src/ov075/unclassified_helpers/UpdateDirectionRepeat_020c62c8.c`; reference line(s) 11, 17, 27.
- `eu/src/overlays/ov075/calls/UpdateMatrixMenu.c` → `src/ov075/matrix_menu/UpdateMatrixMenu_020c707c.c`; reference line(s) 202, 678, 689, 712.
- `eu/src/overlays/ov075/calls/UpdateMatrixMenuView.c`; reference line(s) 86, 137.
- `eu/src/overlays/ov082/calls/StepEntryListCursor.c` → `src/ov082/unclassified_helpers/StepEntryListCursor_020bf448.c`; reference line(s) 22, 45.
- `eu/src/overlays/ov082/calls/UpdateOv082EntryList.c`; reference line(s) 24, 47.
- `eu/src/overlays/ov086/calls/HandleRecordScrollInput.c` → `src/ov086/panel_state/HandleRecordScrollInput_020c1828.c`; reference line(s) 12, 34, 51.
- `eu/src/overlays/ov087/calls/UpdateEntryScroll.c` → `src/ov087/panel_state/UpdateEntryScroll_020c74f0.c`; reference line(s) 24, 71, 78.
- `eu/src/overlays/ov089/calls/UpdateEntryCarousel.c` → `src/ov089/panel_state/UpdateEntryCarousel_020c01f4.c`; reference line(s) 16, 38, 45.

### `main:02060500` → `gPadPressedStorage`

Previous label `data_02060500`; existing ELF size **4 bytes**. Defining source: `eu/src/data/bss/Bss_main_02060500.c`.

4-byte BSS object: low u16 is the newly pressed button mask; upper two bytes are not assigned a role.

Pad_Sample writes (~previous & held) at the +4 halfword of the preceding PadState view, which is this address. Input consumers read this low halfword; movie playback can clear it to suppress an input sample.

Limits: Do not infer that every game-side write comes from Pad_Sample. Preserve the upper two bytes and the cross-symbol view; do not shrink this object to u16.

Pinned EU source/consumer references:

- `eu/src/calls/ToggleSelectedPanelSlot.c` → `src/arm9/panel_state/ToggleSelectedPanelSlot_02028104.c`; reference line(s) 17, 26.
- `eu/src/calls/UpdateKeyRepeat.c`; reference line(s) 11, 32.
- `eu/src/calls/UpdatePanelActivation.c` → `src/arm9/panel_state/UpdatePanelActivation_020288a0.c`; reference line(s) 15, 46.
- `eu/src/calls/UpdatePanelPromptInput.c`; reference line(s) 16, 45, 55.
- `eu/src/data/bss/Bss_main_02060500.c`; reference line(s) 4.
- `eu/src/overlays/ov000/calls/HandleTitleMenuInput.c` → `src/ov000/panel_state/HandleTitleMenuInput_02061de8.c`; reference line(s) 10, 47.
- `eu/src/overlays/ov000/calls/UpdateTitleTimedPanelPhase.c`; reference line(s) 3, 39.
- `eu/src/overlays/ov001/calls/HandleModeMenuInput.c` → `src/ov001/field_manager/HandleModeMenuInput_0207a370.c`; reference line(s) 11, 22, 24, 26, 32, 34, 39, 42, 45, 48, 54.
- `eu/src/overlays/ov001/calls/HandleShoulderLockOn.c` → `src/ov001/shared_engine/HandleShoulderLockOn_0206bd30.c`; reference line(s) 11, 24.
- `eu/src/overlays/ov001/calls/HandleSideTargetButtons.c`; reference line(s) 40, 59.
- `eu/src/overlays/ov001/calls/RunScoreTallySequence.c` → `src/ov001/unclassified_helpers/RunScoreTallySequence_0207cc8c.c`; reference line(s) 66, 122, 167, 205.
- `eu/src/overlays/ov002/calls/IsButtonBPressed.c` → `src/ov002/input_history/IsButtonBPressed_020632c8.c`; reference line(s) 3, 7.
- `eu/src/overlays/ov002/calls/IsButtonXPressed.c` → `src/ov002/input_history/IsButtonXPressed_020632e4.c`; reference line(s) 3, 7.
- `eu/src/overlays/ov002/calls/IsButtonYPressed.c` → `src/ov002/input_history/IsButtonYPressed_02063300.c`; reference line(s) 3, 7.
- `eu/src/overlays/ov002/calls/IsGlobalBit0Set.c` → `src/ov002/shared_engine/IsGlobalBit0Set_020632ac.c`; reference line(s) 1, 4.
- `eu/src/overlays/ov002/calls/UpdateListCursorPad.c` → `src/ov002/panel_state/UpdateListCursorPad_02062f88.c`; reference line(s) 3, 8.
- `eu/src/overlays/ov002/calls/UpdatePanelState.c` → `src/ov002/panel_state/func_ov002_0206162c.c`; reference line(s) 30, 48, 51, 54, 57.
- `eu/src/overlays/ov004/calls/RunScrollTextFrame.c` → `src/ov004/scroll_text/RunScrollTextFrame_020629d0.c`; reference line(s) 30, 69, 78.
- `eu/src/overlays/ov013/calls/UpdatePanelScrollState.c` → `src/ov013/panel_state/UpdatePanelScrollState_02071b6c.c`; reference line(s) 64, 141.
- `eu/src/overlays/ov014/calls/UpdatePanelEditInput.c` → `src/ov014/panel_state/UpdatePanelEditInput_0206d2e8.c`; reference line(s) 83, 155.
- `eu/src/overlays/ov021/calls/RefreshInputState.c` → `src/ov021/unclassified_helpers/RefreshInputState_020a6edc.c`; reference line(s) 18, 28.
- `eu/src/overlays/ov022/calls/RunMoviePlaybackState.c`; reference line(s) 33, 81, 87, 93, 100.
- `eu/src/overlays/ov025/calls/UpdateMenuScreen.c` → `src/ov025/menu_widgets/UpdateMenuScreen_020b5f08.c`; reference line(s) 11, 75.
- `eu/src/overlays/ov027/calls/MoveFocusByDpad.c` → `src/ov027/resource_container/MoveFocusByDpad_020b88c0.c`; reference line(s) 35, 59, 78, 97, 116.
- `eu/src/overlays/ov029/calls/HandleOverlayExitFlag.c` → `src/ov029/unclassified_helpers/HandleOverlayExitFlag_020ba708.c`; reference line(s) 3, 14.
- `eu/src/overlays/ov034/calls/HandleResultsInput.c`; reference line(s) 95, 140, 195, 210, 250, 261, 268, 275, 428.
- `eu/src/overlays/ov034/calls/RefreshResultsScreen.c` → `src/ov034/unclassified_helpers/RefreshResultsScreen_020bb578.c`; reference line(s) 118, 309.
- `eu/src/overlays/ov036/calls/AdvanceTextWindowPage.c` → `src/ov036/text_rendering/AdvanceTextWindowPage_020c0e14.c`; reference line(s) 52, 68.
- `eu/src/overlays/ov036/calls/UpdateTextWindowTyping.c` → `src/ov036/text_rendering/UpdateTextWindowTyping_020c0d34.c`; reference line(s) 14, 28, 39.
- `eu/src/overlays/ov037/calls/UpdateMenuSelection.c` → `src/ov037/unclassified_helpers/UpdateMenuSelection_020bb4bc.c`; reference line(s) 24, 49, 55, 61.
- `eu/src/overlays/ov038/calls/HandleOv038PageInput.c` → `src/ov038/unclassified_helpers/HandleOv038PageInput_020baa98.c`; reference line(s) 9, 19.
- `eu/src/overlays/ov039/calls/HandleListKeyInput.c` → `src/ov039/input/HandleListKeyInput_020bdc28.c`; reference line(s) 22, 48, 61.
- `eu/src/overlays/ov039/calls/PollHandlerInput.c` → `src/ov039/input/PollHandlerInput_020baf1c.c`; reference line(s) 20, 58, 61, 64, 67, 70, 73, 76, 79, 83.
- `eu/src/overlays/ov041/calls/CheckTimedPress.c`; reference line(s) 7, 24, 27.
- `eu/src/overlays/ov041/calls/HandleCommandMenuShortcuts.c`; reference line(s) 22, 64, 69, 76, 83, 91.
- `eu/src/overlays/ov041/calls/MoveTargetCursor.c`; reference line(s) 12, 62, 70, 78, 132, 190, 202, 217, 225, 244, 247, 250, 253, 256.
- `eu/src/overlays/ov041/calls/StageStateChooseItemTarget.c`; reference line(s) 8, 62, 78.
- `eu/src/overlays/ov041/calls/StageStateChooseTarget.c`; reference line(s) 8, 63, 68.
- `eu/src/overlays/ov041/calls/StageStateCommandMenu.c`; reference line(s) 13, 92, 94, 104.
- `eu/src/overlays/ov041/calls/UpdateTimedPressPanel.c`; reference line(s) 8, 65, 68.
- `eu/src/overlays/ov045/calls/RunIntroSequenceStep.c` → `src/ov045/scene/RunIntroSequenceStep_020bfea0.c`; reference line(s) 26, 102.
- `eu/src/overlays/ov045/calls/RunNameRevealStep.c` → `src/ov045/scene/RunNameRevealStep_020bfc30.c`; reference line(s) 32, 119.
- `eu/src/overlays/ov045/calls/RunResultTallyStep.c`; reference line(s) 101, 401.
- `eu/src/overlays/ov045/calls/UpdateResultFadeOut.c` → `src/ov045/shared_engine/UpdateResultFadeOut_020c0044.c`; reference line(s) 22, 51.
- `eu/src/overlays/ov047/calls/Camera_FollowLeaderTarget.c` → `src/ov047/camera/Camera_FollowLeaderTarget_020c491c.c`; reference line(s) 44, 108.
- `eu/src/overlays/ov047/calls/Camera_HandleDistanceToggle.c`; reference line(s) 26, 40.
- `eu/src/overlays/ov047/calls/Camera_ShouldStartManualTurn.c` → `src/ov047/camera/Camera_ShouldStartManualTurn_020c3ad8.c`; reference line(s) 17, 27, 31.
- `eu/src/overlays/ov070/calls/UpdateOv070BossProjectiles.c` → `src/ov070/object_state/UpdateOv070BossProjectiles_020d829c.c`; reference line(s) 101, 156.
- `eu/src/overlays/ov073/calls/HandleSlotListInput.c` → `src/ov073/status_menu/HandleSlotListInput_020c032c.c`; reference line(s) 57, 190, 201, 219, 225, 232.
- `eu/src/overlays/ov073/calls/UpdateStatusMenu.c`; reference line(s) 76, 149, 160, 171, 184, 296, 301.
- `eu/src/overlays/ov074/calls/SelectNextRootMenuItem.c` → `src/ov074/reviewed_helpers/SelectNextRootMenuItem_020c5550.c`; reference line(s) 3, 15.
- `eu/src/overlays/ov074/calls/SelectPreviousRootMenuItem.c` → `src/ov074/reviewed_helpers/SelectPreviousRootMenuItem_020c54f0.c`; reference line(s) 3, 13.
- `eu/src/overlays/ov075/calls/ItemMenu_Update_020d026c.c` → `src/ov075/unclassified_helpers/ItemMenu_Update_020d026c.c`; reference line(s) 110, 174, 180.
- `eu/src/overlays/ov075/calls/SelectMatrixNode.c` → `src/ov075/matrix_menu/SelectMatrixNode_020c4370.c`; reference line(s) 96, 350.
- `eu/src/overlays/ov075/calls/UnlockableListPanel_Open.c` → `src/ov075/unclassified_helpers/func_ov075_020d0014.c`; reference line(s) 99, 184.
- `eu/src/overlays/ov075/calls/UpdateDialInput_020cbf3c.c` → `src/ov075/unclassified_helpers/UpdateDialInput_020cbf3c.c`; reference line(s) 53, 72, 75, 78, 81.
- `eu/src/overlays/ov075/calls/UpdateFlagToggleGrid.c` → `src/ov075/unclassified_helpers/UpdateFlagToggleGrid_020cc3bc.c`; reference line(s) 33, 87.
- `eu/src/overlays/ov075/calls/UpdateMatrixOptionMenu.c`; reference line(s) 148, 315.
- `eu/src/overlays/ov075/calls/UpdateMessageDialog.c` → `src/ov075/unclassified_helpers/UpdateMessageDialog_020cf558.c`; reference line(s) 55, 122.
- `eu/src/overlays/ov075/calls/UpdateSlotCursor.c` → `src/ov075/unclassified_helpers/UpdateSlotCursor_020cc5a8.c`; reference line(s) 40, 141.
- `eu/src/overlays/ov075/calls/UpdateYesNoDialogInput.c` → `src/ov075/unclassified_helpers/UpdateYesNoDialogInput_020cf02c.c`; reference line(s) 26, 46, 49, 52.
- `eu/src/overlays/ov076/calls/ItemSelectionPanel_Open.c` → `src/ov076/unclassified_helpers/MenuPanel_Open_020cc0e4.c`; reference line(s) 99, 184.
- `eu/src/overlays/ov076/calls/MenuPanel_HandleInput.c` → `src/ov076/unclassified_helpers/MenuPanel_HandleInput_020cc33c.c`; reference line(s) 109, 171, 178.
- `eu/src/overlays/ov076/calls/MessageWindow_Update.c` → `src/ov076/unclassified_helpers/MessageWindow_Update_020cb4a8.c`; reference line(s) 55, 122.
- `eu/src/overlays/ov076/calls/MessageWindow_UpdateYesNoInput.c` → `src/ov076/unclassified_helpers/MessageWindow_UpdateYesNoInput_020cae3c.c`; reference line(s) 26, 46, 49, 52.
- `eu/src/overlays/ov076/calls/SlotMenu_HandleColumnInput.c` → `src/ov076/unclassified_helpers/SlotMenu_HandleColumnInput_020c4894.c`; reference line(s) 26, 55, 97.
- `eu/src/overlays/ov077/calls/HandleYesNoWindowInput.c` → `src/ov077/unclassified_helpers/HandleYesNoWindowInput_020c7e70.c`; reference line(s) 28, 47, 50, 53.
- `eu/src/overlays/ov077/calls/ItemListPanel_Open.c` → `src/ov077/unclassified_helpers/MenuPanel_Open_020c9118.c`; reference line(s) 99, 184.
- `eu/src/overlays/ov077/calls/MenuPanel_HandleInput_020c9390.c` → `src/ov077/unclassified_helpers/MenuPanel_HandleInput_020c9370.c`; reference line(s) 96, 161, 168.
- `eu/src/overlays/ov077/calls/MessageWindow_Update_020c84fc.c` → `src/ov077/unclassified_helpers/MessageWindow_Update_020c84dc.c`; reference line(s) 55, 122.
- `eu/src/overlays/ov077/calls/MoveSlotCursor.c` → `src/ov077/unclassified_helpers/MoveSlotCursor_020c4514.c`; reference line(s) 22, 41, 49.
- `eu/src/overlays/ov078/calls/SelectNextPage.c` → `src/ov078/unclassified_helpers/SelectNextPage_020c4e80.c`; reference line(s) 9, 28.
- `eu/src/overlays/ov078/calls/SelectPreviousMenuPage.c`; reference line(s) 3, 21.
- `eu/src/overlays/ov080/calls/SelectSlotOnDown.c` → `src/ov080/unclassified_helpers/SelectSlotOnDown_020c5968.c`; reference line(s) 18, 24.
- `eu/src/overlays/ov080/calls/SelectSlotOnUp.c` → `src/ov080/unclassified_helpers/SelectSlotOnUp_020c5924.c`; reference line(s) 18, 24.
- `eu/src/overlays/ov080/calls/ToggleOptionOnLeft.c` → `src/ov080/unclassified_helpers/ToggleOptionOnLeft_020c59ac.c`; reference line(s) 13, 18.
- `eu/src/overlays/ov080/calls/ToggleOptionOnRight.c` → `src/ov080/unclassified_helpers/ToggleOptionOnRight_020c59dc.c`; reference line(s) 13, 18.
- `eu/src/overlays/ov082/calls/StepEntryListCursor.c` → `src/ov082/unclassified_helpers/StepEntryListCursor_020bf448.c`; reference line(s) 23, 54, 66.
- `eu/src/overlays/ov082/calls/UpdateOv082EntryList.c`; reference line(s) 25, 48.
- `eu/src/overlays/ov084/calls/SelectNextOption.c`; reference line(s) 9, 17.
- `eu/src/overlays/ov084/calls/SelectPrevOption.c` → `src/ov084/select_menu/SelectPrevOption_020bfb88.c`; reference line(s) 3, 10.
- `eu/src/overlays/ov085/calls/StepPickerBack.c` → `src/ov085/unclassified_helpers/StepPickerBack_020c15f0.c`; reference line(s) 12, 19.
- `eu/src/overlays/ov085/calls/StepPickerForward.c` → `src/ov085/unclassified_helpers/StepPickerForward_020c163c.c`; reference line(s) 12, 19.
- `eu/src/overlays/ov086/calls/HandleRecordScrollInput.c` → `src/ov086/panel_state/HandleRecordScrollInput_020c1828.c`; reference line(s) 11, 22, 28, 68, 80.
- `eu/src/overlays/ov087/calls/UpdateEntryScroll.c` → `src/ov087/panel_state/UpdateEntryScroll_020c74f0.c`; reference line(s) 25, 74, 81.
- `eu/src/overlays/ov089/calls/UpdateEntryCarousel.c` → `src/ov089/panel_state/UpdateEntryCarousel_020c01f4.c`; reference line(s) 17, 41, 48.
- `eu/src/overlays/ov091/calls/HandleEntryConfirmInput.c` → `src/ov091/reviewed_helpers/HandleEntryConfirmInput_020c2064.c`; reference line(s) 3, 16.
- `eu/src/overlays/ov091/calls/ScrollListDown.c` → `src/ov091/panel_state/ScrollListDown_020c0010.c`; reference line(s) 34, 60.
- `eu/src/overlays/ov091/calls/ScrollListUp.c` → `src/ov091/panel_state/ScrollListUp_020bfed8.c`; reference line(s) 34, 60.
- `eu/src/overlays/ov093/calls/MoveGridCursorLeft.c` → `src/ov093/unclassified_helpers/MoveGridCursorLeft_020bf218.c`; reference line(s) 23, 51.
- `eu/src/overlays/ov093/calls/MoveGridCursorRight.c`; reference line(s) 23, 69.
- `eu/src/overlays/ov093/calls/ScrollBarStepDown.c` → `src/ov093/unclassified_helpers/ScrollBarStepDown_020c0a9c.c`; reference line(s) 32, 65.
- `eu/src/overlays/ov093/calls/ScrollBarStepUp.c` → `src/ov093/unclassified_helpers/ScrollBarStepUp_020c0958.c`; reference line(s) 32, 65.
- `eu/src/overlays/ov093/calls/WaitForPopupDismiss.c`; reference line(s) 3, 16.
- `eu/src/overlays/ov095/calls/MoveGridCursorDown.c` → `src/ov095/panel_state/MoveGridCursorDown_020c0ce0.c`; reference line(s) 38, 71.
- `eu/src/overlays/ov095/calls/MoveGridCursorUp.c` → `src/ov095/panel_state/MoveGridCursorUp_020c0a64.c`; reference line(s) 36, 69.
- `eu/src/overlays/ov097/calls/MoveListCursorUp.c` → `src/ov097/panel_state/MoveListCursorUp_020c055c.c`; reference line(s) 29, 66.
- `eu/src/overlays/ov097/calls/StepListCursorDown.c` → `src/ov097/panel_state/StepListCursorDown_020c06a8.c`; reference line(s) 29, 66.
- `eu/src/overlays/ov099/calls/StepListCursorDown_020c0f00.c` → `src/ov099/unclassified_helpers/StepListCursorDown_020c0ee0.c`; reference line(s) 27, 54.
- `eu/src/overlays/ov099/calls/StepListCursorUp.c` → `src/ov099/unclassified_helpers/StepListCursorUp_020c0da8.c`; reference line(s) 27, 54.
- `eu/src/overlays/ov101/calls/HandleListLeftInput.c`; reference line(s) 4, 23.
- `eu/src/overlays/ov101/calls/HandleListRightInput.c`; reference line(s) 4, 23.
- `eu/src/overlays/ov101/calls/ScrollPanelCursorDown.c`; reference line(s) 31, 65.
- `eu/src/overlays/ov101/calls/ScrollPanelCursorUp.c`; reference line(s) 31, 65.
- `eu/src/overlays/ov103/calls/ScrollListDown_020bfd60.c` → `src/ov103/panel_state/ScrollListDown_020bfd40.c`; reference line(s) 27, 52.
- `eu/src/overlays/ov103/calls/ScrollListUp_020bfc20.c` → `src/ov103/panel_state/ScrollListUp_020bfc00.c`; reference line(s) 27, 52.

### `main:02060504` → `gPadTransitionVBlankTicks`

Previous label `data_02060504`; existing ELF size **48 bytes**. Defining source: `eu/src/data/bss/Bss_main_02060500.c`.

48-byte BSS object: twelve u32 counters indexed by button bit position.

Pad_Sample updates counter[index] to GetVBlankCounter when that bit changes in previous^held, for twelve bits. ResetPadSampleState clears all 0x30 bytes. UpdateKeyRepeat reads selected indexes to derive repeat timing.

Limits: Timestamps record both press and release transitions, not only press times. Units are the returned VBlank counter, with repeat delay/interval multiplied by two by UpdateKeyRepeat; do not equate them with milliseconds.

Pinned EU source/consumer references:

- `eu/src/calls/Pad_Sample.c` → `src/arm9/input_history/Pad_Sample_0202abc8.c`; reference line(s) 10, 35.
- `eu/src/calls/ResetPadSampleState.c` → `src/arm9/core_small/func_0202aba8.c`; reference line(s) 4, 11.
- `eu/src/calls/UpdateKeyRepeat.c`; reference line(s) 12, 35.
- `eu/src/data/bss/Bss_main_02060500.c`; reference line(s) 3.

### `main:02060388` → `gPendingMasterBrightnessMask`

Previous label `data_02060388`; existing ELF size **1 bytes**. Defining source: `eu/src/data/bss/Bss_main_02060388.c`.

One-byte BSS object; bit 0 queues main-engine brightness and bit 1 queues sub-engine brightness.

SetBrightnessAndSyncMain and SetSecondaryBrightness store signed-byte cached values at base+1/+2. During VBlank they write hardware immediately and clear their bit; otherwise they set their bit. OSi_VBlankInterruptHandler applies flagged cached values and clears the mask.

Limits: Several native getters/setters use an int view anchored at this one-byte symbol and access neighboring objects at+1/+2/+4/+8. Preserve that native cross-symbol addressing; this symbol is not a complete brightness struct.

Pinned EU source/consumer references:

- `eu/src/calls/GetDisplaySetting.c` → `src/arm9/shared_engine/func_02029f68.c`; reference line(s) 1, 4.
- `eu/src/calls/GetMainBrightnessSetting.c` → `src/arm9/shared_engine/func_02029f48.c`; reference line(s) 1, 4.
- `eu/src/calls/GetSubBrightnessSetting.c` → `src/arm9/shared_engine/func_02029f58.c`; reference line(s) 3, 7.
- `eu/src/calls/OSi_VBlankInterruptHandler.c`; reference line(s) 18, 31, 39.
- `eu/src/calls/SetBrightnessAndSyncMain.c` → `src/arm9/shared_engine/SetBrightnessAndSyncMain_02029e7c.c`; reference line(s) 3, 10, 14, 17.
- `eu/src/calls/SetDisplaySetting.c` → `src/arm9/shared_engine/SetDisplaySetting_02029f28.c`; reference line(s) 1, 4, 5.
- `eu/src/calls/SetSecondaryBrightness.c` → `src/arm9/shared_engine/SetSecondaryBrightness_02029ed0.c`; reference line(s) 3, 10, 14, 17.
- `eu/src/data/bss/Bss_main_02060388.c`; reference line(s) 5.

### `main:02060389` → `gCachedMasterBrightnessStorage`

Previous label `data_02060389`; existing ELF size **3 bytes**. Defining source: `eu/src/data/bss/Bss_main_02060388.c`.

3-byte BSS object; signed main brightness at +0, signed sub brightness at +1; final byte opaque.

GetMainBrightnessSetting/GetSubBrightnessSetting read these bytes through base02060388+1/+2. The VBlank handler reads them directly, and ClampValueByMode uses the same signed values as clamp limits.

Limits: Keep three bytes, not a two-element allocation. The cached values also serve as limits; they are not automatically overwritten with hardware state after every read.

Pinned EU source/consumer references:

- `eu/src/calls/ClampValueByMode.c` → `src/arm9/shared_engine/ClampValueByMode_02029e28.c`; reference line(s) 4, 14, 20.
- `eu/src/calls/OSi_VBlankInterruptHandler.c`; reference line(s) 19, 34, 37.
- `eu/src/data/bss/Bss_main_02060388.c`; reference line(s) 4.

### `main:0206038c` → `gMasterBrightnessClampModeStorage`

Previous label `data_0206038c`; existing ELF size **8 bytes**. Defining source: `eu/src/data/bss/Bss_main_02060388.c`.

8-byte BSS object read as two native int mode words at offsets 0 and 4.

ClampValueByMode indexes this pair: mode 0 leaves value unchanged; mode 1 caps it at the cached signed brightness; mode 2 floors it there; other values leave it unchanged. SetDisplaySetting conditionally writes the second word through brightnessBase+8 and GetDisplaySetting reads that same word.

Limits: The inherited DisplaySetting names describe a partial access to the second mode word. This proposal preserves those APIs and native int declarations; it does not assign a platform display-mode enum or guarantee setters reject values outside 0..2.

Pinned EU source/consumer references:

- `eu/src/calls/ClampValueByMode.c` → `src/arm9/shared_engine/ClampValueByMode_02029e28.c`; reference line(s) 3, 8.
- `eu/src/data/bss/Bss_main_02060388.c`; reference line(s) 3.

### `dtcm:027e00a8` → `gGeometryCommandBuffer`

Previous label `data_027e00a8`; existing ELF size **4 bytes**. Defining source: `eu/src/data/dtcm/bss/Bss_dtcm_027e00a8.c`.

4-byte DTCM BSS pointer to a native geometry buffer with count at+0 and command data at+4.

SetGeometryCommandBufferIfUnset sets the pointer only if NULL and initializes the supplied count to zero. Geometry emitters append command words while DMA is active; GXi_FlushCommandList sends queued words to 0x04000400 and resets the count.

Limits: Buffer ownership is supplied by the caller; this pointer object does not allocate the buffer. The native buffer used by FlushGeometryCommandBuffer has capacity 192 words, separate from this four-byte pointer.

Pinned EU source/consumer references:

- `eu/libs/nitro/nns/calls/QueueOrSendGeometryCommandPair.c` → `src/itcm/library_nitro_nns/func_01ffcedc.c`; reference line(s) 10, 15.
- `eu/libs/nns/g3d/calls/NNS_G3dGeBufferOP_N.c` → `src/itcm/library_nitro_nns/func_01ffa37c.c`; reference line(s) 8, 16, 24, 27, 36.
- `eu/src/calls/FlushGeometryCommandBuffer.c` → `src/itcm/library_nitro_nns/func_01ffa204.c`; reference line(s) 9, 25, 26, 27, 34, 35, 36, 37, 46, 47, 48, 49.
- `eu/src/calls/GXi_FlushCommandList.c`; reference line(s) 10, 18, 19, 20.
- `eu/src/calls/SetGeometryCommandBufferIfUnset.c` → `src/arm9/core_small/func_02019ce0.c`; reference line(s) 2, 5, 7.
- `eu/src/data/dtcm/bss/Bss_dtcm_027e00a8.c`; reference line(s) 3.

### `dtcm:027e00ac` → `gGeometryTransferBusy`

Previous label `data_027e00ac`; existing ELF size **4 bytes**. Defining source: `eu/src/data/dtcm/bss/Bss_dtcm_027e00ac.c`.

4-byte DTCM BSS integer used as a nonzero transfer-in-progress flag.

FlushGeometryCommandBuffer waits for zero, sets 1 before an asynchronous geometry DMA and passes this address to ClearGeometryTransferBusy. WaitForGeometryTransfer spins until it becomes zero; emitters test it before buffering or sending.

Limits: No portable concurrency or cancellation API is introduced. Preserve volatile views and callback argument addressing.

Pinned EU source/consumer references:

- `eu/libs/nitro/fs/calls/WaitForGeometryTransfer.c`; reference line(s) 2, 6.
- `eu/libs/nitro/nns/calls/QueueOrSendGeometryCommandPair.c` → `src/itcm/library_nitro_nns/func_01ffcedc.c`; reference line(s) 11, 16.
- `eu/libs/nns/g3d/calls/NNS_G3dGeBufferOP_N.c` → `src/itcm/library_nitro_nns/func_01ffa37c.c`; reference line(s) 9, 17, 30.
- `eu/src/calls/FlushGeometryCommandBuffer.c` → `src/itcm/library_nitro_nns/func_01ffa204.c`; reference line(s) 8, 24, 30, 43, 52, 55, 58.
- `eu/src/calls/GXi_FlushCommandList.c`; reference line(s) 11, 14.
- `eu/src/data/dtcm/bss/Bss_dtcm_027e00ac.c`; reference line(s) 3.

### `itcm:01fffea0` → `gGeometryDmaFastModeStorage`

Previous label `data_01fffea0`; existing ELF size **32 bytes**. Defining source: `eu/src/data/itcm/bss/Bss_itcm_01fffea0.c`.

32-byte ITCM BSS symbol; only the first int is proven as the geometry DMA selection mode.

SetGeometryDmaFastMode writes the first word. FlushGeometryCommandBuffer chooses MI_SendGXCommandAsyncFast for nonzero and MI_SendGXCommandAsync for zero. InitSbcHandlersAndFastDma initializes mode 1.

Limits: The trailing 28 bytes remain opaque. Preserve all integer values, rather than narrowing the mode to BOOL or treating this as an RNG seed.

Pinned EU source/consumer references:

- `eu/src/calls/FlushGeometryCommandBuffer.c` → `src/itcm/library_nitro_nns/func_01ffa204.c`; reference line(s) 10, 53.
- `eu/src/calls/SetGeometryDmaFastMode.c`; reference line(s) 2, 5.
- `eu/src/data/itcm/bss/Bss_itcm_01fffea0.c`; reference line(s) 3.

### `dtcm:027e01f8` → `gSbcCommandHandlerStorage`

Previous label `data_027e01f8`; existing ELF size **136 bytes**. Defining source: `eu/src/data/dtcm/bss/Bss_dtcm_027e01ec.c`.

136-byte DTCM BSS symbol; a command-handler pointer table uses indices 0..31 (128-byte prefix), with eight trailing bytes opaque.

InitSbcHandlersAndFastDma assigns SBC handlers to indices 0..13. G3dDrawInternal masks the opcode with0x1f and invokes handler(state, command&0xe0).

Limits: Do not claim all 32 slots are initialized by this initializer, replace unassigned entries with noops, or shrink the 136-byte symbol. Existing native callback declarations remain unchanged.

Pinned EU source/consumer references:

- `eu/src/calls/G3dDrawInternal.c`; reference line(s) 61, 115.
- `eu/src/calls/InitSbcHandlersAndFastDma.c` → `src/arm9/archive_startup/InitializeArchiveBackend_0203a858.c`; reference line(s) 16, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32.
- `eu/src/data/dtcm/bss/Bss_dtcm_027e01ec.c`; reference line(s) 3.

### `main:02057c38` → `gSoundCommandMutex`

Previous label `data_02057c38`; existing ELF size **24 bytes**. Defining source: `eu/src/data/bss/Bss_main_02057c34.c`.

24-byte BSS symbol used as the sound command mutex.

SND_Init passes this address to OS_InitMutex. LockSoundCommandMutex passes its address to OS_LockMutex; SNDi_UnlockMutex passes the same symbol address through a legacy function-typed declaration to OS_UnlockMutex.

Limits: Do not copy the legacy function-typed unlock declaration into a portable API. Symbol naming changes neither that native ABI view nor mutex layout.

Pinned EU source/consumer references:

- `eu/libs/nitro/snd/calls/SND_Init.c` → `src/arm9/library_nitro_snd/func_0200ed90.c`; reference line(s) 47, 49.
- `eu/libs/nitro/snd/calls/SNDi_UnlockMutex.c` → `src/arm9/object_factory/func_0200eddc.c`; reference line(s) 3, 7.
- `eu/src/calls/LockSoundCommandMutex.c`; reference line(s) 2, 7.
- `eu/src/data/bss/Bss_main_02057c34.c`; reference line(s) 7.

### `main:02057c50` → `gSoundCommandQueueState`

Previous label `data_02057c50`; existing ELF size **36 bytes**. Defining source: `eu/src/data/bss/Bss_main_02057c34.c`.

36-byte BSS prefix: free-list head 0, finished tag 4, reserved-list head 8/tail 0xc, free-list tail 0x10, reply read index 0x14, submit write index 0x18, waiting count 0x1c, current tag 0x20.

SND_CommandInit initializes lists, indexes/count and tags. PopSoundCommand removes the free-list head. SND_FlushCommand submits the reserved list, advances the write index with 0..8 wrap and count/tag. SND_RecvCommandReply advances the read index, returns lists to the free list and advances finished tag.

Limits: SND_CommandInit has a combined struct view whose following queue begins at+0x24, the separate 02057c74 symbol. Preserve split storage. The command pool is excluded from this block because its source view extends beyond its 4096-byte ELF symbol.

Pinned EU source/consumer references:

- `eu/libs/nitro/snd/calls/SND_CountReservedCommand.c` → `src/arm9/library_nitro_snd/func_0200f304.c`; reference line(s) 5, 10.
- `eu/libs/nitro/snd/calls/SND_FlushCommand.c` → `src/arm9/audio/audio_flush_reserved_commands_0200f080.c`; reference line(s) 19, 35, 40, 47, 48, 56, 61, 62, 67, 74, 75, 76, 77, 79, 80, 81, 82.
- `eu/libs/nitro/snd/calls/SND_GetCurrentCommandTag.c` → `src/arm9/core_small/func_0200f288.c`; reference line(s) 6, 12, 13, 15.
- `eu/libs/nitro/snd/calls/SND_RecvCommandReply.c`; reference line(s) 27, 41, 47, 53, 54, 55, 56, 64, 65, 67, 69, 71, 72.
- `eu/src/calls/AppendReservedSoundCommand.c` → `src/arm9/core_small/func_0200f048.c`; reference line(s) 27, 34, 37, 38, 41.
- `eu/src/calls/CountReservedSoundCommands.c` → `src/arm9/core_small/func_0200f340.c`; reference line(s) 6, 14.
- `eu/src/calls/PopSoundCommand.c` → `src/arm9/audio/PopSoundCommand_0200f448.c`; reference line(s) 5, 12, 18, 19.
- `eu/src/calls/SND_CommandInit.c` → `src/arm9/library_nitro_snd/func_0200edf0.c`; reference line(s) 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51.
- `eu/src/calls/sound_command_tag_reached.c` → `src/arm9/audio/sound_command_tag_reached_0200f2b4.c`; reference line(s) 5, 12.
- `eu/src/data/bss/Bss_main_02057c34.c`; reference line(s) 6.

### `main:02057c74` → `gSoundSubmittedCommandListsStorage`

Previous label `data_02057c74`; existing ELF size **44 bytes**. Defining source: `eu/src/data/bss/Bss_main_02057c34.c`.

44-byte BSS symbol; nine code/data pointer-sized words (36 bytes) hold submitted SNDCommand list heads; eight trailing bytes opaque.

SND_FlushCommand stores a reserved-list head at sentRingIndex and wraps after index 8. SND_RecvCommandReply reads at waitingQueueRead and wraps after 8. SND_CommandInit reaches the same prefix as queueState.waitingQueue at+0x24.

Limits: Some native declarations use[8], others[9]; the actual send/receive control flow permits indexes 0..8. Preserve 44 bytes without correcting declarations in this naming block, and do not label the trailing 8 bytes as queue slots 9/10.

Pinned EU source/consumer references:

- `eu/libs/nitro/snd/calls/SND_FlushCommand.c` → `src/arm9/audio/audio_flush_reserved_commands_0200f080.c`; reference line(s) 20, 74.
- `eu/libs/nitro/snd/calls/SND_RecvCommandReply.c`; reference line(s) 28, 53.
- `eu/src/data/bss/Bss_main_02057c34.c`; reference line(s) 5.

### `main:020569c8` → `gVBlankCallbackExecutionFlags`

Previous label `data_020569c8`; existing ELF size **4 bytes**. Defining source: `eu/src/data/bss/Bss_main_020569c8.c`.

4-byte BSS word; only bit 0 is proven as the VBlank callback traversal-active flag.

OSi_VBlankInterruptHandler sets bit 0 before traversing the current callback list and clears it afterward, preserving other bits. InitFileLoader also passes this address as its thread stack-top argument.

Limits: Do not infer roles for other bits or a stack allocation size from this symbol. Passing its address as stack top does not make the four-byte flag word an 0x800-byte stack object.

Pinned EU source/consumer references:

- `eu/src/calls/InitFileLoader.c` → `src/arm9/filesystem/InitFileLoader_0202c20c.c`; reference line(s) 40, 76.
- `eu/src/calls/OSi_VBlankInterruptHandler.c`; reference line(s) 21, 40, 46.
- `eu/src/data/bss/Bss_main_020569c8.c`; reference line(s) 4.

## Sound pool follow-up

The pool is named in the separate `NATIVE_SOUND_POOL_SHARED4.md` block. Original `SND_CommandInit` instructions prove that the 4096-byte prefix, 2024-byte middle and 24-byte last record form one 6144-byte logical pool of 256 records at 24 bytes each. The native objects remain split; the initializer's larger array view and any relocation/source repair stay separate from these DATA names. The ring declarations still differ, so this block records the proven 0..8 indexes without correcting source types. Entropy mixing locals and thread/concurrency semantics remain separate portability work.


## Byte-exact validation

98 DATA identities retain their source paths, native sizes and storage.
280/282 affected official function checks pass; the remaining
2 reproduce the preserved baseline relocation discrepancies described in
[DATA_NATIVE_RELOCATION_BASELINE.md](DATA_NATIVE_RELOCATION_BASELINE.md).
A fresh gate passes
all 108 linked modules, with every module hash unchanged. Comparing
all 348 affected production objects also preserves allocated bytes and
alignment, symbol offsets/sizes and relocation targets/types/addends.

Run from `eu/`:

```sh
python tools/test_rename_symbol.py
python tools/audit_progress.py --check-receipts
bash tools/gate.sh
```
