// blaws, ColorTool.c

#include <GLUT/glut.h>
#include <stdio.h>

float currentColor[3];
int currentIndex;

void display(void){
  int i;
  glClear(GL_COLOR_BUFFER_BIT);

  // RGB color bars
  for(i=0;i<3;i++){
    glColor3f(i==0,i==1,i==2);
    glRectf(50*i+100,100,50*i+110,100+300*currentColor[i]);
  }

  // currentIndex indicator
  glColor3f(1,1,0);
  glBegin(GL_TRIANGLES);
  glVertex2f(50*currentIndex+95,80);
  glVertex2f(50*currentIndex+105,90);
  glVertex2f(50*currentIndex+115,80);
  glEnd();

  // central square of current color
  glColor3f(currentColor[0],currentColor[1],currentColor[2]);
  glRectf(250,150,450,350);
  glutSwapBuffers();
}

void reshape(int w,int h){
  glViewport(0,0,w,h);
  glOrtho(0,500,0,500,-1,1);
}

void mouse(int button,int state,int x,int y){
  
}

void keyboard(unsigned char key,int x,int y){

}

void keyboardSpecials(int key,int x,int y){
  switch(key){
  case GLUT_KEY_UP:
    currentColor[currentIndex] += .01;
    if(currentColor[currentIndex]>1.0) currentColor[currentIndex]=1.0;
    break;
  case GLUT_KEY_DOWN:
    currentColor[currentIndex] -= .01;
    if(currentColor[currentIndex]<0.0) currentColor[currentIndex]=0.0;
    break;
  case GLUT_KEY_LEFT:
    currentIndex = (currentIndex+2) % 3;
    break;
  case GLUT_KEY_RIGHT:
    currentIndex = (currentIndex+1) % 3;
    break;
  default:
    break;
  }
  //printf("currentColor[%d] = %f\n",currentIndex,currentColor[currentIndex]);
  glutPostRedisplay();
}

int main(int argc,char* argv[]){
  currentColor[0] = currentColor[1] = currentColor[2] = 1.0;
  currentIndex = 0;

  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(500,500);
  glutInitWindowPosition(100,100);
  glutCreateWindow(argv[0]);

  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutMouseFunc(mouse);
  glutKeyboardFunc(keyboard);
  glutSpecialFunc(keyboardSpecials);

  glutMainLoop();

  return 0;
}
