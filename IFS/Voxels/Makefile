CC = g++ -g
PROG = IFS_Voxel
CAM = Camera
#SC = Scene
OCT = Octree
SCO = SceneObjects
MATH = VectorMath
#F = FractalGeneration


all: $(PROG)

$(PROG): $(PROG).o
	$(CC) $(CFLAGS) -o $@ $< $(CAM).o $(OCT).o $(SCO).o $(MATH).o

$(PROG).o: $(PROG).cpp $(PROG).h $(CAM).o $(OCT).o $(SCO).o $(MATH).o 
	$(CC) $(CFLAGS) -c $<

$(CAM).o: $(CAM).cpp $(CAM).h $(OCT).o $(SCO).o $(MATH).o
	$(CC) $(CFLAGS) -c $<

$(OCT).o: $(OCT).cpp $(OCT).h $(SCO).o $(MATH).o
	$(CC) $(CFLAGS) -c $<

$(SCO).o: $(SCO).cpp $(SCO).h $(MATH).o
	$(CC) $(CFLAGS) -c $<

$(MATH).o: $(MATH).cpp $(MATH).h
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o $(PROG) \#*

cleani:
	rm *.ppm *.png
