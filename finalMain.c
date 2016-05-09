//
//  shaderMain
//
//  Main program for lighting/shading assignment
//
//  This code can be compiled as either C or C++.
//
//  Students should not be modifying this file.
//

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#ifdef __APPLE__
#include <GLUT/GLUT.h>
#include <OpenGL/gl.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/gl.h>
#endif

#include <SOIL.h>

#include "shaderSetup.h"
#include "simpleShape.h"
#include "shapes.h"
#include "viewParams.h"
#include "lightingParams.h"

// How to calculate an offset into the vertex buffer
#define BUFFER_OFFSET(i) ((char *)NULL + (i))

// We need four vertex buffers and four element buffers:
// two for the torus (flat shading and non-flat shading) and
// two for the teapot (flat shading and non-flat shading).
//
// Array layout:
//         column 0      column 1
// row 0:  torus flat    torus non-flat
// row 1:  teapot flat   teapot non-flat
//
GLuint vbuffer[9][2];
GLuint ebuffer[9][2];
int    numVerts[9][2];

// Animation flag
bool animating = false;

// Initial animation rotation angles
float angles[2] = { 0.0f, 0.0f };

// Current shader type:  flat vs. non-flat
int currentShader = SHADE_NOT_FLAT;

// program IDs...for program and shaders
GLuint program, flat, phong, gouraud, grass;

//
// createShape() - create vertex and element buffers for a shape
//
// @param obj - which shape to create
// @param flat   - flat vs. non-flat shading
//
void createShape( int obj, int flat )
{
    // clear any previous shape
    clearShape();

    // make the shape
    makeShape( obj, flat );

    // save the vertex count
    numVerts[obj][flat] = nVertices();

    // get the points for the shape
    float *points = getVertices();
    int dataSize = nVertices() * 4 * sizeof (float);

    // get the normals for the shape
    float *normals = getNormals();
    int ndataSize = nVertices() * 3 * sizeof (float);

    // get the element data for the shape
    GLushort *elements = getElements();
    int edataSize = nVertices() * sizeof (GLushort);

    // generate the vertex buffer
    glGenBuffers( 1, &vbuffer[obj][flat] );
    glBindBuffer( GL_ARRAY_BUFFER, vbuffer[obj][flat] );
    glBufferData( GL_ARRAY_BUFFER, dataSize + ndataSize, 0, GL_STATIC_DRAW );
    glBufferSubData( GL_ARRAY_BUFFER, 0, dataSize, points );
    glBufferSubData( GL_ARRAY_BUFFER, dataSize, ndataSize, normals );

    // generate the element buffer
    glGenBuffers( 1, &ebuffer[obj][flat] );
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, ebuffer[obj][flat] );
    glBufferData( GL_ELEMENT_ARRAY_BUFFER, edataSize,
        elements, GL_STATIC_DRAW );
}

//
// selectBuffers() - bind the correct vertex and element buffers
//
// @param obj - which object to select
// @param flat   - flat vs. non-flat shading
//
// Assumes the correct shader program has already been enabled
//
void selectBuffers( GLuint program, int obj, int flat ) {

    // bind the buffers
    glBindBuffer( GL_ARRAY_BUFFER, vbuffer[obj][flat] );
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, ebuffer[obj][flat] );

    // calculate the number of bytes of vertex data
    int dataSize = numVerts[obj][flat] * 4 * sizeof(float);

    // set up the vertex attribute variables
    GLuint vPosition = glGetAttribLocation( program , "vPosition" );
    glEnableVertexAttribArray( vPosition );
    glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0,
                           BUFFER_OFFSET(0) );

    GLuint vNormal = glGetAttribLocation( program, "vNormal" );
    glEnableVertexAttribArray( vNormal );
    glVertexAttribPointer( vNormal, 3, GL_FLOAT, GL_FALSE, 0,
                           BUFFER_OFFSET(dataSize) );
}


// Verify shader program creation
static void checkShaderError( GLuint program, const char *which )
{
    if( !program ) {
#ifdef __cplusplus
        cerr << "Error setting " << which << " shader - "
             << errorString(shaderErrorCode) << endl;
#else
        fprintf( stderr, "Error setting up %s shader - %s\n",
            which, errorString(shaderErrorCode) );
#endif
        exit(1);
    }
}


// OpenGL initialization
void init()
{
    phong = shaderSetup( "phong.vert", "phong.frag" );
    checkShaderError( phong, "phong" );

    // Default shader program
    program = phong;

    // Create all four objects
    createShape( OBJ_TORUS, SHADE_NOT_FLAT );
    createShape( OBJ_TEAPOT, SHADE_NOT_FLAT );
    createShape( OBJ_HOUSE, SHADE_NOT_FLAT );
    createShape( OBJ_TALL_TREE, SHADE_NOT_FLAT );
    createShape( OBJ_LEAF_BALL, SHADE_NOT_FLAT );
    createShape( OBJ_LUMPY_TREE, SHADE_NOT_FLAT );

    // lets set up some shaders!
    int width, height;
    unsigned char *grassImage = SOIL_load_image("grass.jpg", &width, &height, 0, SOIL_LOAD_RGB);
    glGenTextures(1, &grass);
    glBindTexture(GL_TEXTURE_2D, grass);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, grassImage);
    glGenerateMipmap(GL_TEXTURE_2D);
    SOIL_free_image_data(grassImage);

    // Some openGL initialization...probably best to keep
    glEnable( GL_DEPTH_TEST );
    glEnable( GL_CULL_FACE );
    glCullFace( GL_BACK );
    glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
    glDepthFunc( GL_LEQUAL );
    glClearDepth( 1.0f );
}

void display ()
{
    // clear and draw params..
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the correct program
    glUseProgram(program);


    // set up viewing and projection parameters
    setUpFrustum(program);

    // set up the camera
    setUpCamera(program,
        1.0f, 4.0f, 6.0f,
        0.3f, 1.8f, 0.0f,
        0.0f, 1.0f, 0.0f
    );

    // TALL TREE //
    // set up material properties for the tall tree
    setUpPhong(program, OBJ_TALL_TREE);
    // set up transformations for the tall tree
    setUpTransforms(program,
        0.2f, 0.34f, 0.2f,
        0.0f, 210.0f, 0.0f,
        -1.5f, -0.5f, -1.5f
    );

    // draw the tall tree
    selectBuffers(program, OBJ_TALL_TREE, currentShader);
    glDrawElements(GL_TRIANGLES, numVerts[OBJ_TALL_TREE][currentShader],
            GL_UNSIGNED_SHORT, (void *)0);

    // SMALLER LEAF BALL //
    // set up material properties for the smaller leaf ball
    setUpPhong(program, OBJ_LEAF_BALL);
    // set up transformations for the smaller leaf ball
    setUpTransforms(program,
        0.15f, 0.15f, 0.15f,
        0.0f, 210.0f, 60.0f,
        -0.8f, 2.4f, -1.5f
    );

    // draw the smaller leaf ball
    selectBuffers(program, OBJ_LEAF_BALL, currentShader);
    glDrawElements(GL_TRIANGLES, numVerts[OBJ_LEAF_BALL][currentShader],
        GL_UNSIGNED_SHORT, (void *)0);

    // LARGER LEAF BALL //
    // set up material properties for the larger leaf ball
    setUpPhong(program, OBJ_LEAF_BALL);
    // set up transformations for the larger leaf ball
    setUpTransforms(program,
        0.3f, 0.3f, 0.3f,
        0.0f, 210.0f, 0.0f,
        -1.4f, 3.5f, -1.5f
    );

    // draw the larger leaf ball
    selectBuffers(program, OBJ_LEAF_BALL, currentShader);
    glDrawElements(GL_TRIANGLES, numVerts[OBJ_LEAF_BALL][currentShader],
        GL_UNSIGNED_SHORT, (void *)0);

    // LUMPY TREE //
    // set up material properties for the lumpy tree
    setUpPhong(program, OBJ_LUMPY_TREE);
    // set up transformations for the lumpy tree
    setUpTransforms(program,
        0.35f, 0.5f, 0.35f,
        0.0f, 120.0f, 0.0f,
        2.1f, 0.0f, -2.5f
    );

    // draw the lumpy tree
    selectBuffers(program, OBJ_LUMPY_TREE, currentShader);
    glDrawElements(GL_TRIANGLES, numVerts[OBJ_LUMPY_TREE][currentShader],
        GL_UNSIGNED_SHORT, (void *)0);

    // HOUSE //
    // set up material properties for the house
    setUpPhong(program, OBJ_HOUSE);
    // set up transformations for the house
    setUpTransforms(program,
        0.25f, 0.35f, 0.25f,
        -10.0f, 135.0f, 0.0f,
        -0.1f, 0.0f, -1.5f
    );

    // draw the house
    selectBuffers(program, OBJ_HOUSE, currentShader);
    glDrawElements(GL_TRIANGLES, numVerts[OBJ_HOUSE][currentShader],
        GL_UNSIGNED_SHORT, (void *)0);

    // swap the buffers
    glutSwapBuffers();
}


void keyboard (unsigned char key, int x, int y)
{
    switch (key) {

        //case '1':    // flat shading
        //    program = flat;
        //    currentShader = SHADE_FLAT;
        //    break;

        //case '2':    // Gouraud shading
        //    program = gouraud;
        //    currentShader = SHADE_NOT_FLAT;
        //    break;

        //case '3':    // Phong shading
        //    program = phong;
        //    currentShader = SHADE_NOT_FLAT;
        //    break;

        case 'a':    // animate
            animating = true;
            break;

        case 's':    // stop animating
            animating = false;
            break;

        case 033:   // terminate the program
        case 'q': case 'Q':
            exit(0);
            break;
    }

    glutPostRedisplay();
}

// Animate the objects (maybe)
void animate (void) {
    if(animating) {
        angles[OBJ_TORUS]  += 2;
        angles[OBJ_TEAPOT] += 1;
        glutPostRedisplay();
    }
}

int main (int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(600, 600);
    glutCreateWindow("CG - Final Project");

#ifndef __APPLE__
    glewInit();
#endif

    init();

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutIdleFunc(animate);

    glutMainLoop();
    return 0;
}
