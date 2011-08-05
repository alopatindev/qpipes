#!/bin/bash

[[ $DISPLAY == "" ]] && export DISPLAY=:0

./configure posix debug

time make && (
    [[ $1 == 'd' ]] && gdb ./qpipes || gdb --eval-command=r --eval-command=q --eval-command=where ./qpipes
)
