all: compilePhysics link run
debug: debugCompileGeometry debugCompilePhysics debugLink

compileGeometry:
	g++ -c -Wall -std=c++17 src/geometry/Calc.cpp -o bin/o/Calc.o
	g++ -c -Wall -std=c++17 src/geometry/Line.cpp -o bin/o/Line.o
	g++ -c -Wall -std=c++17 src/geometry/Point.cpp -o bin/o/Point.o
	g++ -c -Wall -std=c++17 src/geometry/Shape.cpp -o bin/o/Shape.o
	g++ -c -Wall -std=c++17 src/geometry/Vector.cpp -o bin/o/Vector.o
	ar rcs lib/geometry.a bin/o/Calc.o bin/o/Line.o bin/o/Point.o bin/o/Shape.o bin/o/Vector.o 
	ranlib lib/geometry.a
	rm bin/o/*.o

debugCompileGeometry:
	g++ -g -c -Wall -std=c++17 src/geometry/Calc.cpp -o bin/o/Calc.o
	g++ -g -c -Wall -std=c++17 src/geometry/Line.cpp -o bin/o/Line.o
	g++ -g -c -Wall -std=c++17 src/geometry/Point.cpp -o bin/o/Point.o
	g++ -g -c -Wall -std=c++17 src/geometry/Shape.cpp -o bin/o/Shape.o
	g++ -g -c -Wall -std=c++17 src/geometry/Vector.cpp -o bin/o/Vector.o
	ar rcs lib/geometry.a bin/o/Calc.o bin/o/Line.o bin/o/Point.o bin/o/Shape.o bin/o/Vector.o 
	ranlib lib/geometry.a
	rm bin/o/*.o

compilePhysics:
	g++ -c -Wall -std=c++17 src/physics/Object.cpp -o bin/o/Object.o
	g++ -c -Wall -std=c++17 src/physics/StopWatch.cpp -o bin/o/StopWatch.o
	g++ -c -Wall -std=c++17 src/physics/Display.cpp -o bin/o/Display.o
	g++ -c -Wall -std=c++17 src/physics/World.cpp -o bin/o/World.o
	ar rcs lib/physics.a bin/o/Object.o bin/o/StopWatch.o bin/o/Display.o bin/o/World.o 
	ranlib lib/physics.a
	rm bin/o/*.o

debugCompilePhysics:
	g++ -g -c -Wall -std=c++17 src/physics/Object.cpp -o bin/o/Object.o
	g++ -g -c -Wall -std=c++17 src/physics/StopWatch.cpp -o bin/o/StopWatch.o
	g++ -g -c -Wall -std=c++17 src/physics/Display.cpp -o bin/o/Display.o
	g++ -g -c -Wall -std=c++17 src/physics/World.cpp -o bin/o/World.o
	ar rcs lib/physics.a bin/o/Object.o bin/o/StopWatch.o bin/o/Display.o bin/o/World.o 
	ranlib lib/physics.a
	rm bin/o/*.o

link:
	g++ -lX11 -pthread -Wl,-rpath,bin -Wall -std=c++17 src/main.cpp -o bin/main lib/physics.a lib/geometry.a -L lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network

debugLink:
	g++ -g -lX11 -pthread -Wl,-rpath,bin -Wall -std=c++17 src/main.cpp -o bin/main lib/physics.a lib/geometry.a -L lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network

run:
	./bin/main

compAsm:
	nasm -f elf hello.asm
	ld -m elf_i386 -s -o hello hello.o
	rm hello.o
	./hello