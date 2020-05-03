#pragma once
#include "VertexBuffer.h"
#include "GraphicsEngine.h"
#include "zMath.h"
#include <vector>

class MarchingCubes
{
public:
	MarchingCubes();
	~MarchingCubes();
	void GetColor(Vector3 & rfColor, Vector3 & rfPosition, Vector3 & rfNormal);
	void NormalizeVector(Vector3 & rfVectorResult, Vector3 & rfVectorSource);
	void vSetTime(float fNewTime);
	float Sample1(float fX, float fY, float fZ);
	float Sample2(float fX, float fY, float fZ);
	float Sample3(float fX, float fY, float fZ);
	void GetNormal(Vector3 & rfNormal, float fX, float fY, float fZ);
	void MarchCube1(float fX, float fY, float fZ, float fScale);
	void MarchTetrahedron(Vector3 * pasTetrahedronPosition, float * pafTetrahedronValue);
	void MarchCube2(float fX, float fY, float fZ, float fScale);
	void MarchCubes();
	float GetOffset(float fValue1, float fValue2, float fValueDesired);
	size_t vertexsize();
	std::vector<Vertex> vertex;
private:
	void (MarchingCubes::*MarchCube) (float fX, float fY, float fZ, float fScale) = NULL;
	float (MarchingCubes::*fSample) (float fX, float fY, float fZ) = NULL;
	Vector3  sSourcePoint[3];
	float   fTime = 0.0f;
	UINT     iDataSetSize = 16;
	float   fStepSize = 1.0f / iDataSetSize;
	float   fTargetValue = 48.0f;
	VertexBuffer* m_vb;
	
};