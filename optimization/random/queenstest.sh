#time large nqueens intersections search
gcc -Ofast queens.c -oqueens
for (( c=1;c<10000;c++ ))
do
  echo "Test size board of side:$c  " 
   time ./queens $c
done

