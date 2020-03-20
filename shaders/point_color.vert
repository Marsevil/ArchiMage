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
    vec3 point = gl_Vertex;

    if (point == cpu_point)
    {
        vf_color = cpu_color;
        vf_actif = 1.0;
    }

}
