# Ulu Tools
<img src="https://github.com/user-attachments/assets/5758bdac-d6ab-4d9e-b607-c943716461db" alt="UluTools_Icon" width="75"/>


 A quality-of-life and workflow optimization toolkit for 3D artists working in Unreal Engine.
 
 -----
 
_The Ulu is a knife at the center of Inuit culture. From processing seal skins to preparing food, it's an indispensable tool that continues to aid people in the Arctic to this day. I have been tanning seal skins with an Ulu knife for the past few months, and the versatility it offers to the artists who wield it inspired the name of this plugin. Just like an Ulu knife, I hope this plugin will help 3D artists complete their tasks faster, more naturally, and in accordance with their project's guidelines. Keep your blades sharp!_

Ulu Tools extends the Unreal Editor to accelerate level artist workflows, ensure 3D assets comply with the defined asset pipeline, and help the production team identify issues with imported assets early in the process.

Features:
- Level Design Tools for iteration speed and asset optimization
- One-click Material Instance creation from selected textures and assignment to meshes, while fixing wrong compression settings.
- Customizable naming convention and compression settings presets that can be applied to large numbers of assets at once.
- Asset Validation tools to warn artists when their imported assets may cause performance issues.

---

### Table of Contents
- [Installation](#installation)
- [Quick Start](#quick-start)
- [Core Features](#core-features)
- [The Level Editor](#the-level-editor)
- [Material Instance Maker](#material-instance-maker)
- [Asset Validation](#asset-validation)

---

### Installation
1. Download the plugin and unzip it.
2. Create a `Plugins` folder under the root folder of your Unreal project if you don't have one already.
3. Paste **Ulu Tools** in your Plugins folder.
4. Launch your project, and click `Yes` when prompted to rebuild **Ulu Tools**.
5. Note: The plugin was built against Unreal 5.2

---

### Quick Start

1. From the top menu in the Editor, click on `Tools` -> `Ulu Tools` to launch the level art editor utility widget.<img src="https://github.com/user-attachments/assets/f68920ab-b660-4a5d-9815-bef8d7687c4b" width="600" alt="UluTools Screenshot" />

2. Assign the Rule Presets to the Project Settings
![image](https://github.com/user-attachments/assets/0c8f909f-6306-409c-9ca1-e329e245ddc9)

3. Ready!
![image](https://github.com/user-attachments/assets/5bb4422d-5da0-4304-aa39-bbe732dc0cb0)



---

### Core Features:
- Extended Level Editor Selection Capabilities:
  - Select invisible meshes, all meshes in camera view, lights/sounds in range, actors by mesh, meshes with wrong collision settings.
  - Display performance info about selected assets in the level: Nanite-conscious polycounts, number of materials, collision type, and number of instances.
  - Temporarily Show/Hide Niagara Systems that are capturing mouse focus while attempting to select assets underneath the VFX.
  - Temporarily bump up Texture Streaming Pool Size to keep working long sessions without needing to restart the editor.
 
- Fix Asset Naming Conventions
  - Artists can add custom prefixes to their assets in bulk, and optionally remove wrong prefixes.

- Material Instance Maker
  - With one click, artists can create material instances of a custom-defined material out of selected textures, automatically fix texture compression settings, and apply this material instance to any number of selected static meshes.
  - Artists can choose a default rule set for their texture, mesh, and material naming conventions, and automatically rename all their assets according to the selected convention.
 
- Asset Validation Tools
  - Static Meshes:
    - Non-Nanite Static Meshes with high polycounts.
    - Non-Nanite Static Meshes with missing LODS.
    - Static meshes that use complex collision as simple and have tri counts of 50+.
  - Skeletal Meshes:
    - Skeletal Meshes that are missing LODS.
  - Sound Waves and Meta Sounds:
    - Sound Assets missing a sound class or attenuation settings.
   
- Built for artists, with user-friendliness at its core
  - Most asset actions are available from the dedicated Editor Utility widgets or directly by right-clicking on the assets in the content browser.
 
---

### The Level Editor
![image](https://github.com/user-attachments/assets/e1e2a160-9b51-4c5e-bcfb-75c4d5dd3574)
The level editor contains various actions to help you get to assets in your level that are usually hard to select. Additionally, you can also view performance-related statistics for each mesh selected in the level. Unlike the default `gettricount` implementation, Ulu Tools displays the true Nanite polycount of Nanite meshes and not the fallback polycount.

### Material Instance Maker
![image](https://github.com/user-attachments/assets/43478e7a-7873-4390-a6a6-643471c26cab)
Drag and drop the textures that make up your asset in the Material Instance Maker, and optionally select related material instances and static meshes from the content browser. Click on `Rename Assets!` to have all the selected assets renamed according to their type and naming convention, including prefixes and suffixes, as well as fixing compression settings that might be mismatched from the ones defined in the Rules preset.

### Material Instance from Textures
<img src="https://github.com/user-attachments/assets/a648eeb9-ba0f-4292-a34f-3f1d9d7e8214" width="400" alt="UluTools Screenshot" />

Ulu tools lets you create material instances of a custom-defined material out of selected textures, automatically fix texture compression settings, and apply this material instance to any number of selected static meshes. No more waiting!

In order to make use of this functionality, you will need to ensure of the following:
- Your textures suffixes match the suffixes defined in your `MaterialMakerRules`.
- Your target material defined in `MaterialMakerRules` has a `TextureParameter` slot for each texture.
- The name of this parameter also needs to be specified in `MaterialMakerRules`.
  
To get started, select the 3 textures in the Examples folder and right click on any of them. A new button `CreateMaterialInstanceFromTextures` will be visible. Click it, and a new Material Instance named after the 3 textures will be created in the same folder.
Similarly, you can create a material instance by using the `New Material Instance From Textures` button in the Ulu Tools Level Editor widget. This button also allows you to apply the new material to any currently selected static meshes in the content browser.



