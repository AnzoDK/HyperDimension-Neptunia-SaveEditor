#!/bin/bash
#BUILD_DIR=$1
#echo "Copying LibNepNep to ${BUILD_DIR}"
rm -rf ./libNepNep
#rm -rf $BUILD_DIR/libNepNep
git clone https://github.com/AnzoDK/HyperDimension-Neptunia-Save-Reasearch
mv ./HyperDimension-Neptunia-Save-Reasearch/libNepNep ./libNepNep
rm -rf ./HyperDimension-Neptunia-Save-Reasearch
cd libNepNep
make
if [[ $? -ne 0 ]]
then
    echo "Failed to build LibNepNep"
    exit 1
fi
#cp ./libnepnep.* ../
cp ./libnepnep.* ./libnepnep.so
cd ..
#cp ./libnepnep.* $BUILD_DIR/
#cp -r ./libNepNep/include $BUILD_DIR/libNepNep
