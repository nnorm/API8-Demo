uniform float uTime;
varying vec2 v_uv;

float a = 1.0;
//uniform vec3 b;
vec3 b = vec3(0.0,0.0,2.2);
vec3 c = vec3(1.0);
float d = 0.1;
//float e = abs(sin(uTime));
uniform float e;

#define MAX_STEP 128
#define EPS 0.001
#define MAX_DIST 128.0

vec3 rotate(vec3 p, float x, float y, float z, float alpha)
{
	mat3 finalMat = mat3(vec3(1.0, 0.0, 0.0),
						 vec3(0.0, 1.0, 0.0),
						 vec3(0.0, 0.0, 1.0));
	if(x != 0.0)
		finalMat *= mat3(vec3(1.0,0.0,0.0),
				  		 vec3(0.0, cos(alpha), -sin(alpha)), 
	      				 vec3(0.0, sin(alpha), cos(alpha))) * x;
	if(y != 0.0)
		finalMat *= mat3(vec3(cos(alpha),0.0,sin(alpha)),
				  		 vec3(0.0, 1.0, 0.0), 
						 vec3(-sin(alpha), 0.0, cos(alpha))) * y;
	if(z != 0.0)
		finalMat *= mat3(vec3(cos(alpha),-sin(alpha),0.0),
				  	   	 vec3(sin(alpha), cos(alpha), 0.0), 
				   		 vec3(0.0, 0.0, 1.0)) * z;
	return finalMat * p;
}

float smin( float a, float b, float k )
{
    float res = exp( -k*a ) + exp( -k*b );
    return -log( res )/k;
}

/* ----------------------------------------- */



float octahedron(vec3 p, float e, float r)
{
	float s = pow(abs(dot(p,vec3(0.577, 0.577, 0.577))), e);
	s += pow(abs(dot(p,vec3(-0.577, 0.577, 0.577))),e);
	s += pow(abs(dot(p,vec3(0.577, -0.577, 0.577))),e);
	s += pow(abs(dot(p,vec3(0.577, 0.577, -0.577))),e);
	s = pow(s, 1.0/e);
	return s-r;
}

float plane(vec3 p, vec4 n)
{
	return dot(p, n.xyz) + n.w;
}

vec3 disp(vec3 p, float freq, float amp, float offset)
{
	vec2 uv1 = p.xy + vec2(-offset,offset);
	vec2 uv2 = p.xz + vec2(offset,-offset);
	float r1 = sqrt(uv1.x*uv1.x + uv1.y*uv1.y);
	float theta1 = atan(uv1.y,uv1.x);
	float r2 = sqrt(uv2.x*uv2.x + uv2.y*uv2.y);
	float theta2 = atan(uv2.y,uv2.x);
	r1 = sin(r1 * freq) * amp;
	r2 = sin(r2 * freq) * amp;
	uv1 = vec2(r1 * cos(theta1), r1 * sin(theta1));
	uv2 = vec2(r2 * cos(theta2), r2 * sin(theta2));
	return vec3(uv1.x+uv2.x,uv1.y + uv2.y,p.z);
}

float scene(vec3 p)
{
	vec3 s = rotate((p+vec3(0.0,1.5*e,0.0)) / vec3(1.0,3.0,1.0),0.0,1.0,1.0,uTime*0.25);
	float octa = octahedron(s*1.5, 64.0, 0.5)/1.5;
	octa += disp(s, 16.0, 0.1 * a,1.75*sin(uTime*d)).x;
	octa += (sin(rotate(s + vec3(uTime*d,0.0,0.0),0.0,0.0,1.0,90.0).x * 25.0) * 0.5 + 0.5) * 0.1 * e;
	return smin(octa,plane(p,vec4(0.0,-1.0,0.0,1.0)),1.0/0.5);
}

/* ----------------------------------------- */

vec3 GetNormal(vec3 p)
{
	vec2 eps = vec2(EPS, 0.0);

	return normalize(vec3(
		scene(p + eps.xyy) - scene(p - eps.xyy),
		scene(p + eps.yxy) - scene(p - eps.yxy),
		scene(p + eps.yyx) - scene(p - eps.yyx)
	));
}

vec4 raymarch(in vec3 ro, in vec3 rd, out bool hit)
{
	vec4 toReturn = vec4(0.0);
	vec3 p = ro;
	float currentDistance = scene(p);
	float d = currentDistance;
	for(int i = 0; i < MAX_STEP; i++)
	{
		if(currentDistance < EPS || d >= MAX_DIST)
		{
			toReturn.xyz = p;
			toReturn.w = d;
			hit = (currentDistance < EPS);
			return toReturn;
		}
		
		currentDistance = scene(p);
		p += rd * currentDistance;
		d += currentDistance;
	}
	toReturn = vec4(p, d);
	hit = false;
	return toReturn;
} 

float ao(vec3 pos, vec3 normal)
{
    float occlusion = 0.0;
    float k = 1.0;
    for(int i = 0; i < 5; i++) 
    {
        float halfR = 0.01 + 0.12 * float(i)/4.0;
        vec3 occlusionPosition = normal * halfR + pos;
        float dist = scene(occlusionPosition);
        occlusion += -(dist-halfR) * k;
        k *= 0.95;
    }
    return clamp(1.0 - 2.0*occlusion, 0.0, 1.0);
}

void main()
{
	vec3 ro = vec3(0.0,-0.25+e, 2.5);
	vec3 rd = normalize(0.0 - vec3(v_uv.x, v_uv.y+e, 1.0));

	bool hit = false;
	vec4 rm = raymarch(ro, rd, hit);

	vec3 N = GetNormal(rm.xyz);

	vec3 lightPos = vec3(ro.xy,b.z);
	vec3 L = lightPos - rm.xyz;
	vec3 V = ro - rm.xyz;

	float NDotL = dot(normalize(L), normalize(N));
	float NDotV = dot(normalize(V), normalize(N)) / 2.5;
	
	if(hit)
		gl_FragColor = 1.0-pow(vec4(c * (NDotL+NDotV),1.0) * ao(rm.xyz, N),vec4(8.0)) ;
	else
		gl_FragColor = vec4((1.0- length(vec2(v_uv.x, ro.y*5.0) - vec2(0.0,1.25))) * 1.0/2.0);
}