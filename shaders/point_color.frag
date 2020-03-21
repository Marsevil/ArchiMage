/* FRAGMENT SHADER - POINT_COLOR */

// Ce qu'on reçoit du vertex shader :
varying float vf_actif; // Et ce qu'on change la couleur
varying vec4 vf_color; // Et la couleur


void main (void)
{
	if (vf_actif == 1.0)
		gl_FragColor = vf_color;
	else
        gl_FragColor = vec4(1.0,1.0,1.0,1.0);
}
