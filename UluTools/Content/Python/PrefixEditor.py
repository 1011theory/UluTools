# this script does not run directly. It is copied in the 'RenameAssets' function of EUW_UluTools to let Blueprint User
# Widget custom inputs be used as inputs of the script.

import unreal


def get_selected_content_browser_assets():
    editor_utility = unreal.EditorUtilityLibrary()
    selected_assets = editor_utility.get_selected_assets()

    return selected_assets


def generate_new_name_for_asset(asset, new_prefix, old_prefix):
    old_name = asset.get_name()
    cleaned_name = old_name.removeprefix(old_prefix)
    return new_prefix + cleaned_name


def rename_assets(assets, new_prefix, old_prefix):
    """Rename each asset and show a progress bar that the user can cancel."""
    total = len(assets)
    if total == 0:
        unreal.log_warning("No assets selected – nothing to rename.")
        return

    task_label = f"Renaming {total} asset{'s' if total != 1 else ''} ..."
    with unreal.ScopedSlowTask(total, task_label) as slow_task:
        slow_task.make_dialog(True)

    for i in range(len(assets)):
        asset = assets[i]

        if slow_task.should_cancel():
            unreal.log_warning("User cancelled the rename operation.")
            break
        slow_task.enter_progress_frame(1, f"Renaming {asset.get_name()}")

        old_name = asset.get_name()
        asset_old_path = asset.get_path_name()
        asset_folder = unreal.Paths.get_path(asset_old_path)

        new_name = generate_new_name_for_asset(asset, new_prefix, old_prefix)
        new_path = asset_folder + "/" + new_name

        rename_success = unreal.EditorAssetLibrary.rename_asset(asset_old_path, new_path)
        if not rename_success:
            unreal.log_error("Failed to rename asset" + asset_old_path)


def run():
    selected_assets = get_selected_content_browser_assets()
    rename_assets(selected_assets, new_prefix, old_prefix)


run()