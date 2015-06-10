uniform float uTime;
varying vec4 v_pos;
varying vec3 v_normal;
varying vec3 v_lightpos;
void main(void) { 
	vec3 lightDir = (v_pos.xyz - v_lightpos);
   vec3 camDir = (v_pos.xyz - vec3(0.0, 10.0, 20.0));
   float NDotL = dot(normalize(v_normal), normalize(lightDir)) * sin(dot(normalize(v_normal), normalize(camDir)));
	gl_FragColor = vec4(v_normal, 1.0) * NDotL;
}