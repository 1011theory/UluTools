# Ulu Tools

 A quality-of-life and workflow optimization toolkit for 3D artists working in Unreal Engine.
 
 -----
 
_The Ulu is a knife at the center of Inuit culture. From processing seal skins to preparing food, it's an indispensable tool that continues to aid people in the Arctic to this day. I have been tanning seal skins with an Ulu knife for the past few months, and the versatility it offers to the artists who wield it inspired the name of this plugin. Just like an Ulu knife, I hope this plugin will help 3D artists complete their tasks faster, more naturally, and in accordance with their project's guidelines. Keep your blades sharp!_

Ulu Tools extends the Unreal Editor by leveraging Python, C++, and Blueprint scripting to accelerate level artist workflows, ensure 3D assets comply with the defined asset pipeline, and help the production team identify issues with imported assets early in the process.

---

### Quick Start

From the top menu in the Editor, click on `Tools` -> `Ulu Tools` to run the level art editor utility widget.

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


