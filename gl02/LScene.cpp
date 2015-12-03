//
//  LScene.cpp
//  gl02
//
//  Created by 鲁飞 on 15/8/17.
//  Copyright (c) 2015年 鲁飞. All rights reserved.
//

#include "LScene.h"
#include "stdio.h"
#include "string.h"
#include "GLUT/glut.h"


void LScene::read(const char *filename){
    // Read information from xml file.
    m_doc = TiXmlDocument(filename);
    bool loadOkay = m_doc.LoadFile();
    
    // faile to load 'phonebookdata.xml'.
    if (!loadOkay) {
        printf( "Could not load scene file %s. Error='%s'. Exiting.\n", filename, m_doc.ErrorDesc() );
        exit( 1 );
    }
}

void LScene::drawScene(){
    TiXmlElement *scene = m_doc.RootElement();
   
    printf("----------start----------\n");
    int i = 0;
    for (TiXmlNode *node=scene->FirstChild("node"); node; node=node->NextSibling()) {
        const char *string = NULL;
        const char *type = NULL;
        float dx=0.0f, dy=0.0f, dz=0.0f;
        float sx=0.0f, sy=0.0f, sz=0.0f;
        float angle=0.0f, x=0.0f, y=0.0f, z=0.0f;
        printf("-----%d------\n",++i);
        for (TiXmlNode *attribute=node->FirstChild(); attribute; attribute=attribute->NextSibling()) {
            string = attribute->Value();
            if (strcmp(string, "type")==0) {
                type = attribute->ToElement()->GetText();
                printf("type:%s\n", type);
            }
            else if (strcmp(string, "translate")==0){
                string = attribute->ToElement()->GetText();
                dx = atof(strtok((char*)string, " "));
                dy = atof(strtok(NULL, " "));
                dz = atof(strtok(NULL, " "));
                printf("translate:%f %f %f\n", dx, dy, dz);
            }
            else if (strcmp(string, "scale")==0){
                string = attribute->ToElement()->GetText();
                sx = atof(strtok((char*)string, " "));
                sy = atof(strtok(NULL, " "));
                sz = atof(strtok(NULL, " "));
                printf("scale:%f, %f, %f\n", sx, sy , sz);
            }
            else if (strcmp(string, "rotate")==0){
                string = attribute->ToElement()->GetText();
                angle = atof(strtok((char*)string, " "));
                x = atof(strtok(NULL, " "));
                y = atof(strtok(NULL, " "));
                z = atof(strtok(NULL, " "));
                printf("rotate:%f %f %f %f\n", angle, x, y, z);
            }
        }
        if (strcmp(type, "wiresphere")==0) {
            glPushMatrix();
            glTranslatef(dx, dy, dz);
            glScalef(sx, sy, sz);
            glRotatef(angle, x, y, z);
            glutWireSphere(0.25, 10, 8);
            glPopMatrix();
        }
        else if (strcmp(type, "wirecube")==0) {
            glPushMatrix();
            glTranslatef(dx, dy, dz);
            glScalef(sx, sy, sz);
            glRotatef(angle, x, y, z);
            glutWireCube(2.0);
            glPopMatrix();
        }
        else if (strcmp(type, "wirecone")==0) {
            glPushMatrix();
            glTranslatef(dx, dy, dz);
            glScalef(sx, sy, sz);
            glRotatef(angle, x, y, z);
            glutWireCone(1.0, 1.0, 10, 12);
            glPopMatrix();
        }
    }
    printf("----------end------------\n");
   }