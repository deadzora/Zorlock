#version 330 core
#define NUM_LIGHTS 16
struct lightbase
{
	vec4 lightpos;   
    vec4 lightcolor;
	float radius;
    float strength;
};
struct surfaceproperties
{
	float specular;
	float shininess;
};
//type fragment
layout(location = 0) out vec4 color;
in vec4 v_Position;
in vec4 v_Normal;
in vec3 v_Color;
in vec2 v_TexCoord;
in vec4 v_World;
uniform lightbase lights[NUM_LIGHTS];
uniform surfaceproperties u_SurfaceProperties;
uniform vec4 u_Ambient;
uniform vec4 u_ViewPosition;
uniform sampler2D u_Texture;

void main()
{
	vec4 pixelcolor = texture(u_Texture, v_TexCoord);
	vec4 appliedlight = u_Ambient;
	vec4 viewDir = normalize(u_ViewPosition - v_World);
	
    for (int i = 0; i < NUM_LIGHTS; i++)
    {
		vec4 lightDir = normalize(lights[i].lightpos - v_World); 
		vec4 reflectDir = reflect(-lightDir, v_Normal); 
		float spec = pow(max(dot(viewDir, reflectDir), 0.0), u_SurfaceProperties.shininess);
		vec4 specular = (u_SurfaceProperties.specular * spec) * lights[i].lightcolor;  
		float diff = max(dot(v_Normal, lightDir), 0.0);
		float distancetolight = distance(v_World,lights[i].lightpos);
		float attenuationFactor = (1.0f + lights[i].radius) / (1.0f + 0.5f * distancetolight + 0.1f * pow(distancetolight, 2));
		diff *= attenuationFactor;
		vec4 diffuse = diff * lights[i].lightcolor;
		vec4 result = (u_Ambient + diffuse + specular) * pixelcolor;
		appliedlight += result;
    }
	color = pixelcolor * appliedlight;
	
}

