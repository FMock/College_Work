#!/bin/bash
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

echo "Removing old compiled files..."
rm $DIR/*.o
rm $DIR/homework3.out

echo "Precompiling all cpp files..."
for i in $DIR/*.cpp; do
	g++ -c -std=c++11 -pthread $i -o `basename "$i" .cpp`.o
done

echo "Linking and creating final executable..."
g++ -pthread -o $DIR/homework3.out $DIR/*.o

echo ""
echo "----------------------------------"
echo ""
echo "Done!"
echo ""
echo "To run the program make sure you are in the right directory:"
echo "cd $DIR"
echo ""
echo "Then run the command:"
echo "./homework3.out"
echo ""
echo "Alternatively, you can run the file from any directory with this command:"
echo "$DIR/homework3.out"
echo ""
echo "----------------------------------"
echo ""
