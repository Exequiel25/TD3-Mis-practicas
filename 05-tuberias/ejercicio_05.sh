#!/bin/env sh

touch mi_script.sh
echo "Necesitamos ser super usuario para modificar los permisos de ejecución de 'mi_script.sh'"
sudo chmod 744 mi_script.sh
echo "ls -R ~/ | grep network" > ./mi_script.sh
./mi_script.sh

