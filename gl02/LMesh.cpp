//
//  LMesh.cpp
//  gl02
//
//  Created by 鲁飞 on 15/8/18.
//  Copyright (c) 2015年 鲁飞. All rights reserved.
//

#include "LMesh.h"
#include "string.h"
#include "GLUT/glut.h"

void LMesh::read(const char *filename){
    TiXmlDocument doc(filename);
    
    bool loadOkay = doc.LoadFile();
    if (!loadOkay) {
        printf( "Could not load scene file %s. Error='%s'. Exiting.\n", filename, doc.ErrorDesc() );
        exit(1);
    }
    
    TiXmlElement *root = doc.RootElement();
    TiXmlNode *mesh = root->FirstChild();
    for (TiXmlNode *attr=mesh->FirstChild(); attr; attr=attr->NextSibling()) {
        if (strcmp(attr->Value(), "vertexnum")==0) {
            this->pointNum = atoi(attr->ToElement()->GetText());
            printf("pointNum:%d\n", this->pointNum);
            this->pointList = new LPoint3f[this->pointNum];
        }
        else if (strcmp(attr->Value(), "vertex")==0){
            const char *str = attr->ToElement()->GetText();
            this->pointList[0].x = atof(strtok((char*)str, " "));
            this->pointList[0].y = atof(strtok(NULL, " "));
            this->pointList[0].z = atof(strtok(NULL, " "));
            printf("point[%d]:%f %f %f\n", 0, this->pointList[0].x, this->pointList[0].y, this->pointList[0].z);
            for (int i=1; i<this->pointNum; i++) {
                this->pointList[i].x = atof(strtok(NULL, " "));
                this->pointList[i].y = atof(strtok(NULL, " "));
                this->pointList[i].z = atof(strtok(NULL, " "));
                printf("point[%d]:%f %f %f\n", i, this->pointList[i].x, this->pointList[i].y, this->pointList[i].z);
            }
        }
        else if (strcmp(attr->Value(), "normalnum")==0){
            this->normalNum = atoi(attr->ToElement()->GetText());
            this->normalList = new LVector3f[this->pointNum];
            printf("normalnum:%d\n", this->normalNum);
        }
        else if (strcmp(attr->Value(), "normal")==0){
            const char *str = attr->ToElement()->GetText();
            this->normalList[0].v1 = atof(strtok((char*)str, " "));
            this->normalList[0].v2 = atof(strtok(NULL, " "));
            this->normalList[0].v3 = atof(strtok(NULL, " "));
            printf("normalList[%d]:%f %f %f\n", 0, this->normalList[0].v1, this->normalList[0].v2, this->normalList[0].v3);
            for (int i=1; i<this->normalNum; i++) {
                this->normalList[i].v1 = atof(strtok(NULL, " "));
                this->normalList[i].v2 = atof(strtok(NULL, " "));
                this->normalList[i].v3 = atof(strtok(NULL, " "));
                printf("normalList[%d]:%f %f %f\n", i, this->normalList[i].v1, this->normalList[i].v2, this->normalList[i].v3);
            }
        }
        else if (strcmp(attr->Value(), "facenum")==0){
            this->faceNum = atoi(attr->ToElement()->GetText());
            this->faceList = new LFace[this->faceNum];
            printf("faceNum:%d\n", this->faceNum);
        }
        else if (strcmp(attr->Value(), "face")==0){
            const char *str = attr->ToElement()->GetText();
            strtok((char*)str, " ");
            for (int i=0; i<this->faceNum; i++) {
                this->faceList[i].vertexNum =  atoi(strtok(NULL, " "));
                this->faceList[i].vertexList = new LVertex[this->faceList[i].vertexNum];
                for (int j=0; j<this->faceList[i].vertexNum; j++) {
                    this->faceList[i].vertexList[j].vertexID = atoi(strtok(NULL, " "));
                    this->faceList[i].vertexList[j].normalID = atoi(strtok(NULL, " "));
                    printf("faceList[%d]vertexList[%d]:%d %d\n", i, j, this->faceList[i].vertexList[j].vertexID, this->faceList[i].vertexList[j].normalID);
                }
            }
        }
    }
}

void LMesh::draw(){
    for (int i=0; i<this->faceNum; i++) {
        glBegin(GL_POLYGON);
        glColor3f(1.0f, 0.0f, 0.0f);
        for (int j=0; j<this->faceList[i].vertexNum; j++) {
            int vertexID = this->faceList[i].vertexList[j].vertexID;
            int normalID = this->faceList[i].vertexList[j].normalID;
            glNormal3f(this->normalList[normalID].v1, this->normalList[normalID].v2, this->normalList[normalID].v3);
            glVertex3f(this->pointList[vertexID].x, this->pointList[vertexID].y, this->pointList[vertexID].z);
            printf("facevertex[%d][%D]:%f %f %f\n",i, j, this->pointList[vertexID].x, this->pointList[vertexID].y, this->pointList[vertexID].z);
        }
        glEnd();
    }

}