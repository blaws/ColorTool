all: colorTool

colorTool: colorTool.c
	gcc colorTool.c -o colorTool -framework GLUT -framework OpenGL

clean:
	rm -f colorTool *~
