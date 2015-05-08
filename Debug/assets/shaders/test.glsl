in vec3 attrVertexPosition;
in vec3 attrVertexNormal;
uniform mat4 uViewMatrix;
uniform mat4 uProjectionMatrix;
uniform float uTime;
varying vec4 v_pos;
varying vec3 v_normal;
varying vec3 v_lightpos;

void main(void) { 
	float rotationSpeed = 0.1;
	mat3 rotateZ = mat3(vec3(cos(uTime*rotationSpeed), -sin(uTime*rotationSpeed), 0.0),
						vec3(sin(uTime*rotationSpeed), cos(uTime*rotationSpeed), 0.0),
						vec3(0.0, 0.0, 1.0));
	vec3 rotated = rotateZ * attrVertexPosition.xyz * 2.0;
	gl_Position = uProjectionMatrix * uViewMatrix * vec4(rotated, 1.0);
	v_pos = gl_Position;
	v_normal = abs(attrVertexNormal);
   	vec3 lp = rotateZ * -vec3(0.0, 10.0, 20.0);
   	v_lightpos = (uProjectionMatrix * uViewMatrix * vec4(lp, 1.0)).xyz;
}