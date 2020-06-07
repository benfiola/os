#!/bin/sh -e
. ./common.sh
cd $BUILD
make copy-headers
make all
make install
make iso
