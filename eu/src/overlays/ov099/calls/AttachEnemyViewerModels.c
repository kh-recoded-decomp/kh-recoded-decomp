#include "nitro/types.h"

typedef struct ViewerModel {
    u16 flags;
    u8 unknown002[0x104 - 2];
} ViewerModel;

typedef struct ModelViewer {
    void *modelData;
    int *modelRecords[40];
    void *sourceFile;
    ViewerModel models[5];
    int selectedEnemy;
} ModelViewer;

typedef char ViewerModelSize[sizeof(ViewerModel) == 0x104 ? 1 : -1];
typedef char ViewerModelsOffset[(u32)&((ModelViewer *)0)->models == 0xa8 ? 1 : -1];
typedef char ViewerSelectionOffset[(u32)&((ModelViewer *)0)->selectedEnemy == 0x5bc ? 1 : -1];

extern void attach_child_object(ViewerModel *child, ViewerModel *parent, const char *jointName);
extern const char sOv099_Bip01Head_020c28a4[];
extern const char sOv099_Bip01Spine1_020c28b0[];
extern const char sOv099_LLink_020c28c0[];
extern const char sOv099_RLink_020c28c8[];
extern const char sOv099_Sword_020c28d0[];
extern const char sOv099_WeaponTg00_020c28d8[];
extern const char sOv099_RoHL_020c28e4[];
extern const char sOv099_RoHR_020c28ec[];
extern const char sOv099_Root_020c28f4[];

void AttachEnemyViewerModels(ModelViewer *viewer, int selectedEnemy)
{
    switch (selectedEnemy) {
    case 11:
    case 32:
        break;
    case 1:
        attach_child_object(&viewer->models[1], &viewer->models[0], sOv099_Bip01Head_020c28a4);
        attach_child_object(&viewer->models[2], &viewer->models[0], sOv099_Bip01Spine1_020c28b0);
        break;
    case 6:
        attach_child_object(&viewer->models[1], &viewer->models[0], sOv099_LLink_020c28c0);
        attach_child_object(&viewer->models[2], &viewer->models[0], sOv099_RLink_020c28c8);
        break;
    case 35:
        attach_child_object(&viewer->models[1], &viewer->models[0], sOv099_Sword_020c28d0);
        break;
    case 33:
        attach_child_object(&viewer->models[1], &viewer->models[0], sOv099_Bip01Head_020c28a4);
        attach_child_object(&viewer->models[2], &viewer->models[0], sOv099_Bip01Spine1_020c28b0);
        break;
    case 34:
        attach_child_object(&viewer->models[1], &viewer->models[0], sOv099_WeaponTg00_020c28d8);
        break;
    case 37:
        attach_child_object(&viewer->models[1], &viewer->models[0], sOv099_RoHL_020c28e4);
        attach_child_object(&viewer->models[2], &viewer->models[0], sOv099_RoHR_020c28ec);
        break;
    case 12:
        attach_child_object(&viewer->models[1], &viewer->models[0], sOv099_Root_020c28f4);
        break;
    case 13:
        attach_child_object(&viewer->models[1], &viewer->models[0], sOv099_Bip01Head_020c28a4);
        {
            ViewerModel *models = viewer->models;
            models[1].flags |= 8;
        }
        break;
    }
}
