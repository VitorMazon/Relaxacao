set terminal pdf enhanced font 'Times New Roman'
set output "edp1.pdf"
set view map
set nokey
#set xrange [0:1]
#set yrange [0:2]
set size square
#f(x,y)=(x-y)**2
plot "sol.dat" matrix w image
set output
