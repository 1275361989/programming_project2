set xrange [-1.564000:-1.543100]
set yrange [53.8016:53.811]
unset key
plot 'mappointinfo.dat' with points lc rgb "red" pointtype 7 pointsize 0.8, \
'maplineinfo.dat' with line lc rgb "red", \
'shortestpath.dat' with line lc rgb "blue" linewidth 3 
