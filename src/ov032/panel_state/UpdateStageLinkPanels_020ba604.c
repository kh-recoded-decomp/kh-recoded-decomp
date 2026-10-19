#include "nitro/types.h"

typedef struct StageLinkMenu {
    u8 reserved00[0x24];
    u8 selection;
    u8 previousSelection;
    u8 reserved26[2];
    s8 selectedNode;
    u8 reserved29[8];
    s8 panelIds[6];
    s8 rotations[6];
    s8 neighbors[6][4];
    s8 currentNode;
    s8 nodeFlags[6];
    u8 reserved5c[0x24];
    BOOL redraw;
    s32 transition;
    BOOL showSelection;
} StageLinkMenu;

typedef struct FieldObject FieldObject;

extern StageLinkMenu *gStageLinkMenu;
extern void ConfigureMenuPanel(int panel, int style, int destination, int direction, BOOL enabled);
extern void SetScenePanelEnabled(int panel, BOOL enabled);
extern void SetScenePanelAnimation(int panel, int blend, int argument, BOOL keepFlag);
extern FieldObject *GetIndexedFieldObject(int which, int panelId);
extern void FieldObject_SetEnabled(FieldObject *object, BOOL enabled);

/* Map the current node's four links onto rotated panels, then update the
 * selected-node objects and request a redraw of the link menu. */
void UpdateStageLinkPanels_020ba604(void)
{
    s8 rotation;
    int edgeDirection;
    int panelIndex;
    int direction;

    for (direction = 0; direction < 4; direction++) {
        int current = gStageLinkMenu->currentNode;

        if (gStageLinkMenu->neighbors[current][direction] >= 0) {
            /* Find the reciprocal edge in the neighboring node. */
            for (edgeDirection = 0; edgeDirection < 4; edgeDirection++) {
                if (gStageLinkMenu->neighbors[gStageLinkMenu->neighbors[current][direction]][edgeDirection] == current) {
                    break;
                }
            }

            int target = gStageLinkMenu->neighbors[current][direction];
            int reverseDirection = ((edgeDirection + 4) -
                gStageLinkMenu->rotations[gStageLinkMenu->neighbors[current][direction]]) & 3;

            /* The reciprocal direction is saved; use the direction index for
             * the current node's panel orientation next. */
            edgeDirection = direction + 4;
            panelIndex = ((edgeDirection - gStageLinkMenu->rotations[current]) & 3) + 1;
            ConfigureMenuPanel(panelIndex, 3, gStageLinkMenu->panelIds[target] + 1,
                reverseDirection + 1, TRUE);
            SetScenePanelEnabled(
                (((direction + 4 - gStageLinkMenu->rotations[gStageLinkMenu->currentNode]) & 3) + 1), TRUE);
        } else {
            ConfigureMenuPanel(((direction + 4 - gStageLinkMenu->rotations[current]) & 3) + 1,
                0, -1, -1, TRUE);
            rotation = gStageLinkMenu->rotations[gStageLinkMenu->currentNode];
            SetScenePanelEnabled(((direction + 4 - rotation) & 3) + 1, FALSE);
        }
    }

    if (gStageLinkMenu->nodeFlags[gStageLinkMenu->currentNode] != 0) {
        SetScenePanelAnimation(0, 1, 0, TRUE);
    } else {
        SetScenePanelAnimation(0, 0, 0, TRUE);
    }
    if (gStageLinkMenu->showSelection && gStageLinkMenu->currentNode == gStageLinkMenu->selectedNode) {
        FieldObject *object;
        BOOL otherSelection;

        object = GetIndexedFieldObject(gStageLinkMenu->selection == gStageLinkMenu->previousSelection,
            gStageLinkMenu->panelIds[gStageLinkMenu->currentNode]);
        FieldObject_SetEnabled(object, TRUE);
        otherSelection = TRUE;
        if (gStageLinkMenu->selection == gStageLinkMenu->previousSelection) {
            otherSelection = FALSE;
        }
        object = GetIndexedFieldObject(otherSelection, gStageLinkMenu->panelIds[gStageLinkMenu->currentNode]);
        FieldObject_SetEnabled(object, FALSE);
    } else {
        FieldObject *object;

        object = GetIndexedFieldObject(0, gStageLinkMenu->panelIds[gStageLinkMenu->currentNode]);
        FieldObject_SetEnabled(object, FALSE);
        object = GetIndexedFieldObject(1, gStageLinkMenu->panelIds[gStageLinkMenu->currentNode]);
        FieldObject_SetEnabled(object, FALSE);
    }
    gStageLinkMenu->redraw = TRUE;
    gStageLinkMenu->transition = 0;
}
