CC=g++
CFLAGS=-c -Wall -Wextra -std=c++17
LDFLAGS=
SOURCES=main.cpp point.cpp segment.cpp circle.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=prog

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

draw: 
	gnuplot
	set term dumb
	set style line 1 lc rgb '#0060ad' lt 1 lw 2 pt 7 ps 1.5
	set xrange [-10:10]
	set yrange [-10:10]
	plot 'polygons.txt' using 1:2 with linespoints linestyle 1, "points.txt" using 1:2 with points linestyle 1, "cicles.txt" using 1:2 with lines linestyle 1