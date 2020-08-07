set xlabel "Time"
set ylabel "Sample size"

set key left top
set key box

set size square

plot "out/insertion_inverted" with linespoints,\
	"out/insertion_random" with linespoints,\
	"out/insertion_sorted" with linespoints
