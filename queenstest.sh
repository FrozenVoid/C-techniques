#time large nqueens intersections search
gcc -O3 -pipe -march=native  -oqueens queens.c
  echo "Test size:64712 min " 100
   time ./queens 64712 100
