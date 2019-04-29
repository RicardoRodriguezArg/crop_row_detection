
import bpy
from bpy import context


def unselect_all_object():
    for obj in bpy.data.objects:
        obj.select = False
        

def create_grid():
    me = bpy.data.meshes.new("Grid")
    bm = bmesh.new()
    bmesh.ops.create_grid(bm, x_segments=32, y_segments=32, size=50)
    bmesh.ops.delete(bm, geom=bm.faces, context=3)
    bm.to_mesh(me)

    ob = bpy.data.objects.new("Grid", me)
    sce.objects.link(ob)
    sce.update()

def create_soil_mesh(model_height=2):
    print ("Create Soil Mesh")
    bpy.ops.mesh.primitive_plane_add(radius=10, view_align=False, location=(0, 0, 0))
    bpy.ops.transform.translate(value=(0,0,-1.0 * model_height / 2.0 + 0.2 * model_height))
    return bpy.data.objects['Plane']

def add_modifier(plane_mesh, modifier, type):
    print ("Adding Modifier: {} ".format(modifier))
    plane_mesh.select = True
    bpy.context.scene.objects.active = plane_mesh
    #Add the modifier
    modDec = plane_mesh.modifiers.new(modifier, type)
    bpy.context.scene.update()
    #bpy.ops.object.modifier_add(type)
    #Apply the modifier
    #bpy.ops.object.modifier_apply(modifier)
    
def clear_object(object_name):
    print ("Cleanning Scenes: {}".format(object_name))
    for obj in bpy.data.objects:
        if obj.name == object_name:
            obj.select = True
            bpy.ops.object.delete()


def add_material_to_active_object(material_name):
    ob = bpy.context.active_object
    # Get material
    mat = bpy.data.materials.get(material_name)
    if mat is None:
        # create material
        mat = bpy.data.materials.new(name=material_name)
    # Assign it to object
    if ob.data.materials:
        # assign to 1st material slot
        ob.data.materials[0] = mat
    else:
        # no slots
        ob.data.materials.append(mat)
    return mat

#def setup_soil_material(material):
    
    

plane_name = 'soil_plane'
clear_object(plane_name)
clear_object('Cube')
unselect_all_object()
plane = create_soil_mesh()
plane.name = plane_name
plane.show_wire = True
add_modifier(plane, modifier='Ocean', type='OCEAN')
