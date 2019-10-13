import bpy

class CurveCreator():
	def __init__(self, x_points, y_points, plane):
		self.x_list = x_points
		self.y_list = y_points
		self.z_list = None
		self.plane = plane

