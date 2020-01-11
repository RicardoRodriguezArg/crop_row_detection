Map Compiler
This compiler it is designed to be built from scratch, and it separated in the following stages:
1.- Process input images sequences and generate mesh data, point cloud and finally the output image with georeference points with 
their coordinates assigned
2.Process output image from the previous step to obtain:
  1.- Lanes
  2.- Obstacles
  3.- LandMarks
  4.- Links
  5.- Features Points
4.- Parse previous obtainned features and generate a phisicall representation of the obtainned features.
5.- generate sql data representation from input data (lanes, obstacles,...)
