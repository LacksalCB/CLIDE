#!/bin/bash

DEST=$1

# Check source code directory
if [ ! -d $DEST ]; then
    echo "Creating source directory: ${DEST}"
    mkdir ${DEST}
fi


if [ ! -d $DEST/bin ]; then
    echo "Creating bin: ${DEST}/bin"
    mkdir ${DEST}/bin
fi


if [ ! -d $DEST/build ]; then
    echo "Creating build: ${DEST}/build"
    mkdir ${DEST}/build
fi


if [ ! -d $DEST/include ]; then
    echo "Creating include: ${DEST}/include"
    mkdir ${DEST}/include
fi


if [ ! -d $DEST/logs ]; then
    echo "Creating logs: ${DEST}/logs"
    mkdir ${DEST}/logs
fi

if [ ! -d $DEST/src ]; then
    echo "Creating src: ${DEST}/src"
    mkdir ${DEST}/src
fi
