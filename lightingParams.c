//
//  lightingParams
//

#include "lightingParams.h"
#include "shapes.h"

// Add any global variables you need here.

/**
 * This function sets up the lighting, material, and shading parameters
 * for the Phong shader.
 *
 * You will need to write this function, and maintain all of the values
 * needed to be sent to the vertex shader.
 *
 * @param program - The ID of an OpenGL (GLSL) shader program to which
 *    parameter values are to be sent
 *
 */
void setUpPhong (GLuint program, int obj)
{
    // // Phong Illumination Parameters
    // uniform vec4  ia; // ambiant light color
    // uniform vec4  id; // light source color
    // uniform vec4  oa; // material ambiant light reflection color
    // uniform vec4  od; // material diffuse light reflection color
    // uniform vec4  os; // material specular light reflection color
    // uniform float ka; // material ambiant light reflection coefficient
    // uniform float kd; // material diffuse light reflection coefficient
    // uniform float ks; // material specular light reflection coefficient
    // uniform float ke; // material specular exponent
    // uniform vec4  lightPos; // light source position in view coordinates
    GLuint ia = glGetUniformLocation(program, "ia");
    GLuint id = glGetUniformLocation(program, "id");
    GLuint oa = glGetUniformLocation(program, "oa");
    GLuint od = glGetUniformLocation(program, "od");
    GLuint os = glGetUniformLocation(program, "os");
    GLuint ka = glGetUniformLocation(program, "ka");
    GLuint kd = glGetUniformLocation(program, "kd");
    GLuint ks = glGetUniformLocation(program, "ks");
    GLuint ke = glGetUniformLocation(program, "ke");
    GLuint lightPos = glGetUniformLocation(program, "lightPos");

    glUniform4f(ia, 0.5, 0.5, 0.5, 1.0);
    glUniform4f(id, 1.0, 1.0, 1.0, 1.0);

    switch (obj) {
        case OBJ_TORUS:
        case OBJ_TEAPOT:
        default:
            glUniform4f(oa, 0.5, 0.1, 0.9, 1.0);
            glUniform4f(od, 0.89, 0.0, 0.0, 1.0);
            glUniform4f(os, 1.0, 1.0, 1.0, 1.0);
            glUniform1f(ka, 0.5);
            glUniform1f(kd, 0.7);
            glUniform1f(ks, 1.0);
            glUniform1f(ke, 10.0);
            glUniform4f(lightPos, 0.0, 5.0, 2.0, 1.0);
            break;
        case OBJ_HOUSE:
            glUniform4f(oa, 0.5, 0.5, 0.5, 1.0);
            glUniform4f(od, 1.0, 0.0, 1.0, 1.0);
            glUniform4f(os, 1.0, 1.0, 1.0, 1.0);
            glUniform1f(ka, 0.5);
            glUniform1f(kd, 0.7);
            glUniform1f(ks, 1.0);
            glUniform1f(ke, 10.0);
            glUniform4f(lightPos, 0.0, 5.0, 2.0, 1.0);
            break;
        case OBJ_TALL_TREE:
            glUniform4f(oa, 0.5, 0.5, 0.5, 1.0);
            glUniform4f(od, 0.4141, 0.3203, 0.2891, 1.0);
            glUniform4f(os, 0.5, 1.0, 1.0, 1.0);
            glUniform1f(ka, 0.5);
            glUniform1f(kd, 0.7);
            glUniform1f(ks, 0.0);
            glUniform1f(ke, 10.0);
            glUniform4f(lightPos, 0.0, 5.0, 2.0, 1.0);
            break;
        case OBJ_LEAF_BALL:
        case OBJ_LUMPY_TREE:
            glUniform4f(oa, 0.5, 0.5, 0.5, 1.0);
            glUniform4f(od, 0.2265, 0.3711, 0.0430, 1.0);
            glUniform4f(os, 1.0, 1.0, 1.0, 1.0);
            glUniform1f(ka, 0.5);
            glUniform1f(kd, 0.7);
            glUniform1f(ks, 0.0);
            glUniform1f(ke, 5.0);
            glUniform4f(lightPos, 0.0, 5.0, 2.0, 1.0);
            break;
    }
}
