#!/bin/bash


red=$(printf "\033[31m")
green=$(printf "\033[32m")
yellow=$(printf "\033[33m")
blue=$(printf "\033[34m")
magenta=$(printf "\033[35m")
cyan=$(printf "\033[36m")
white=$(printf "\033[37m")
normal=$(printf "\033[m")


THEDATETAG=`date +"%y-%m-%d_%H-%M-%S"`
tar cvfjh TestUbuntu12.10_$THEDATETAG.tar.bz2 test/
 

echo "$green Done.. $normal"
exit 0
