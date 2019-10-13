#
DIR="input_data"
if [ -d "$DIR" ]; then
  # Take action if $DIR exists. #
  echo "Directory exist ${DIR}!"

fi
else
  ###  Control will jump here if $DIR does NOT exists ###
  echo "Error: ${DIR} not found. Creating input data folder for images."
  mkdir ${DIR}
fi
  echo "Creating ODM docker image"
  docker build -t opendronemap-image .
