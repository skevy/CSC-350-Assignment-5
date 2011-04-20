#!BPY

""" Registration info for Blender menus:
Name: 'HabuGraphics (.hgs)...'
Blender: 236
Group: 'Export'
Tooltip: 'Export to HabuGraphics file (.hgs)'
"""

__author__  = ("Jeremy M Miller")
__email__   = ["Jeremy, info:bluehabu*net"]
__url__     = ["Author's (Jeremy) homepage, http://dev.bluehabu.com"]
__version__ = "2007/01/13"
__bpydoc__ = """\
This script exports to HabuGraphics format.

Usage:

Run this script from "File->Export" menu.  A pop-up will ask whether you
want to export only selected or all relevant objects.

Known issues:<br>
    none;<br>
"""

# $Id: habugraphics_export.py,v 0.1 2007/01/13 
#------------------------------------------------------------------------
# HabuGraphics exporter for blender 2.36 or above
#
#***************************************************************************//
# HabuGraphics Base Class Interface
#
# Created Jan 13, 2007
# By: Jeremy M Miller
#
# Copyright (c) 2007 Jeremy M Miller.  All rights reserved.
# This source code module, and all information, data, and algorithms
# associated with it, are part of BlueHabu technology (tm).
# 
#***************************************************************************//

import math
import Blender
from Blender import NMesh, Material, Window, Camera, Object, Scene, Lamp

try:
	from os.path import exists, join
	pytinst = 1
except:
	print "Python not installed, Visit http://www.python.org/ to get python."
	pytinst = 0

def write(filename):
	editmode = Window.EditMode()
	if editmode: Window.EditMode(0)
	print "Start export"
	out = file(filename, "w")

	for material in Material.get():
		out.write('Material %s\n' % (material.name))
		out.write('Diffuse %f %f %f %f\n' % (material.R, material.G, material.B, material.getTranslucency()))
		out.write('Ambient %f\n' % (material.amb))
		out.write('Specular %f %f %f %f\n' % (material.getSpecCol()[0], material.getSpecCol()[1], material.getSpecCol()[2], material.getSpecTransp())) 

	for object in Blender.Object.Get():
		if(object.getType() == "Mesh"):
			out.write('%s %s\n' % (object.getType(), object.getName()))
			index_list = []
			mesh = NMesh.GetRawFromObject(object.name)

			for face in mesh.faces:
				for n in range(len(face.v)):
					index_list.append(face.v[n].index)

			out.write('%s\n' % (len(mesh.faces)) )        # Write the number of faces
			out.write('%s\n' % (len(object.data.verts)) ) # Write the number of vertices
			out.write('%s\n' % (len(index_list)) )        # Write the number of indices
			
			for material in mesh.materials:
				out.write('Material %s\n' % material.name)

			out.write('Loc %f %f %f\n' % (object.matrixWorld[3][0], object.matrixWorld[3][1], object.matrixWorld[3][2]))

			for vert in object.data.verts:
				out.write( 'v %f %f %f n %f %f %f\n' % (vert.co.x, vert.co.y, vert.co.z, vert.no.x, vert.no.y, vert.no.z))

			for index in index_list:
				out.write( 'i %s\n' % (index) )

		elif(object.getType() == "Camera"):
			data = object.data
			cam = Camera.get(data.name)
			out.write('Camera %s\n' % (data.name))
			out.write('Right %f %f %f\n' %   (object.getMatrix()[0][0], object.getMatrix()[0][1],  object.getMatrix()[0][2]))
			out.write('Up %f %f %f\n' %      (object.getMatrix()[1][0], object.getMatrix()[1][1],  object.getMatrix()[1][2]))
			out.write('Forward %f %f %f\n' % (object.getMatrix()[2][0], object.getMatrix()[2][1],  object.getMatrix()[2][2]))
			out.write('Loc %f %f %f\n' %     (object.getLocation()[0],  object.getLocation()[1],   object.getLocation()[2]))
			out.write('Far %f\n' %           (cam.getClipEnd()))
			out.write('Near %f\n' %          (cam.getClipStart()))
			out.write('FOV %f\n' %           (2.0 * math.atan(16.0/cam.getLens())))
			
		elif object.getType() == "Lamp":
			data = object.data
			light = Lamp.get(data.name)
			if light.type == Lamp.Types.Lamp:
				out.write('Light Type Unsupported')
			elif light.type == Lamp.Types.Spot:
				out.write('Light Type Unsupported')
			elif light.type == Lamp.Types.Sun:
				out.write('Light %s\n' % (data.name))
				out.write('Type Omni\n')
				out.write('Color %f %f %f\n' % (light.R, light.G, light.B))
				out.write('Right %f %f %f\n' %   (object.getMatrix()[0][0], object.getMatrix()[0][1],  object.getMatrix()[0][2]))
				out.write('Up %f %f %f\n' %      (object.getMatrix()[1][0], object.getMatrix()[1][1],  object.getMatrix()[1][2]))
				out.write('Forward %f %f %f\n' % (object.getMatrix()[2][0], object.getMatrix()[2][1],  object.getMatrix()[2][2]))
				out.write('Loc %f %f %f\n' %     (object.matrixWorld[3][0], object.matrixWorld[3][1], object.matrixWorld[3][2]))
			else:
				out.write('Light Type Unsupported')

	out.close()
	print "End export"

Blender.Window.FileSelector(write, "Export")
