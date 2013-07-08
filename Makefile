all: colorTool

colorTool: colorTool.c font.c
	gcc colorTool.c font.c -o colorTool -framework GLUT -framework OpenGL

clean:
	rm -f colorTool *~
