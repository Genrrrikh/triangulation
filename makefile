all: delanau

delanau: main_Genrikh.o delanau.o
	g++ main_Genrikh.o -o delanau

main_Genrih.o: main_Genrikh.cpp
	g++ -c main_Genrikh.cpp

clean:
	rm -rf *.o delanau
