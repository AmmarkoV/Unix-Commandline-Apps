#!/bin/bash 
./lddr -n -maxDepth 10 /home/ammar/Documents/3dParty/mbv/trunk/Bin/SynergyTrackerRGBD

./lddr  -maxDepth 10  /home/ammar/Documents/3dParty/mbv/trunk/Bin/SynergyTrackerRGBD 2> test.txt


#Make sure that the linked files are unique
cat test.txt  | sort -u > testU.txt

#Make links for each of the ldd shared object files
while read p; do
  ln -s $p
done < testU.txt

exit 0
