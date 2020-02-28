# super simple makefile
# call it using 'make NAME=name_of_code_file_without_extension'
# (assumes a .cpp extension)
NAME = snake

#
# Add $(MAC_OPT) to the compile line for Mac OSX.
MAC_OPT = "-I/opt/X11/include"

all:
	@echo "Compiling..."
<<<<<<< HEAD
	g++ -o $(NAME) $(NAME).cpp -L/usr/X11R6/lib -lX11 -lstdc++ $(MAC_OPT)
=======
	g++ -g -o $(NAME) $(NAME).cpp -L/opt/X11/lib -lX11 -lstdc++ $(MAC_OPT)
>>>>>>> d6e3ff51e286dc507d30a4fd2cb6a9910167fdc2

run: all
	@echo "Running..."
	./$(NAME) 

clean:
<<<<<<< HEAD
	-rm animation clipping doublebuffer drawing drawing.min 
	-rm eventloop eventloop.min hello.min null null.min openwindow openwindow.min
=======
	rm ./snake
>>>>>>> d6e3ff51e286dc507d30a4fd2cb6a9910167fdc2
