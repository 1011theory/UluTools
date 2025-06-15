# Ulu Tools
<img src="https://github.com/user-attachments/assets/5758bdac-d6ab-4d9e-b607-c943716461db" alt="UluTools_Icon" width="75"/>


 A quality-of-life and workflow optimization toolkit for 3D artists working in Unreal Engine.
 
 ---
 
_The Ulu is a knife at the center of Inuit culture. From processing seal skins to preparing food, it's an indispensable tool that continues to aid people in the Arctic to this day. I have been tanning seal skins with an Ulu knife for the past few months, and the versatility it offers to the artists who wield it inspired the name of this plugin. Just like an Ulu knife, I hope this plugin will help 3D artists complete their tasks faster, more naturally, and in accordance with their project's guidelines. Keep your blades sharp!_

Ulu Tools extends the Unreal Editor to accelerate level artist workflows, ensure 3D assets comply with the defined asset pipeline, and help the production team identify issues with imported assets early in the process. Built for artists, with user-friendliness at its core.

Features:
- Level Design Tools for iteration speed and asset optimization.
- One-click Material Instance creation from selected textures and assignment to meshes, while fixing wrong compression settings.
- Customizable naming convention and compression settings presets that can be applied to large numbers of assets at once.
- Asset Validation tools to warn artists when their imported assets may cause performance issues.
- Batch Rename/Replace asset prefixes.
- Most asset actions are available from the dedicated Editor Utility widgets or directly by right-clicking on the assets in the content browser.

---

### Table of Contents
- [Installation](#installation)
- [Quick Start](#quick-start)
- [The Level Editor](#the-level-editor)
- [Rules Presets](#rules-presets)
- [Asset Renamer](#asset-renamer)
- [Material Instance From Textures](#material-instance-from-textures)
- [Fix Asset Naming Conventions](#fix-asset-naming-conventions)
- [Asset Validation Tools](#asset-validation-tools)
- [Sound Fixer](sound-fixer)

---

### Installation
1. Download the plugin and unzip it.
2. Create a `Plugins` folder under the root folder of your Unreal project if you don't have one already.
3. Paste **Ulu Tools** in your Plugins folder.
4. Launch your project, and click `Yes` when prompted to rebuild **Ulu Tools**.
5. Note: The plugin was built against Unreal 5.2

---

### Quick Start

1. From the top menu in the Editor, click on `Tools` -> `Ulu Tools` to launch the level art editor utility widget.

   <img src="https://github.com/user-attachments/assets/f68920ab-b660-4a5d-9815-bef8d7687c4b" width="600" alt="UluTools Screenshot" />

2. Assign the `Rule Presets` to the `Ulu Tools Developer Settings` section in `Project Settings`.

   ![image](https://github.com/user-attachments/assets/0c8f909f-6306-409c-9ca1-e329e245ddc9)

---

### The Level Editor
![image](https://github.com/user-attachments/assets/e1e2a160-9b51-4c5e-bcfb-75c4d5dd3574)

The level editor contains various actions to help you get to assets in your level that are usually hard to select. Additionally, you can also view performance-related statistics for each mesh selected in the level. Unlike the default `gettricount` implementation, Ulu Tools displays the true Nanite polycount of Nanite meshes and not the fallback polycount.
- Select invisible meshes, all meshes in camera view, lights/sounds in range, actors by mesh, meshes with wrong collision settings.
  - Display performance info about selected assets in the level: Nanite-conscious polycounts, number of materials, collision type, and number of instances.
  - Temporarily Show/Hide Niagara Systems that are capturing mouse focus while attempting to select assets underneath the VFX.
  - Temporarily bump up Texture Streaming Pool Size to keep working long sessions without needing to restart the editor.

---
 
### Rules Presets

There are two kinds of `rules presets`.
1. `MaterialInstanceMaker` rules presets are used to control the naming conventions and compression settings of your assets.
2. `UluRules` rules presets.

You can use your own presets by creating a new `Data Asset` in the `Content Browser`. To do so, right-click on an empty space, select `Miscellaneous`->`Data Asset`. Pick either ` ULUDA_MaterialInstanceMaker` (for texture and material rules) or `ULUDA_Rules` (for generic project rules) as your base class.

`Data Assets` derived from `ULUDA_MaterialInstanceMaker` are used as rule presets for the material generation, naming convention, and texture compression settings. In the example asset provided, you will see that the Rules Preset is set up to accomodate assets with the typical ORM texture packing setup used by the Unreal Substance Painter export preset.
Besides defining how you want to prefix, suffix, and compress your various textures, it's important to define the Parameter name of those textures in your materials. This is necessary to ensure correct material instance generation.

![image](https://github.com/user-attachments/assets/1737ce88-6e96-423c-a50b-25f4ed08a307)

---

### Asset Renamer
![image](https://github.com/user-attachments/assets/43478e7a-7873-4390-a6a6-643471c26cab)

Artists often import meshes and textures iteratively, and they don't have time to adjust to custom naming conventions. Textures and meshes will be imported in the engine with all sorts of names and wrong compression settings. The asset renamer was created to overcome this.
1. Drag and drop the textures that make up your asset in the asset renamer
2. (Optional) Select related material instances and static meshes related to the textures
3. Click on `Rename Assets!` to have all the selected assets renamed according to their type and naming convention, including prefixes and suffixes, as well as fixing compression settings that might be mismatched from the ones defined in the Rules preset.

---

### Material Instance from Textures
<img src="https://github.com/user-attachments/assets/a648eeb9-ba0f-4292-a34f-3f1d9d7e8214" width="400" alt="UluTools Screenshot" />

Ulu tools lets you create material instances of a custom-defined material out of selected textures, automatically fix texture compression settings, and apply this material instance to any number of selected static meshes. No more waiting!

In order to make use of this functionality, you will need to ensure of the following:
- Your textures suffixes match the suffixes defined in your `MaterialMakerRules`.
- Your target material defined in `MaterialMakerRules` has a `TextureParameter` slot for each texture.
- The name of this parameter also needs to be specified in `MaterialMakerRules`.
  
To get started, select the 3 textures in the Examples folder and right click on any of them. A new button `CreateMaterialInstanceFromTextures` will be visible. Click it, and a new Material Instance named after the 3 textures will be created in the same folder.
Similarly, you can create a material instance by using the `New Material Instance From Textures` button in the Ulu Tools Level Editor widget. This button also allows you to apply the new material to any currently selected static meshes in the content browser.

---

### Fix Asset Naming Conventions
  - Artists can add custom prefixes to their assets in bulk, and optionally remove wrong prefixes.
  1. Select your assets with incorrect naming prefixes.
  2. (Optional) Define the incorrect prefix in the `Fix Prefixes` button of the `Ulu Level Editor`.
  3. Define the new prefix in the `Fix Prefixes` button of the `Ulu Level Editor`.
  4. Click on `Fix Prefixes`.
  5. If you need to revert back to the old prefix, make sure you are running the `Fix Redirectors` command to fix hidden references to the renamed assets.

<img width="233" alt="image" src="https://github.com/user-attachments/assets/821198cb-6d12-4112-a483-710546976961" />

<img width="1303" alt="image" src="https://github.com/user-attachments/assets/8b4eef41-7885-4b56-a51a-c501206f64f9" />

---

 ### Asset Validation Tools

Ulu tools comes with a set of validators to help you ensure your imported assets are performant and avoid common mistakes. Upon importing or saving your assets, you will receive warnings and errors if critical features are missing/incorrect.

![image](https://github.com/user-attachments/assets/a714be39-d958-404d-8fe9-001a5d805b49)
![image](https://github.com/user-attachments/assets/3467a669-a6e7-4885-b703-0ee1eddffeaf)


Here are the validator warnings and errors provided.
  - **Static Meshes**:
    - Non-Nanite Static Meshes with high polycounts.
    - Non-Nanite Static Meshes with missing LODS.
    - Static meshes that use complex collision as simple and have tri counts of 50+.
  - **Skeletal Meshes**:
    - Skeletal Meshes that are missing LODS.
  - **Sound Waves and Meta Sounds**:
    - Sound Assets missing a sound class or attenuation settings.

---
   
### Sound Fixer

A common production problem is that sounds make it to packaged builds without being assigned any `soundclass` or `attenuation settings`. Having no soundclass can become a big problem especially in terms of volume management within a game - if an explosion sound isn't marked as `sfx` and the player turned the sfx volume down, the volume of the explosion will still be at max loudness. Similarly, forgetting attenuation settings can make a sound feel out of place in the level. 
Luckily, our asset validation tools flag these issues. But we still need a way to apply these fixes in bulk to thousands of assets at once. This is where the Ulu Tools `Sound Fixer` comes in handy.

1. Ensure that you have assigned your desired `soundclass` and optionally `attenuation settings` to your `UluRules` preset in the `Ulu Tools Dev Settings`.
2. Select all your sounds and meta sounds that need to be fixed.
3. Right-click on any of the sounds, and choose one of the two Ulu Tools actions `Assign Soundclass` or `Assign Attenuation`.
   
   ![image](https://github.com/user-attachments/assets/a8117037-a14a-49c4-95ae-a259dfa0b81c)

---



