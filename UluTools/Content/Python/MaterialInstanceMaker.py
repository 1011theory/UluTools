# this script lets you create a material instance from the textures you selected in the content browser, and optionally
# assign this newly created material instance to any selected static meshes.
# the script will also help you catch issues with compression formats in the textures.

# you can define rules for default material instances, naming conventions, and texture formats by creating a data asset child of ULUDA_MaterialInstanceMaker.
# after creating the data asset, assign it to the project settings section dedicated to Ulu Tools.
# you can define multiple data assets and use them as presets for your material creation purposes.


import unreal

print ('Material Instance Maker Locked In!')

rules_path = unreal.ULUDevSettings.get_default_object().material_instance_maker_rules.get_path_name() #python converts TexturePrefix(c++) to texture_prefix
rules = unreal.load_asset(rules_path)


def create_materialinstance_from_textures():

    selected_assets = unreal.EditorUtilityLibrary().get_selected_assets()

    mat = unreal.load_asset(rules.base_material.get_path_name())

    if not mat:
        unreal.log_error("Could not load parent material.")
        return

    #step 1: categorize each texture selected
    textures_data = rules.textures_data
    n_textures_required = len(textures_data)

    texture_struct_map = {}  # asset -> texturedata

    textures = isolate_textures_from_selection()

    if len(textures) == n_textures_required:
        for texture in textures:
            for texture_data in textures_data:
                if texture.get_name().endswith(texture_data.texture_suffix): #todo: check class = unreal.Texture instead at loop start. fix prefix if off too.
                    fix_texture_compression(texture, texture_data.texture_comp_settings) #common user error is to forget to specify mask compression setting for orm textures. this fixes it.
                    texture_struct_map[texture] = texture_data
                    continue
    else:
        unreal.EditorDialog.show_message('Error', f'Selected an incorrect number of textures({len(textures)})! Make sure you select {n_textures_required} textures.', unreal.AppMsgType.OK)
        return

    if len(texture_struct_map) != len(textures_data):
        unreal.EditorDialog.show_message('Error', 'Could not find all required textures. Ensure that the correct suffixes are used.', unreal.AppMsgType.OK) #todo: check each suffix is matched, and add unmatched suffixes to error message.
        return

    #step 2: Create MI and assign textures
    factory = unreal.MaterialInstanceConstantFactoryNew()
    current_path = unreal.EditorUtilityLibrary().get_current_content_browser_path()
    new_name = generate_material_instance_name(texture_struct_map)
    new_mi = unreal.AssetToolsHelpers.get_asset_tools().create_asset(asset_name = new_name, package_path = current_path, asset_class = unreal.MaterialInstanceConstant, factory = factory)

    unreal.MaterialEditingLibrary.set_material_instance_parent(instance = new_mi, new_parent = mat)

    for key, value in texture_struct_map.items():
        unreal.MaterialEditingLibrary.set_material_instance_texture_parameter_value(instance=new_mi, parameter_name=value.texture_parameter_name, value=key)

    unreal.EditorAssetLibrary.sync_browser_to_objects([new_mi.get_path_name()]) #selects the newly created asset in the content browser

    apply_material_to_static_meshes(new_mi)


def isolate_textures_from_selection():

    textures = []
    selected_assets = unreal.EditorUtilityLibrary().get_selected_assets()

    for asset in selected_assets:
        if isinstance(asset, unreal.Texture):
            textures.append(asset)

    return textures


def fix_texture_compression(in_texture: unreal.Texture, in_compression: unreal.TextureCompressionSettings):

    if in_texture.compression_settings != in_compression:
        result = unreal.EditorDialog.show_message(title='Warning', message='texture is using the wrong compression format. Fix?', message_type=unreal.AppMsgType.YES_NO)

        if result == unreal.AppReturnType.YES:
            in_texture.compression_settings = in_compression
            in_texture.modify()  # tells ue that the object has been changed. useful for undo/redo and correct saving
            unreal.EditorAssetLibrary.save_loaded_asset(in_texture)


def generate_material_instance_name(texture_struct_map):

    in_texture = next(iter(texture_struct_map))
    in_texture_rules = texture_struct_map[in_texture]

    prefix = rules.texture_prefix
    stripped_name = in_texture.get_name().removesuffix(in_texture_rules.texture_suffix).removeprefix(prefix)
    new_name = rules.material_instance_prefix + stripped_name
    return new_name


def apply_material_to_static_meshes(material):

    if material is None:
        return

    selected_assets = unreal.EditorUtilityLibrary().get_selected_assets()
    for asset in selected_assets:
        if isinstance(asset, unreal.StaticMesh):
            asset.set_material(0, material)


def run():
    create_materialinstance_from_textures()


#run()

#todo: improve clarity by defining variable types used