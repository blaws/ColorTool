// blaws, ColorTool.c

#include <GLUT/glut.h>
#include <stdio.h>
#include <stdlib.h>

float currentColor[6];
int currentIndex,blendEn;

void display(void){
  int i;
  glClear(GL_COLOR_BUFFER_BIT);

  // RGB color bars
  for(i=0;i<3;i++){
    glColor3f(i==0,i==1,i==2);
    glRectf(50*i+100,400,50*i+110,400-300*currentColor[i]);
  }
  // second color bars for blending
  if(blendEn){
    for(i=0;i<3;i++){
      glColor3f(i==0,i==1,i==2);
      glRectf(50*i+500,400,50*i+510,400-300*currentColor[i+3]);
    }
  }

  // currentIndex indicator
  int offset = currentIndex>2 ? 340 : 90;
  glColor3f(1,1,0);
  glBegin(GL_TRIANGLES);
  glVertex2f(50*currentIndex+offset+5,420);
  glVertex2f(50*currentIndex+offset+15,410);
  glVertex2f(50*currentIndex+offset+25,420);
  glEnd();

  // central square of current color
  glColor3f(currentColor[0],currentColor[1],currentColor[2]);
  //glRectf(250,150,450,350);
  glBegin(GL_QUADS);
  glVertex2f(250,150);
  glVertex2f(250,350);
  if(blendEn) glColor3f(currentColor[3],currentColor[4],currentColor[5]);
  glVertex2f(450,350);
  glVertex2f(450,150);
  glEnd();
  glutSwapBuffers();
}

void reshape(int w,int h){
  glViewport(0,0,w,h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0,w,h,0,-1,1);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glutPostRedisplay();
}

void mouse(int button,int state,int x,int y){
  
}

void keyboard(unsigned char key,int x,int y){
  switch(key){
  case 'b':
    blendEn = !blendEn;
    if(!blendEn && currentIndex>2) currentIndex=2;
    break;
  case 'q':
    exit(0);
    break;
  default:
    break;
  }
  glutPostRedisplay();
}

void keyboardSpecials(int key,int x,int y){
  switch(key){
  case GLUT_KEY_UP:
    currentColor[currentIndex] += .025;
    if(currentColor[currentIndex]>1.0) currentColor[currentIndex]=1.0;
    break;
  case GLUT_KEY_DOWN:
    currentColor[currentIndex] -= .025;
    if(currentColor[currentIndex]<0.0) currentColor[currentIndex]=0.0;
    break;
  case GLUT_KEY_LEFT:
    currentIndex = (currentIndex+(blendEn?5:2)) % (blendEn ? 6 : 3);
    break;
  case GLUT_KEY_RIGHT:
    currentIndex = (currentIndex+1) % (blendEn ? 6 : 3);
    break;
  default:
    break;
  }
  //printf("currentColor[%d] = %f\n",currentIndex,currentColor[currentIndex]);
  glutPostRedisplay();
}

int main(int argc,char* argv[]){
  int i;
  for(i=0;i<6;i++) currentColor[i] = 1.0;
  currentIndex = blendEn = 0;

  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(800,500);
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
