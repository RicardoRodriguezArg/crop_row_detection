#!/bin/bash
echo Launching Blender
#calling initial scripts
python clothoides.py
~/Desktop/blender-2.79b-linux-glibc219-x86_64/blender --python create_row_fields.py
