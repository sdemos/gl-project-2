#version 120

// Phong shading fragment shader

// Phong Illumination Parameters
uniform vec4  ia; // ambiant light color
uniform vec4  id; // light source color
uniform vec4  oa; // material ambiant light reflection color
uniform vec4  od; // material diffuse light reflection color
uniform vec4  os; // material specular light reflection color
uniform float ka; // material ambiant light reflection coefficient
uniform float kd; // material diffuse light reflection coefficient
uniform float ks; // material specular light reflection coefficient
uniform float ke; // material specular exponent

uniform vec3 lightPos; // light source position in view coordinates

varying vec3 normal;
varying vec3 view;

void main()
{
    vec3 light = lightPos - view;
    vec3 reflection = normalize(reflect(-light, normal));

    vec4 ambiant  = ka * ia * oa;
    vec4 diffuse  = kd * id * od * max(0.0, dot(normal, light));
    vec4 specular = ks * id * os * pow(max(0.0, dot(-view, reflection)), ke);

    gl_FragColor = ambiant + diffuse + specular;
    //gl_FragColor = vec4(normal, 1.0);
}
