set xrange [-1.565:-1.540]
set yrange [53.8:53.812]
set multiplot
plot 'D:\HuHudoc\CTestprogram\shortestpath\MapPointInfo.dat' with points lc rgb "red" pointtype 7 pointsize 0.8
plot 'D:\HuHudoc\CTestprogram\shortestpath\MapLineInfo.dat' with line lc rgb "red" 