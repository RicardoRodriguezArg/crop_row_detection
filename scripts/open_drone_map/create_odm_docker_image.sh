#!/bin/bash
DIR="input_data"
if [ -d "$DIR" ]; then
  # Take action if $DIR exists. #
  echo "Directory exist ${DIR}!"
else
  ###  Control will jump here if $DIR does NOT exists ###
  echo "Error: ${DIR} not found. Creating input data folder for images."
  mkdir ${DIR}
fi

echo "Building ODM docker image"
docker pull opendronemap/odm:odm_image

docker run -it --rm \
    -v $(pwd)/images:/code/images \
    -v $(pwd)/odm_orthophoto:/code/odm_orthophoto \
    -v $(pwd)/odm_texturing:/code/odm_texturing \
    -v $(pwd)/odm_georeferencing:/code/odm_georeferencing \
    odm_image

