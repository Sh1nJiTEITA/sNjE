#version 330
out vec4 FragColor;

// Structs
struct Material {
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	
	float shininess;
};

struct MaterialTex {
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};

struct Light {
	vec3 position;
	
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

// Directional Light

struct DLight {
	vec3 direction;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct PLight {
	vec3 position;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float constant;
	float linear;
	float quadratic;
};

struct SLight {
	vec3 position;
	vec3 direction;
	float cut_off;
	float outer_cut_off;
	float constant;
	float linear;
	float quadratic;
	
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};






#define NR_POINT_LIGHTS 4

in vec3 normal;
in vec3 frag_pos;
in vec2 tex_coo;

uniform vec3 view_pos;

//uniform Material material;
uniform MaterialTex material_tex;

//uniform Light light;
uniform DLight Dlight;
uniform PLight Plight[NR_POINT_LIGHTS];
uniform SLight Slight;

vec3 CalcDLight(DLight light, vec3 normal, vec3 view_direction);
vec3 CalcPLight(PLight light, vec3 normal, vec3 view_direction, vec3 frag_pos);
vec3 CalcSLight(SLight light, vec3 normal, vec3 view_direction, vec3 frag_pos);


void main()
{
	vec3 norm = normalize(normal);
	vec3 view_direction = normalize(view_pos - frag_pos);

	vec3 result_color = CalcDLight(Dlight, norm, view_direction);

	for (int i = 0; i < NR_POINT_LIGHTS; i++)
	{
		result_color += CalcPLight(Plight[i], norm, view_direction, frag_pos);
	}

	result_color += CalcSLight(Slight, norm, view_direction, frag_pos);

	FragColor = vec4(result_color, 1.0);
}

vec3 CalcDLight(DLight light, vec3 normal, vec3 view_direction)
{
	vec3 lightDir = normalize(-light.direction);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(view_direction, reflectDir), 0.0), material_tex.shininess);
    // combine results
    vec3 ambient = light.ambient * vec3(texture(material_tex.diffuse, tex_coo));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material_tex.diffuse, tex_coo));
    vec3 specular = light.specular * spec * vec3(texture(material_tex.specular, tex_coo));
    return (ambient + diffuse + specular);
}


vec3 CalcPLight(PLight light, vec3 normal, vec3 view_direction, vec3 frag_pos)
{
	vec3 lightDir = normalize(light.position - frag_pos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(view_direction, reflectDir), 0.0), material_tex.shininess);
    // attenuation
    float distance = length(light.position - frag_pos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
    // combine results
    vec3 ambient = light.ambient * vec3(texture(material_tex.diffuse, tex_coo));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material_tex.diffuse, tex_coo));
    vec3 specular = light.specular * spec * vec3(texture(material_tex.specular, tex_coo));
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);

}

vec3 CalcSLight(SLight light, vec3 normal, vec3 view_direction, vec3 frag_pos)
{
	vec3 lightDir = normalize(light.position - frag_pos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(view_direction, reflectDir), 0.0), material_tex.shininess);
    // attenuation
    float distance = length(light.position - frag_pos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
    // spotlight intensity
    float theta = dot(lightDir, normalize(-light.direction)); 
    float epsilon = light.cut_off - light.outer_cut_off;
    float intensity = clamp((theta - light.outer_cut_off) / epsilon, 0.0, 1.0);
    // combine results
    vec3 ambient = light.ambient * vec3(texture(material_tex.diffuse, tex_coo));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material_tex.diffuse, tex_coo));
    vec3 specular = light.specular * spec * vec3(texture(material_tex.specular, tex_coo));
    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;
    return (ambient + diffuse + specular);
}




//void main()
//{
//	
//	bool isTexture = true;
//	bool isDLight = true;
//	bool isPLight = true;
//
//
//	if (isTexture) {
////		// lightsource
////		// Ambient 
////		vec3 ambient = light.ambient * texture(material_tex.diffuse, tex_coo).rgb;
////	
////		// Diffuse
////		vec3 norm = normalize(normal);
////		vec3 light_direction = normalize(light.position - frag_pos);
////
////		float diff = max(dot(light_direction, norm), 0.0);
////		vec3 diffuse = light.diffuse * diff * texture(material_tex.diffuse, tex_coo).rgb;
////
////		// Specular
////		vec3 view_direction = normalize(view_pos - frag_pos);
////		vec3 reflect_direction = reflect(-light_direction, norm);
////
////		float spec = pow(max(dot(view_direction, reflect_direction), 0.0001), material_tex.shininess);
////		vec3 specular = light.specular * spec * texture(material_tex.specular, tex_coo).rgb;
////
////		// Result
////		vec3 result_color = ambient + diffuse + specular;
////
////		FragColor =  vec4(result_color, 1.0);
//		
//		vec3 result_color;
//
//		if (isDLight) {
//			// DLight
//			//Ambient 
//			vec3 ambient = Dlight.ambient * texture(material_tex.diffuse, tex_coo).rgb;
//	
//			// Diffuse
//			vec3 norm = normalize(normal);
//			vec3 light_direction = normalize(-Dlight.direction);
//
//			float diff = max(dot(light_direction, norm), 0.0);
//			vec3 diffuse = Dlight.diffuse * diff * texture(material_tex.diffuse, tex_coo).rgb;
//
//			// Specular
//			vec3 view_direction = normalize(view_pos - frag_pos);
//			vec3 reflect_direction = reflect(-light_direction, norm);
//
//			float spec = pow(max(dot(view_direction, reflect_direction), 0.0001), material_tex.shininess);
//			vec3 specular = Dlight.specular * spec * texture(material_tex.specular, tex_coo).rgb;
//
//			// Result
//			result_color += ambient + diffuse + specular;
//
//			FragColor =  vec4(result_color, 1.0);
//		}
//
//		if (isPLight) {
//			vec3 ambient = Plight.ambient * texture(material_tex.diffuse, tex_coo).rgb;
//	
//			// Diffuse
//			vec3 norm = normalize(normal);
//			vec3 light_direction = normalize(Plight.position - frag_pos);
//
//			float diff = max(dot(light_direction, norm), 0.0);
//			vec3 diffuse = Plight.diffuse * diff * texture(material_tex.diffuse, tex_coo).rgb;
//
//			// Specular
//			vec3 view_direction = normalize(view_pos - frag_pos);
//			vec3 reflect_direction = reflect(-light_direction, norm);
//
//			float spec = pow(max(dot(view_direction, reflect_direction), 0.0001), material_tex.shininess);
//			vec3 specular = Plight.specular * spec * texture(material_tex.specular, tex_coo).rgb;
//			
//			float distance = length(Plight.position - frag_pos);
//
//			float attenuation = 1.0 / (Plight.constant + Plight.linear * distance + Plight.quadratic * (distance * distance));    
//
//			ambient  *= attenuation;  
//			diffuse   *= attenuation;
//			specular *= attenuation;
//
//			result_color += ambient + diffuse + specular;
//		}
//		FragColor = vec4(result_color, 1.0);
//	}
//
//	else {
//		// Ambient 
//		vec3 ambient = light.ambient * material.ambient;
//
//		// Diffuse
//		vec3 norm = normalize(normal);
//		vec3 light_direction = normalize(light.position - frag_pos);
//
//		float diff = max(dot(light_direction, norm), 0.0);
//		vec3 diffuse = light.diffuse * (diff * material.diffuse);
//	
//		// Specular
//		vec3 view_direction = normalize(view_pos - frag_pos);
//		vec3 reflect_direction = reflect(-light_direction, norm);
//
//		float spec = pow(max(dot(view_direction, reflect_direction), 0.0001), material.shininess);
//		vec3 specular = light.specular * (spec * material.specular);
//		
//		// Result
//		vec3 result_color = ambient + diffuse + specular;
//
//		FragColor =  vec4(result_color, 1.0);
//	}
//
//	
//}
//
//