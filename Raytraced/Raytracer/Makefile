CC = g++
PROG = PPMRaytracer
CAM = Camera
SC = Scene
SCO = SceneObjects
MATH = RaytracerMath
F = FractalGeneration


all: $(PROG)

$(PROG): $(PROG).o
	$(CC) $(CFLAGS) -o $@ $< $(F).o $(CAM).o $(SC).o $(SCO).o $(MATH).o

$(PROG).o: $(PROG).cpp $(PROG).h $(F).o $(CAM).o $(SC).o $(SCO).o $(MATH).o 
	$(CC) $(CFLAGS) -c $<

$(F).o: $(F).cpp $(SCO).o $(MATH).o
	$(CC) $(CFLAGS) -c $<

$(CAM).o: $(CAM).cpp $(CAM).h $(SC).o $(SCO).o $(MATH).o
	$(CC) $(CFLAGS) -c $<

$(SC).o: $(SC).cpp $(SC).h $(SCO).o
	$(CC) $(CFLAGS) -c $<

$(SCO).o: $(SCO).cpp $(SCO).h $(MATH).o
	$(CC) $(CFLAGS) -c $<

$(MATH).o: $(MATH).cpp $(MATH).h
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o $(PROG) \#*

cleani:
	rm *.ppm *.png
