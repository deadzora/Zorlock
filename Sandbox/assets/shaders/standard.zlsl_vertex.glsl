#version 330 core
#define MAX_BONES 200
//type vertex
layout(location = 0) in vec4 a_Position;
layout(location = 1) in vec3 a_Normal;
layout(location = 2) in vec3 a_Color;
layout(location = 3) in vec2 a_TexCoord;
layout(location = 4) in vec4 a_BoneIDs;
layout(location = 5) in vec4 a_Weights;
uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;
uniform mat4 u_Bones[5];
out vec4 v_Position;
out vec4 v_Normal;
out vec3 v_Color;
out vec2 v_TexCoord;
out vec4 v_World;

void main()
{
    vec4 newVertex;
	vec4 newNormal;
	
	mat4 BoneTransform = u_Bones[int(a_BoneIDs.x)] * a_Weights.x;
    BoneTransform += u_Bones[int(a_BoneIDs.y)] * a_Weights.y;
    BoneTransform += u_Bones[int(a_BoneIDs.z)] * a_Weights.z;
    BoneTransform += u_Bones[int(a_BoneIDs.w)] * a_Weights.w;

	v_TexCoord = a_TexCoord;
	v_Normal = vec4(a_Normal,1.0);
	v_Normal = u_Transform*v_Normal;
	v_Normal = normalize(v_Normal);
	v_Color = a_Color;
	v_Position = a_Position;
	//v_Position = Z_Mul(BoneTransform,v_Position);
	v_Position = u_Transform*v_Position;
	v_Position = u_ViewProjection*v_Position;		
	v_World = u_Transform*a_Position;	
	gl_Position=v_Position;
}

