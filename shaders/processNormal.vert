uniform vec4 vertex;
uniform float nbTriangle;
uniform mat3[] triangles;

//varying vertexNormal

void main(void) {
	vec3 vertexNormal = {0.0, 0.0, 0.0};

	for (float i = 0; i < nbTriangle; ++i) {
		vertexNormal += cross(triangles[i][1] - triangles[i][0], triangles[i][2] - triangles[i][0]);
	}

	vertexNormal /= nbTriangle;

	if (vertex.xyz == gl_Position.xyz) {
		gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex + vertexNormal;
	}
}
