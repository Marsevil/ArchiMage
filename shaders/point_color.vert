/* VERTEX SHADER - POINT_COLOR */

// Ce qu'on reçoit du CPU :
uniform vec3 cpu_point; // Le point dont on doit changer la couleur
uniform vec4 cpu_color; // La couleur

// Ce qu'on transmet au fragment shader :
varying float vf_actif; // Et ce qu'on change la couleur
varying vec4 vf_color; // Et on lui passe la couleur



void main(void)
{
    vf_actif = 0.0;
    vf_color = cpu_color;
    gl_PointSize = 1.0;
    float delta = 0.0;

    if (gl_Vertex.xyz == cpu_point.xyz)
    {
        gl_PointSize = 10.0;
        vf_actif = 1.0;
    }

    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}
