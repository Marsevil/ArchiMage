/* VERTEX SHADER - POINT_COLOR */

// Ce qu'on reçoit du CPU :
//uniform vec3 cpu_point; // Le point dont on doit changer la couleur
uniform vec4 cpu_color; // La couleur
// test:
uniform vec3 S1;
uniform vec3 S2;
uniform vec3 S3;

// Ce qu'on transmet au fragment shader :
varying float vf_actif; // Et ce qu'on change la couleur
varying vec4 vf_color; // Et on lui passe la couleur



void main(void)
{
    vf_actif = 0.0;
    vf_color = cpu_color;

    if (gl_Vertex.xyz == S1.xyz || gl_Vertex.xyz == S2.xyz || gl_Vertex.xyz == S3.xyz)
    {
        vf_actif = 1.0;
    }

    gl_Position = gl_Vertex;
}
