import unreal

print ('Sound Fixer Initialized!')


def apply_attenuation():
    rules_path = unreal.ULUDevSettings.get_default_object().ulu_tools_rules.get_path_name()
    rules: unreal.ULUDA_Rules = unreal.load_asset(rules_path)

    selected_assets = unreal.EditorUtilityLibrary.get_selected_assets_of_class(unreal.SoundBase)

    for in_sound in selected_assets:
        in_sound.set_editor_property('attenuation_settings', rules.sound_attenuation_class)
        in_sound.modify()


def fix_prefixes(): # call this separately since names will change, and the apply sound script might not be able to catch the change in time?
    selected_assets = unreal.EditorUtilityLibrary.get_selected_assets_of_class(unreal.SoundBase)

    for in_sound in selected_assets:
        old_name = in_sound.get_name()
        new_name = old_name

        if in_sound.get_class() == unreal.MetaSound:
            if not old_name.startswith('MS_'):
                new_name = 'MS_' + old_name

        elif not old_name.startswith('S_'): #if it's not a meta sound, then it's a sound.
            new_name = 'S_' + old_name

        if new_name != old_name:
            asset_old_path = in_sound.get_path_name()
            asset_folder = unreal.Paths.get_path(asset_old_path)
            new_path = asset_folder + "/" + new_name
            rename_success = unreal.EditorAssetLibrary.rename_asset(asset_old_path, new_path)


def apply_sound_class():
    rules_path = unreal.ULUDevSettings.get_default_object().ulu_tools_rules.get_path_name()
    rules: unreal.ULUDA_Rules = unreal.load_asset(rules_path)

    selected_assets = unreal.EditorUtilityLibrary.get_selected_assets_of_class(unreal.SoundBase)

    for in_sound in selected_assets:
        in_sound.set_editor_property('sound_class_object', rules.sound_class)
        in_sound.modify()

    unreal.EditorDialog.show_message(title='Sounds Edited',
                                     message=f'Sounds Affected = {len(selected_assets)}',
                                     message_type=unreal.AppMsgType.OK)




# ToDo: customizable sound class input
# ToDo: specify sound attenuation class
# ToDo: Expose as button
# ToDo: add pop up when running that lets you pick sound class and attenuation setting