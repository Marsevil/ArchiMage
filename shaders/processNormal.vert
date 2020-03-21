uniform vec3 cpu_point;
uniform vec3 normal;

//varying vertexNormal

void main(void) {
	if (cpu_point.xyz == gl_Position.xyz) {
		//Change point coord.
		gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex + vec4(normal, 1.0);
	} else {
		//If the point is not the target point we print the same.
		gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
	}
}
