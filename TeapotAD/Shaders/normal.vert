#version 430

layout (location = 0) in vec3 VertexPosition;
layout (location = 1) in vec3 VertexNormal;
layout (location = 2) in vec2 VertexUV;
layout (location = 3) in vec3 VertexTangent;
layout (location = 4) in vec3 VertexBiTangent;

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
	data_out.FragPos = vec3(Model * vec4(VertexPosition, 1.0));
	data_out.TexCoords = VertexUV;

	vec3 tangent = normalize(mat3(Model) * VertexTangent);
	vec3 bitangent = normalize(mat3(Model) * VertexBiTangent);
	vec3 normal = normalize(mat3(Model) * VertexNormal);
	mat3 TBN = transpose(mat3(tangent, bitangent, normal));

	data_out.TangentLight = TBN * lightPos;
	data_out.TangentView = TBN * viewPos;
	data_out.TangentFragPos = TBN * data_out.FragPos;

	gl_Position = Projection * View * Model * vec4(VertexPosition, 1.0);
}