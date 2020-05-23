#!/bin/sh -e
. ./common.sh
grub-mkrescue -o "${ISO}" "${SYSROOT}"

