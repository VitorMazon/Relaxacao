#!/bin/bash

for i in $(seq 1 5)
do 
  gcc -O2 -lm relax.c -o rl
  ./rl 1e-9 > sol.dat
  gnuplot map.gp
  tempo=$(grep 'tempo = ' sol.dat | cut -d = -f 2)
  echo $i '  ' $tempo >> temp9.dat
done
