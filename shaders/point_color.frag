/* FRAGMENT SHADER - POINT_COLOR */

// Ce qu'on reçoit du vertex shader :
varying float vf_actif; // Et ce qu'on change la couleur
varying vec4 vf_color; // Et la couleur


void main (void)
{
	if (VFactif == 0.0)
		gl_FragColor = vec4(0.0,0.0,1.0,1.0);
	else
        gl_FragColor = vf_color;
}
