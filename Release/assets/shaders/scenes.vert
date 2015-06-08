in vec3 attrVertexPosition;
uniform mat4 uViewMatrix;
uniform mat4 uProjectionMatrix;
uniform float uTime;
varying vec2 v_uv;

void main()
{
	gl_Position = vec4(attrVertexPosition,1.0);
	v_uv = gl_Position.xy;
}