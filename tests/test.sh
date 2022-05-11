FILES="testCoord
testFieldAir
testFieldBorder
testFieldClay
testFieldRock
testFieldLava
testItem
testMap
testPlayerHuman
testPlayerMonster"

for i in $FILES
do
	make -j12 debug/$i
done

for j in $FILES
do
	valgrind debug/$j
done
