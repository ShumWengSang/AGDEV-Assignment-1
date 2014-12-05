#include "Obj.h"


Obj::Obj()
{
}


Obj::~Obj()
{
}

Mesh * Obj::LoadObj(char *filename) {
	int vc = 0, nc = 0, tc = 0, fc = 0;
	char buf[256]; FILE * fp = fopen(filename, "r");

	if (fp == NULL)
	{
		std::cout << "ERROR IN LOADING OBJ" << std::endl;
		return 0;
	}

	Mesh * pMesh = (Mesh *)malloc(sizeof (Mesh));
	// initialise values in (*p) 
	// Count elements 
	pMesh->noNormals = pMesh->noTexCoords = pMesh->noVertices = pMesh->noFaces = 0;
	while (!feof(fp)) {
		if (!fgets(buf, 256, fp)) break; // read one line 
		if (!strncmp("vn ", buf, 3)) pMesh->noNormals++;
		else if (!strncmp("vt ", buf, 3)) pMesh->noTexCoords++;
		else if (!strncmp("v ", buf, 2)) pMesh->noVertices++;
		else if (!strncmp("f ", buf, 2)) pMesh->noFaces++;
	}
	pMesh->vertices = (Vertex *)malloc(pMesh->noVertices * sizeof (Vertex)); // You have do the same for normals, texture coords, faces
	pMesh->normals = (Vertex *)malloc(pMesh->noNormals * sizeof (Vertex));
	pMesh->texCoords = (Vertex *)malloc(pMesh->noTexCoords * sizeof (Vertex)); // You have do the same for normals, texture coords, faces
	pMesh->faces = (Face *)malloc(pMesh->noFaces * sizeof (Face)); // You have do the same for normals, texture coords, faces
	fseek(fp, 0, SEEK_SET); // reset file ptr to beginning 
	while (!feof(fp)) {
		fgets(buf, 256, fp);
		if (!strncmp("vn ", buf, 3))
		{
			sscanf((buf + 2), "%f%f%f",
				&pMesh->normals[nc].x,
				&pMesh->normals[nc].y,
				&pMesh->normals[nc].z);
			nc++;// process vn 
		}
		else if (!strncmp("vt ", buf, 3))
		{
			sscanf((buf + 2), "%f%f",
				&pMesh->texCoords[tc].u,
				&pMesh->texCoords[tc].v);
			tc++;
		}// process vt 
		else if (!strncmp("v ", buf, 2))
		{
			sscanf((buf + 2), "%f%f%f",
				&pMesh->vertices[vc].x,
				&pMesh->vertices[vc].y,
				&pMesh->vertices[vc].z);
			vc++;
		}// process v 
		else if (!strncmp("f ", buf, 2))
		{
			char * pSp = NULL; int ii = 0;
			Face * pf = &pMesh->faces[fc];
			for (int i = 0; i < strlen(buf); i++)
			if (buf[i] == '/') ii++; // no of '/' 
			pf->vCount = ii / 2; // no of vertices 
			pf->vIndices = (int *)malloc(pf->vCount * sizeof (int));
			pf->nIndices = (int *)malloc(pf->vCount * sizeof (int));
			pf->tcIndices = (int *)malloc(pf->vCount * sizeof (int));
			pSp = strtok((buf + 2), " \t\n");
			for (int i = 0; pSp; pSp = strtok(NULL, " \t\n"), i++)
			{
				sscanf(pSp, "%d/%d/%d", &pf->vIndices[i], &pf->tcIndices[i], &pf->nIndices[i]);
				pf->vIndices[i] --;
				pf->tcIndices[i] --;
				pf->nIndices[i] --;
			}
			fc++;
		}// process f 
	} fclose(fp); // close file
	TheMesh = pMesh;
	return pMesh;
}

void Obj::RenderMesh() {
	glPushMatrix();
	//glEnable(GL_TEXTURE_2D);
	glColor3f(1, 1, 1);
	//glBindTexture(GL_TEXTURE_2D, theTexture.texID);
	for (int i = 0; i < TheMesh->noFaces; i++) {
		Face * pf = &TheMesh->faces[i];
		glBegin(GL_POLYGON);
		for (int j = 0; j < pf->vCount; j++) {
			glTexCoord2f(TheMesh->texCoords[pf->tcIndices[j]].u,
				TheMesh->texCoords[pf->tcIndices[j]].v);
			//glNormal3f(TheMesh->normals[pf->nIndices[j]].x,
				//TheMesh->normals[pf->nIndices[j]].y,
				//TheMesh->normals[pf->nIndices[j]].z);
			glVertex3f(TheMesh->vertices[pf->vIndices[j]].x,
				TheMesh->vertices[pf->vIndices[j]].y,
				TheMesh->vertices[pf->vIndices[j]].z);
		}
		glEnd();
	}
	//glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}