"""
Jednoduchý skript, který exportuje informace o entitách z Blenderu do formátu JSON
"""
import bpy
import os
import json

objs = []
lamps = []

for obj in bpy.context.scene.objects:
    if obj.type == 'EMPTY':
        jsonObj = {}
        for key, value in zip(obj.keys(), obj.values()):
            if not key in ['_RNA_UI', 'cycles', 'cycles_visibility']:
                jsonObj[key] = value
        jsonObj['x'] = obj.location.x
        jsonObj['y'] = obj.location.z
        jsonObj['z'] = obj.location.y
        objs.append(jsonObj)
    elif obj.type == 'LAMP':
        jsonObj = {}
        jsonObj['x'] = obj.location.x
        jsonObj['y'] = obj.location.z
        jsonObj['z'] = obj.location.y
        jsonObj['r'] = obj.color[0]
        jsonObj['g'] = obj.color[1]
        jsonObj['b'] = obj.color[2]
        lamps.append(jsonObj)
        
mapFile = open('/home/martin/CLionProjects/Spacer/Maps/map.json', 'w')
mapFile.write(json.dumps({'entities': objs, "lights": lamps}))
mapFile.close()