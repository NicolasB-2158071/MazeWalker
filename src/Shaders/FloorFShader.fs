#version 330 core
struct Material {
	sampler2D diffuse;
	vec3 specular;
	float shininess;
};

struct Light {
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

layout (std140) uniform TransformationBlock
{
	mat4 projection;
	mat4 view;
};

uniform Material material;
uniform Light light;

void main()
{
	// Pre calculations
	vec3 norm = normalize(Normal); // Normal
	vec3 lightPosView = vec3(view * vec4(light.position, 1.0)); // light.position in view space

	// Ambient
	vec3 ambient = light.ambient * texture(material.diffuse, TexCoord).rgb;

	// Difuse
	vec3 lightDir = normalize(lightPosView - FragPos); // lightRayVector
	float diff = max(dot(norm, lightDir), 0.0); // Geeft hoek terug
	vec3 diffuse = light.diffuse * diff * texture(material.diffuse, TexCoord).rgb; // Impact van licht

	// Specular
	vec3 viewDir = normalize(-FragPos); // viewPos = (0, 0, 0)
	vec3 reflectDir = reflect(-lightDir, norm); // Berekent licht vector ray
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess); // Hoek tussen licht en directie vector
	vec3 specular = light.specular * (material.specular * spec);

	// Attentuation
	float distance = length(lightPosView - FragPos);
	float attentuation = 1.0 / (light.Kc + light.K1 * distance + light.Kq * distance * distance);

	// Result
	ambient *= attentuation, diffuse *= attentuation, specular *= attentuation;
	FragColor = vec4((ambient + diffuse + specular), 1.0); // Kleur die overblijft is kleur die niet geabsorbeerd is door object (= combinatie van object kleur en licht)
}