#!/bin/bash
#A small script that generates 10000 dice rolls inside dice.txt using an installed instance of pick!
for i in {1..10000}; do pick 1 2 3 4 5 6 >> dice.txt; done
exit 0
