OBJ1 = app.cpp
OBJ2 = bitmap.cpp

all: $(OBJ1) $(OBJ2)
	g++ $(OBJ1) $(OBJ2) -o DitherApp
