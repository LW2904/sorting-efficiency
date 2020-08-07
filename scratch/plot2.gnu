load "scratch/common.gnu"

plot "out/insertion_sorted" with linespoints,\
	"out/quick_sorted" with linespoints,\
	"out/heap_sorted" with linespoints,\
	"out/merge_sorted" with linespoints
