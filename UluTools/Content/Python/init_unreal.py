#init_unreal scripts in the /Python subfolder are run automatically by Unreal on plugin startup.
import unreal

menus = unreal.ToolMenus.get()

# Launch Ulu Tools Menu
@unreal.uclass() #class used as the menu entry
class UluToolsScriptObject(unreal.ToolMenuEntryScript):
    def add_icon(self):
        self.data.icon = unreal.ScriptSlateIcon("UluToolsStyle", "UluTools.Icon")
    @unreal.ufunction(override=True)
    def execute(self, context):
        widget: unreal.EditorUtilityWidgetBlueprint = unreal.load_asset('/UluTools/EUW_UluTools.EUW_UluTools')
        if not widget:
            unreal.log_warning('Failed to load Ulu Tools Widget.')
            return
        unreal.get_editor_subsystem(unreal.EditorUtilitySubsystem).spawn_and_register_tab(widget)


#menu entry assignment
tools_menu = menus.find_menu("LevelEditor.MainMenu.Tools")
ulu_tools_menu_entry = UluToolsScriptObject()
ulu_tools_menu_entry.add_icon()
ulu_tools_menu_entry.init_entry(owner_name= tools_menu.menu_name, menu=tools_menu.menu_name, section="Python", name="Ulu Tools", label="Ulu Tools", tool_tip="Launch Ulu Tools")
ulu_tools_menu_entry.register_menu_entry()
#-----------------------------------------------------------------------------------------------------------------------


# Audio Operations
import SoundFixer

#Apply SoundClass when right-clicking on Sound Asset
@unreal.uclass() #class used as the menu entry
class UluTools_SoundClassButton(unreal.ToolMenuEntryScript):
    def add_icon(self):
        self.data.icon = unreal.ScriptSlateIcon("UluToolsStyle", "UluTools.Icon")
    @unreal.ufunction(override=True)
    def execute(self, context):
        SoundFixer.apply_sound_class()


asset_context_menu = menus.find_menu("ContentBrowser.AssetContextMenu.SoundWave")
soundclassbutton_script_object = UluTools_SoundClassButton();
soundclassbutton_script_object.add_icon()
soundclassbutton_script_object.init_entry(owner_name= asset_context_menu.menu_name, menu=asset_context_menu.menu_name, section="GetAssetActions", name="Assign SoundClass", label="Assign Sound Class", tool_tip="Assigns the Sound Class specified in Ulu Tools Developer Settings.")
soundclassbutton_script_object.register_menu_entry()


#Apply Attenuation Settings when right-clicking on Sound Asset
@unreal.uclass() #class used as the menu entry
class UluTools_SoundAttenuationButton(unreal.ToolMenuEntryScript):
    def add_icon(self):
        self.data.icon = unreal.ScriptSlateIcon("UluToolsStyle", "UluTools.Icon")
    @unreal.ufunction(override=True)
    def execute(self, context):
        SoundFixer.apply_attenuation()


soundattenuationbutton_script_object = UluTools_SoundAttenuationButton();
soundattenuationbutton_script_object.add_icon()
soundattenuationbutton_script_object.init_entry(owner_name= asset_context_menu.menu_name, menu=asset_context_menu.menu_name, section="GetAssetActions", name="Assign Attenuation", label="Assign Attenuation", tool_tip="Assigns the Sound Attenuation specified in Ulu Tools Developer Settings.")
soundattenuationbutton_script_object.register_menu_entry()
#ToDo: add menu sub-entry for these operations.
#-----------------------------------------------------------------------------------------------------------------------


#Texture Operations
import MaterialInstanceMaker

#Apply SoundClass when right-clicking on Sound Asset
@unreal.uclass() #class used as the menu entry
class UluTools_MaterialMakerButton(unreal.ToolMenuEntryScript):
    def add_icon(self):
        self.data.icon = unreal.ScriptSlateIcon("UluToolsStyle", "UluTools.Icon")
    @unreal.ufunction(override=True)
    def execute(self, context):
        MaterialInstanceMaker.run()


texture_context_menu = menus.find_menu("ContentBrowser.AssetContextMenu.Texture")
materialmakerbutton_script_object = UluTools_MaterialMakerButton();
materialmakerbutton_script_object.add_icon()
materialmakerbutton_script_object.init_entry(
    texture_context_menu.menu_name,
    texture_context_menu.menu_name,
    "GetAssetActions",
    "Material Instance From Textures",
    "Material Instance From Textures",
    "Create a Material Instance of the Material specified in Ulu Tools Developer Settings from the selected Textures.")
materialmakerbutton_script_object.register_menu_entry()
#ToDo: support simultaneous selection of textures + static meshes.
#-----------------------------------------------------------------------------------------------------------------------


