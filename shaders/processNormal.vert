uniform vec3 cpu_point;
uniform float nbTriangle;
uniform mat3 triangles;

//varying vertexNormal

void main(void) {
	if (cpu_point.xyz == gl_Position.xyz) {
		vec3 vertexNormal = vec3(0.0, 0.0, 0.0);

		//Process normal for all triangles.
		for (int i = 0; i < int(nbTriangle); ++i) {
			vertexNormal += cross(triangles[i][1] - triangles[i][0], triangles[i][2] - triangles[i][0]);
		}

		//Process average normale.
		vertexNormal /= nbTriangle;

		//Change point coord.
		gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex + vec4(vertexNormal, 1.0);
	} else {
		gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
	}
}
