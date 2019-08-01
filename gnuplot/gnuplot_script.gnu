https://blog.csdn.net/ouening/article/details/72141345

gnuplot三维

reset   
set isosamples 40   
unset key
set hidden3d
set title "J_0(r^2)"
set xrange [-4:4]
set yrange [-4:4]
set ztics 1
splot besj0(x**2+y**2)
set view 29,53 #Done implicitly by mousing.
set term pngcairo mono enhanced
#set out 'bessel.png'
replot


reset
set isosamples 100
set samples 100
unset key
set title "J_0(r^2)"
set xrange [-4:4]
set yrange [-4:4]
set ztics 1
unset surface
set pm3d
splot besj0(x**2+y**2)


reset
f(x,y) = 3*(1-x)**2*exp(-x**2-(y+1)**2)-10*(x/5-x**3-y**5)*exp(-x**2-y**2)-1/3*exp(-(x+1)**2-y**2) #matlab的peaks函数
set cntrparam levels 10
set contour both
unset sur
set view map
set xrange [-4:4]
set yrange [-4:4]
set iso 100
set samp 100
set key rmargin
splot f(x,y)


reset
set samp 100
set xtics .4
set ytics .4
set parametric
set urange [-pi:pi]
set ztics 1
splot cos(u),sin(3*u),cos(5*u) lw 2


#仅仅获取(0,0)相交二维图形
reset
set view 0,0
set isosample 500,500
set contour base
set cntrparam levels discrete 0
unset surface
set grid
unset key
unset ztics
set xlabel 'x'
set ylabel 'y'
f(x,y) = x**3 + 3*x + 2 - y**2
splot [-10:10][-10:10] f(x,y)


#三维图形和(0,0)平面相交图形
reset   
set isosamples 40   
unset key
set hidden3d
set xlabel 'x'
set ylabel 'y'
f(x,y) = x**3 + 3*x + 2 - y**2
splot f(x,y),0                



gluplot_tutorial.pdf

set xlabel "月份"
set ylabel "降水量（毫米）"
set title "北京市月平均降水量"
unset key
set xrange [0.5:12.5 ]
set xtics 1,1,12
plot "datafile.dat"
plot "datafile.dat " with linespoints
plot "datafile.dat" w lp l c 3 lw 2 pt 7 ps 2

set xlabel "月份"
set ylabel "降水量（毫米）"
set title "各城市月平均降水量"
set xrange [0.5:12.5]
set xtics 1,1 ,12
plot "precipitation.dat" using 1:2 w lp pt 5 title "Beijing",\
"precipitation.dat" using 1:3 w lp pt 7 title "Shanghai"

输出为文件
set xlabel "Month"
set ylabel "Precipitation(mm) "
set xrange [0.5:12.5]
set xtics 1,1,12
set term jpeg
set output "precipitation.jpg"
plot "precipitation.dat " using 1:2 w lp pt 5 title "Beijing",\
"precipitation.dat" using 1:3 w lp pt 7 title "Shanghai "
set output
set term wxt