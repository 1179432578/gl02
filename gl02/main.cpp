//
//  main.c
//  gl02
//
//  Created by 鲁飞 on 15/8/7.
//  Copyright (c) 2015年 鲁飞. All rights reserved.
//


#include "LCommon.h"
#include "drawitem.h"

void init(){
    srand(clock());
   // glClearColor(0.0f, 0.0f, 1.0f, 0.0f);
    glColor3f(1.0f, 0.0f, 0.0f);
   // gluOrtho2D(-10.0f, 10.0f, -10.0f, 10.0f);
    glViewport(0, 0, 640, 480);
    glEnable(GL_NORMALIZE);
}

bool t = true;
void display(){
    while(t)
    {
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-2.0*64.0/48.0, 2.0*64.0/48.0, -2.0, 2.0, 0.1, 100);
        
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(2.0, 2.0, 2.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
        
        glClear(GL_COLOR_BUFFER_BIT);
        
        LMesh mesh;
        mesh.read("/Users/lufei1/Documents/project/gl02/mesh.xml");
        mesh.draw();
        
        glFlush();
        t = false;
    }
  
}

void mouse(int button, int state, int x, int y){
    if (state == GLUT_DOWN) {
        if (button == GLUT_LEFT_BUTTON) {
         //   glutPostRedisplay();
        }
    }
    
}

void keyboard(unsigned char keyValue, int x, int y){
    switch (keyValue) {
        case 'q':
            printf("EXIT");
            exit(-1);
            break;
            
        default:
            break;
    }
}


int main(int argc, const char * argv[]) {
    // insert code here...
    glutInit(&argc, (char **)argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize (640, 480);
    glutInitWindowPosition (1000, 100);
    glutCreateWindow ("graphics with opengl");
    glutDisplayFunc(display);
    //glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);
    init();
    glutMainLoop();
    return 0;
}
