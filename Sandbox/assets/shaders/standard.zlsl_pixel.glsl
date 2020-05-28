#version 330 core
#define NUM_LIGHTS 16
struct lightbase
{
	vec4 lightpos;   
    vec4 lightcolor;
	float radius;
    float strength;
};
//type fragment
layout(location = 0) out vec4 color;
in vec4 Z_Position;
in vec4 v_Normal;
in vec3 v_Color;
in vec2 v_TexCoord;
in vec4 v_World;
uniform lightbase lights[NUM_LIGHTS];
uniform vec4 u_Ambient;
uniform sampler2D u_Texture;

void main()
{
	vec4 pixelcolor = texture(u_Texture, v_TexCoord);
	vec4 appliedlight = vec4(0,0,0,1);
	appliedlight += u_Ambient;
	
	for (int i = 0; i < NUM_LIGHTS; i++)
	{
		vec4 vectortolight = normalize(lights[i].lightpos - v_World);		
		float diffuseintensity = max(dot(vectortolight, v_Normal), 0);
		float distancetolight = distance(lights[i].lightpos, v_World);
		float attenuationFactor = (1.0f + lights[i].radius) / (1.0f + 0.5f * distancetolight + 0.1f * pow(distancetolight, 2));
		diffuseintensity *= attenuationFactor;
		vec4 diffuselight = diffuseintensity * lights[i].strength * lights[i].lightcolor;
		appliedlight += diffuselight;
	}
	color = pixelcolor * appliedlight;
	
}

