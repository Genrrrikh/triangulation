all: triangulation

triangulation: main_Genrikh.o Graphics.o delanau.o
	g++ main_Genrikh.o delanau.o Graphics.o -lglut -lGLU -lGL -o triangulation

main_Genrikh.o: main_Genrikh.cpp
	g++ -c main_Genrikh.cpp

delanau.o: delanau.cpp
	g++ -c delanau.cpp

Graphics.o: Graphics.cpp
	g++ -c Graphics.cpp

clean:
	rm -rf *.o triangulation
