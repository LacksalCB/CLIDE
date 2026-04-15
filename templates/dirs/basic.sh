#!/bin/bash

DEST=$1

if [ ! -d $DEST ]; then
    echo "Creating ${DEST}"
    mkdir ${DEST}
fi

mkdir ${DEST}/bin ${DEST}/build ${DEST}/include ${DEST}/logs ${DEST}/src 
