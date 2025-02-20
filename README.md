# TestTask_2025

Developed with Unreal Engine 5.4.4

The main folder of the TestTask_2025 project. The AssetPacks, ExternalContent, StarterContent, LevelPrototyping folders are auxiliary. The whole project is written in Blueprints, but the selected template was generated using C++, so a small part of the logic is stored in the Source folder. The unfinished slide is contained in the TT2025CharacterMovementComponent.

TestTask_2025 folder contains:
Blueprints - Main Character, Controller, HUD, game mode. Objects - contains objects with which the character can interact on the level. Weapon - our weapon.
Character - contains a rig that is not used.
Component - our components for character health, the ability to interact with objects on the level, weapon component, effects component.
Impacts - contains a decal of the hit from the weapon ammunition.
Input - character control of the character.
Interface - contains the interface that should realize the objects with which we want to interact.
LevelPrototyping - contains objects that react to ammunition hits.
Maps - contains the basic map of the project.
Mixamo - contains animations, animation Blueprint, animation montages and character skeleton/textures/materials.
PhysMaterials - contains materials that we attach to objects if we want weapon ammunition to create different effects depending on the material.
Sounds - contains all sounds that are used in the project SoundClass, SoundCue.
Structs - structures that are used to customize decals, ammunition hits, ammunition customization, weapon customization and animations to them.
UI - widgets of the project.
VFX - contains all Niagara effects that are used in the project.

Controls:
Shooting - LKM.
Reloading - R.
Movement - WASD.
Acceleration - SHIFT.
Slide - F.
Change weapons - Q.
Change camera - V.

Not implemented:
Climbing, Wall Runnings, AI system, scene lighting, basic optimization of LOD usage.
