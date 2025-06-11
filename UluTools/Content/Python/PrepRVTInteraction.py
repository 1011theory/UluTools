# This script lets us automatically add a virtual texture that a static mesh can draw in. Useful when you don't want to
# affect currently drawn in RVTs on selected meshes and edit them all once, and to enable artists to configure this as they are working

import unreal

def prep_meshes_for_rvt_interaction():
    actors = unreal.EditorActorSubsystem().get_selected_level_actors()
    for actor in actors:
        if isinstance(actor, unreal.StaticMeshActor):
            sm_comp = actor.static_mesh_component
            if sm_comp is not None:
                new_vt=unreal.load_asset('/Game/AncestralHarvest/Systems/FoliageInteraction/RVT/RVT_HeightCI.RVT_HeightCI')
                if new_vt not in sm_comp.runtime_virtual_textures:
                    sm_comp.runtime_virtual_textures.append(new_vt)


def run():
    prep_meshes_for_rvt_interaction()


run()
