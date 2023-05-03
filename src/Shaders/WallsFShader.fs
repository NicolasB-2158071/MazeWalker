#version 330 core
struct Material {
	sampler2D diffuse;
	vec3 specular;
	float shininess;
};

struct PointLight {
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float Kc;
	float K1;
	float Kq;
};

out vec4 FragColor;

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

#define NUMBER_OF_LIGHTS 10

layout (std140) uniform TransformationBlock
{
	mat4 projection;
	mat4 view;
};

layout (std140) uniform PointLightBlock
{
	PointLight pointLights[NUMBER_OF_LIGHTS];
};

uniform Material material;

vec3 calculatePointLight(int index, vec3 norm);

// Zelfde shader als muren -> code duplicatie
void main()
{
	// Pre calculations
	vec3 norm = normalize(Normal); // Normal
	vec3 output = vec3(0.0);

	for (int i = 0; i < NUMBER_OF_LIGHTS; ++i)
		output += calculatePointLight(i, norm);

	FragColor = vec4(output, 1.0);
}

vec3 calculatePointLight(int index, vec3 norm)
{
	// Pre calculations
	vec3 lightPosView = vec3(view * vec4(pointLights[index].position, 1.0)); // light.position in view space

	// Ambient
	vec3 ambient = pointLights[index].ambient * texture(material.diffuse, TexCoord).rgb;

	// Difuse
	vec3 lightDir = normalize(lightPosView - FragPos); // lightRayVector
	float diff = max(dot(norm, lightDir), 0.0); // Geeft hoek terug
	vec3 diffuse = pointLights[index].diffuse * diff * texture(material.diffuse, TexCoord).rgb; // Impact van licht

	// Specular
	vec3 viewDir = normalize(-FragPos); // viewPos = (0, 0, 0)
	vec3 reflectDir = reflect(-lightDir, norm); // Berekent licht vector ray
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess); // Hoek tussen licht en directie vector
	vec3 specular = pointLights[index].specular * (material.specular * spec);

	// Attentuation
	float distance = length(lightPosView - FragPos);
	float attentuation = 1.0 / (pointLights[index].Kc + pointLights[index].K1 * distance + pointLights[index].Kq * distance * distance);

	// Result
	ambient *= attentuation, diffuse *= attentuation, specular *= attentuation;
	return (ambient + diffuse + specular);
}