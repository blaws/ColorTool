// blaws, ColorTool.c

#include <GLUT/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include "font.h"

float currentColor[8];
int currentIndex,blendType;

void display(void){
  int i;
  char value[100];
  glClear(GL_COLOR_BUFFER_BIT);

  // RGB color bars and labels
  for(i=0;i<4;i++){
    glColor4f(i==0||i==3,i==1||i==3,i==2||i==3,currentColor[3]);
    glRectf(50*i+100,400,50*i+110,400-300*currentColor[i]);
    sprintf(value,"%.0f",255*currentColor[i]);
    glColor4f(i==0||i==3,i==1||i==3,i==2||i==3,1.0);
    glRasterPos2i(50*i+90,420);
    printString(value);
  }
  // second color bars for blending
  if(blendType){
    for(i=0;i<4;i++){
      glColor4f(i==0||i==3,i==1||i==3,i==2||i==3,currentColor[7]);
      glRectf(50*i+550,400,50*i+560,400-300*currentColor[i+4]);
      sprintf(value,"%.0f",255*currentColor[i+4]);
      glColor4f(i==0||i==3,i==1||i==3,i==2||i==3,1.0);
      glRasterPos2i(50*i+540,420);
      printString(value);
    }
  }

  // currentIndex indicator
  int offset = currentIndex>3 ? 340 : 90;
  glColor3f(1,1,0);
  glBegin(GL_TRIANGLES);
  glVertex2f(50*currentIndex+offset+5,440);
  glVertex2f(50*currentIndex+offset+15,430);
  glVertex2f(50*currentIndex+offset+25,440);
  glEnd();

  // central square of current color
  glColor4f(currentColor[0],currentColor[1],currentColor[2],currentColor[3]);
  glBegin(GL_QUADS);
  glVertex2f(300,150);
  glVertex2f(300,350);
  if(blendType==1) glColor4f(currentColor[4],currentColor[5],currentColor[6],currentColor[7]);
  glVertex2f(500,350);
  glVertex2f(500,150);
  glEnd();
  if(blendType==2){
    glColor4f(currentColor[4],currentColor[5],currentColor[6],currentColor[7]);
    glRectf(300,150,500,350);
  }

  // current blend mode identifier
  char message[][11] = {"SOLID","GRADIENT","BLEND"};
  glColor3f(1.0,1.0,1.0);
  glRasterPos2i(blendType==1?360:375,125);
  printString(message[blendType]);

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

void keyboard(unsigned char key,int x,int y){
  switch(key){
  case 'b':
    blendType = (blendType+1) % 3;
    if(!blendType && currentIndex>3) currentIndex=3;
    break;
  case 'q':
  case 27:  // ESC key
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
    currentIndex = (currentIndex+(blendType?7:3)) % (blendType ? 8 : 4);
    break;
  case GLUT_KEY_RIGHT:
    currentIndex = (currentIndex+1) % (blendType ? 8 : 4);
    break;
  default:
    break;
  }
  glutPostRedisplay();
}

int main(int argc,char* argv[]){
  int i;
  for(i=0;i<8;i++) currentColor[i] = 1.0;
  currentIndex = blendType = 0;

  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(800,500);
  glutInitWindowPosition(100,100);
  glutCreateWindow(argv[0]);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

  makeRasterFont();

  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutKeyboardFunc(keyboard);
  glutSpecialFunc(keyboardSpecials);

  glutMainLoop();

  return 0;
}
