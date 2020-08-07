set xlabel "Time"
set ylabel "Sample size"

set key left top
set key box

set size square

plot "out/insertion_sorted" with linespoints,\
	"out/quick_sorted" with linespoints,\
	"out/heap_sorted" with linespoints,\
	"out/merge_sorted" with linespoints
