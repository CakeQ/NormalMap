#version 430

out vec4 FragColour;

in Data
{
	vec3 FragPos;
	vec2 TexCoords;
	vec3 TangentLight;
	vec3 TangentView;
	vec3 TangentFragPos;
} data_in;

uniform sampler2D diffusemap;
uniform sampler2D normalmap;

void main()
{
	vec3 normal = texture(normalmap, data_in.TexCoords).rgb;
	normal = normalize(normal * 2.0 - 1.0);

	vec3 color = texture(diffusemap, data_in.TexCoords).rgb;

	vec3 ambient = 0.1 * 0.2 * color;
	
	vec3 lightDir;  //Complete this

	float diff = max(dot(lightDir, normal), 0.0);
	vec3 diffuse = diff * color;

	vec3 viewDir;   //Complete this

	vec3 reflectDir = reflect(-lightDir, normal);
	vec3 halfway = normalize(lightDir + viewDir);

	float spec = pow(max(dot(normal, halfway), 0.0), 32.0);
	vec3 specular = vec3(0.2) * spec;

	FragColour = vec4(ambient + diffuse + specular, 1.0f);
}