#!/bin/sh -e
. ./common.sh
# kill running qemu-system-i386 processes
# (otherwise qemu can't bind to the debugging port)
pgrep qemu-system-i386 -l -f | awk '{print $1}' | xargs -n 1 -I PID kill PID
qemu-system-i386 -cdrom "${ISO}" -s -S --daemonize