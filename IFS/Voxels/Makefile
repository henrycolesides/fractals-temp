CC = g++
PROG = IFS_Voxel
#CAM = Camera
#SC = Scene
SCO = SceneObjects
MATH = VectorMath
#F = FractalGeneration


all: $(PROG)

$(PROG): $(PROG).o
	$(CC) $(CFLAGS) -o $@ $< $(SCO).o $(MATH).o

$(PROG).o: $(PROG).cpp $(PROG).h $(SCO).o $(MATH).o 
	$(CC) $(CFLAGS) -c $<

$(SCO).o: $(SCO).cpp $(SCO).h $(MATH).o
	$(CC) $(CFLAGS) -c $<

$(MATH).o: $(MATH).cpp $(MATH).h
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o $(PROG) \#*

cleani:
	rm *.ppm *.png
