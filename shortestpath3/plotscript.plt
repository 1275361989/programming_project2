set xrange [-1.565:-1.540]
set yrange [53.8:53.812]
unset key
plot 'MapPointInfo.dat' with points lc rgb "red" pointtype 7 pointsize 0.8, \
'MapLineInfo.dat' with line lc rgb "red", \
'ShortestPath.dat' with line lc rgb "blue" linewidth 3
