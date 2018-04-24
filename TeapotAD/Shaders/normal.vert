#version 430

layout (location = 0) in vec3 VertexPosition;
layout (location = 1) in vec3 VertexNormal;
layout (location = 2) in vec2 VertexUV;
layout (location = 3) in vec4 VertexTangent;

out Data
{
	vec3 FragPos;
	vec2 TexCoords;
	vec3 TangentLight;
	vec3 TangentView;
	vec3 TangentFragPos;
} data_out;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

uniform vec3 lightPos;
uniform vec3 viewPos;

void main()
{
	gl_Position = Projection * View * Model * vec4(VertexPosition, 1.0);
	//*********************************************//
	mat3 normalmatrix;  //Complete this
	vec3 tangent;  //Complete this
	vec3 normal;  //Complete this
	vec3 bitangent;  //Complete this
	mat3 TBN;  //Complete this
	//*********************************************//

	data_out.FragPos = vec3(Model * vec4(VertexPosition, 1.0));
	data_out.TexCoords ;  //Complete this
	data_out.TangentLight ;  //Complete this 
	data_out.TangentView ;   //Complete this 
	data_out.TangentFragPos ;   //Complete this
}