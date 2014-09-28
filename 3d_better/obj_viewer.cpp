// Objects.cpp
// OpenGL SuperBible, Chapter 4
// Demonstrates GLTools built-in objects
// Program by Richard S. Wright Jr.

#include <GLTools.h>	// OpenGL toolkit
#include <GLMatrixStack.h>
#include <GLFrame.h>
#include <GLFrustum.h>
#include <GLBatch.h>
#include <GLGeometryTransform.h>

#include "../obj_importer.h"

#include <math.h>
#ifdef __APPLE__
#include <glut/glut.h>
#else
#define FREEGLUT_STATIC
#include <GL/glut.h>
#endif

/////////////////////////////////////////////////////////////////////////////////
// An assortment of needed classes
GLShaderManager		shaderManager;
GLMatrixStack		modelViewMatrix;
GLMatrixStack		projectionMatrix;
GLFrame				cameraFrame;
GLFrame             objectFrame;
GLFrustum			viewFrustum;

GLTriangleBatch     sphereBatch;
GLTriangleBatch     torusBatch;
GLTriangleBatch     cylinderBatch;
GLTriangleBatch     coneBatch;
GLTriangleBatch     diskBatch;

GLTriangleBatch     toutatisBatch;


GLGeometryTransform	transformPipeline;
M3DMatrix44f		shadowMatrix;


GLfloat vGreen[] = { 0.0f, 1.0f, 0.0f, 1.0f };
//GLfloat vGreen[] = { 0.0f, 0.0f, 0.0f, 1.0f };// black
GLfloat vBlack[] = { 0.0f, 0.0f, 0.0f, 1.0f };
//GLfloat vBlack[] = { 0.0f, 0.0f, 0.0f, 1.0f };


// Keep track of effects step
int nStep = 0;

obj_importer obj(string("C:\\Users\\Administrator\\Documents\\GitHub\\obj_importer\\data.obj"));

void gltMakeToutatis(GLTriangleBatch& toutatisBatch, obj_importer obj){
	M3DVector3f mtmp[3], zero[3];
	zero[0][0] = zero[0][1] = zero[0][2] = zero[1][0] = zero[1][1] = zero[1][2] = zero[2][0] = zero[2][1] = zero[2][2] = 0;
	M3DVector2f zero2[3];
	zero2[0][0] = zero2[0][1] = zero2[0][2] = zero2[1][0] = zero2[1][1] = zero2[1][2] = 0;
	toutatisBatch.BeginMesh(obj.vertices.size());
	for (int i = 0; i < obj.faces.size(); i++){
		if (obj.faces[i].size() == 3){
			for (int j = 0; j < 3; j++){
				mtmp[j][0] = obj.vertices[obj.faces[i][j] - 1].x * 2;
				mtmp[j][1] = obj.vertices[obj.faces[i][j] - 1].y * 2;
				mtmp[j][2] = obj.vertices[obj.faces[i][j] - 1].z * 2;
			}
		}
		toutatisBatch.AddTriangle(mtmp, zero, zero2);
	}
	toutatisBatch.End();
}
///////////////////////////////////////////////////////////////////////////////
// This function does any needed initialization on the rendering context. 
// This is the first opportunity to do any OpenGL related tasks.
void SetupRC()
{
	// Black background
	glClearColor(0.7f, 0.7f, 0.7f, 1.0f );

	shaderManager.InitializeStockShaders();

	glEnable(GL_DEPTH_TEST);

	transformPipeline.SetMatrixStacks(modelViewMatrix, projectionMatrix);

	cameraFrame.MoveForward(-15.0f);
	// Toutatis
	gltMakeToutatis(toutatisBatch, obj);

	// Sphere
	gltMakeSphere(sphereBatch, 3.0, 10, 20);

	// Torus
	gltMakeTorus(torusBatch, 3.0f, 0.75f, 15, 15);

	// Cylinder
	gltMakeCylinder(cylinderBatch, 2.0f, 2.0f, 3.0f, 13, 2);

	// Cone
	gltMakeCylinder(coneBatch, 2.0f, 0.0f, 3.0f, 13, 2);

	// Disk
	gltMakeDisk(diskBatch, 1.5f, 3.0f, 13, 3);
}


/////////////////////////////////////////////////////////////////////////
void DrawWireFramedBatch(GLTriangleBatch* pBatch)
{
	shaderManager.UseStockShader(GLT_SHADER_FLAT, transformPipeline.GetModelViewProjectionMatrix(), vGreen);
	pBatch->Draw();

	// Draw black outline
	glPolygonOffset(-1.0f, -1.0f);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_POLYGON_OFFSET_LINE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glLineWidth(2.5f);
	shaderManager.UseStockShader(GLT_SHADER_FLAT, transformPipeline.GetModelViewProjectionMatrix(), vBlack);
	pBatch->Draw();

	// Restore polygon mode and depht testing
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDisable(GL_POLYGON_OFFSET_LINE);
	glLineWidth(1.0f);
	glDisable(GL_BLEND);
	glDisable(GL_LINE_SMOOTH);
}


///////////////////////////////////////////////////////////////////////////////
// Called to draw scene
void RenderScene(void)
{    
	// Clear the window with current clearing color
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	modelViewMatrix.PushMatrix();
	M3DMatrix44f mCamera;
	cameraFrame.GetCameraMatrix(mCamera);
	modelViewMatrix.MultMatrix(mCamera);

	M3DMatrix44f mObjectFrame;
	objectFrame.GetMatrix(mObjectFrame);
	modelViewMatrix.MultMatrix(mObjectFrame);

	shaderManager.UseStockShader(GLT_SHADER_FLAT, transformPipeline.GetModelViewProjectionMatrix(), vBlack);

	switch(nStep) {
	case 0:
		DrawWireFramedBatch(&toutatisBatch);
		//DrawWireFramedBatch(&sphereBatch);
		break;
	case 1:
		DrawWireFramedBatch(&torusBatch);
		break;
	case 2:
		DrawWireFramedBatch(&cylinderBatch);
		break;
	case 3:
		DrawWireFramedBatch(&coneBatch);
		break;
	case 4:
		DrawWireFramedBatch(&diskBatch);
		break;
	}

	modelViewMatrix.PopMatrix();

	// Flush drawing commands
	glutSwapBuffers();
}


// Respond to arrow keys by moving the camera frame of reference
void SpecialKeys(int key, int x, int y)
{
	if(key == GLUT_KEY_UP)
		objectFrame.RotateWorld(m3dDegToRad(-5.0f), 1.0f, 0.0f, 0.0f);

	if(key == GLUT_KEY_DOWN)
		objectFrame.RotateWorld(m3dDegToRad(5.0f), 1.0f, 0.0f, 0.0f);

	if(key == GLUT_KEY_LEFT)
		objectFrame.RotateWorld(m3dDegToRad(-5.0f), 0.0f, 1.0f, 0.0f);

	if(key == GLUT_KEY_RIGHT)
		objectFrame.RotateWorld(m3dDegToRad(5.0f), 0.0f, 1.0f, 0.0f);

	glutPostRedisplay();
}




///////////////////////////////////////////////////////////////////////////////
// A normal ASCII key has been pressed.
// In this case, advance the scene when the space bar is pressed
void KeyPressFunc(unsigned char key, int x, int y)
{
	if(key == 32)
	{
		nStep++;

		if(nStep > 4)
			nStep = 0;
	}

	switch(nStep)
	{
	case 0: 
		glutSetWindowTitle("Sphere");
		break;
	case 1:
		glutSetWindowTitle("Torus");
		break;
	case 2:
		glutSetWindowTitle("Cylinder");
		break;
	case 3:
		glutSetWindowTitle("Cone");
		break;
	case 4:
		glutSetWindowTitle("Disk");
		break;
	}

	glutPostRedisplay();
}

///////////////////////////////////////////////////////////////////////////////
// Window has changed size, or has just been created. In either case, we need
// to use the window dimensions to set the viewport and the projection matrix.
void ChangeSize(int w, int h)
{
	glViewport(0, 0, w, h);
	viewFrustum.SetPerspective(35.0f, float(w) / float(h), 1.0f, 500.0f);
	projectionMatrix.LoadMatrix(viewFrustum.GetProjectionMatrix());
	modelViewMatrix.LoadIdentity();
}

///////////////////////////////////////////////////////////////////////////////
// Main entry point for GLUT based programs
int main(int argc, char* argv[])
{
	gltSetWorkingDirectory(argv[0]);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_STENCIL);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Sphere");
	glutReshapeFunc(ChangeSize);
	glutKeyboardFunc(KeyPressFunc);
	glutSpecialFunc(SpecialKeys);
	glutDisplayFunc(RenderScene);

	GLenum err = glewInit();
	if (GLEW_OK != err) {
		fprintf(stderr, "GLEW Error: %s\n", glewGetErrorString(err));
		return 1;
	}


	SetupRC();

	glutMainLoop();
	return 0;
}
