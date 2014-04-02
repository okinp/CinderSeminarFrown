#version 120
uniform float scale;
varying vec3 v;
varying vec3 N;
#define M_PI 3.1415926535897932384626433832795
vec4 applyDeformer( vec4 pos )
{
    vec4 deformed;
    deformed.x = pos.x + scale*sin(2.0*M_PI*(pos.z+2.5)/5.0);
    deformed.y = pos.y - scale*cos(2.0*M_PI*(pos.z+2.5)/5.0 +0.5);
    deformed.z = pos.z;
    deformed.w = pos.w;
    return deformed;
}

void main()
{
	v = vec3(gl_ModelViewMatrix * gl_Vertex);       
	N = normalize(gl_NormalMatrix * gl_Normal);
    
    //Deformer
    
    vec4 currentVert = gl_Vertex;
    vec4 newVertexPos = applyDeformer( currentVert );
    gl_Position = gl_ModelViewProjectionMatrix*newVertexPos;
    
}
