in vec3 attrVertexPosition;
in vec3 attrVertexNormal;
uniform mat4 uViewMatrix;
uniform mat4 uProjectionMatrix;
uniform float uTime;
varying vec2 v_uv;

void main()
{
	gl_Position = uProjectionMatrix * uViewMatrix * vec4(attrVertexPosition,1.0);
	v_uv = gl_Position.xy;
}