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
uniform sampler2D depthmap;
uniform sampler2D specularmap;

uniform float heightscale;

vec2 ParrallaxMapping(vec2 texCoordsIn, vec3 viewDirIn)
{
	float height =  texture(depthmap, texCoordsIn).r;    
    vec2 p = viewDirIn.xy / viewDirIn.z * (height * heightscale);
    return texCoordsIn - p;   
}

void main()
{
	vec3 viewDir = normalize(data_in.TangentView - data_in.TangentFragPos);
	vec2 texCoords = data_in.TexCoords;

	texCoords = ParrallaxMapping(data_in.TexCoords,  viewDir);
	if(texCoords.x > 1.0 || texCoords.y > 1.0 || texCoords.x < 0.0 || texCoords.y < 0.0)
		discard;

	vec3 normal = texture(normalmap, texCoords).rgb;
	normal = normalize(normal * 2.0 - 1.0);

	vec3 color = texture(diffusemap, texCoords).rgb;

	vec3 ambient = 0.1 * 0.2 * color;
	
	vec3 lightDir = normalize(data_in.TangentLight - data_in.TangentFragPos);

	float diff = max(dot(lightDir, normal), 0.0);
	vec3 diffuse = diff * color;

	vec3 reflectDir = reflect(-lightDir, normal);
	vec3 halfway = normalize(lightDir + viewDir);

	float spec = pow(max(dot(normal, halfway), 0.0), 32.0);
	vec3 specular = texture(specularmap, texCoords).rgb * spec;

	FragColour = vec4(ambient + diffuse + specular, 1.0f);
}