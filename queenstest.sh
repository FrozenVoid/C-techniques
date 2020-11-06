gcc -O3 -pipe -march=native -oqueens queens.c
for (( c=0; c<=256; c++ ))
do  
  echo "Test size:"$c
   time ./queens $c
done
