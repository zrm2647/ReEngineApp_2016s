#include "MyPrimitive.h"
MyPrimitive::MyPrimitive() { }
MyPrimitive::MyPrimitive(const MyPrimitive& other) { }
MyPrimitive& MyPrimitive::operator=(const MyPrimitive& other) { return *this; }
MyPrimitive::~MyPrimitive(void) { super::Release(); }
void MyPrimitive::CompileObject(vector3 a_v3Color)
{
	m_uVertexCount = static_cast<int> (m_lVertexPos.size());
	for (uint i = 0; i < m_uVertexCount; i++)
	{
		AddVertexColor(a_v3Color);
	}
	
	CompleteTriangleInfo(true);
	CompileOpenGL3X();

}
//C--D
//|\ |
//| \|
//A--B
//This will make the triang A->B->C and then the triang C->B->D
void MyPrimitive::AddQuad(vector3 a_vBottomLeft, vector3 a_vBottomRight, vector3 a_vTopLeft, vector3 a_vTopRight)
{
	AddVertexPosition(a_vBottomLeft);
	AddVertexPosition(a_vBottomRight);
	AddVertexPosition(a_vTopLeft);

	AddVertexPosition(a_vTopLeft);
	AddVertexPosition(a_vBottomRight);
	AddVertexPosition(a_vTopRight);
}
void MyPrimitive::GeneratePlane(float a_fSize, vector3 a_v3Color)
{
	if (a_fSize < 0.01f)
		a_fSize = 0.01f;

	Release();
	Init();

	float fValue = 0.5f * a_fSize;

	vector3 pointA(-fValue, -fValue, 0.0f); //0
	vector3 pointB(fValue, -fValue, 0.0f); //1
	vector3 pointC(fValue, fValue, 0.0f); //2
	vector3 pointD(-fValue, fValue, 0.0f); //3

	vector3 pointE(fValue, -fValue, -0.001f); //1
	vector3 pointF(-fValue, -fValue, -0.001f); //0
	vector3 pointG(fValue, fValue, -0.001f); //2
	vector3 pointH(-fValue, fValue, -0.001f); //3

											  //F
	AddQuad(pointA, pointB, pointD, pointC);
	//Double sided
	AddQuad(pointE, pointF, pointG, pointH);

	CompileObject(a_v3Color);
}
void MyPrimitive::GenerateCube(float a_fSize, vector3 a_v3Color)
{
	if (a_fSize < 0.01f)
		a_fSize = 0.01f;

	Release();
	Init();

	float fValue = 0.5f * a_fSize;
	//3--2
	//|  |
	//0--1
	vector3 point0(-fValue, -fValue, fValue); //0
	vector3 point1(fValue, -fValue, fValue); //1
	vector3 point2(fValue, fValue, fValue); //2
	vector3 point3(-fValue, fValue, fValue); //3

	vector3 point4(-fValue, -fValue, -fValue); //4
	vector3 point5(fValue, -fValue, -fValue); //5
	vector3 point6(fValue, fValue, -fValue); //6
	vector3 point7(-fValue, fValue, -fValue); //7

	//F
	AddQuad(point0, point1, point3, point2);

	//B
	AddQuad(point5, point4, point6, point7);

	//L
	AddQuad(point4, point0, point7, point3);

	//R
	AddQuad(point1, point5, point2, point6);

	//U
	AddQuad(point3, point2, point7, point6);

	//D
	AddQuad(point4, point5, point0, point1);

	CompileObject(a_v3Color);
}
void MyPrimitive::GenerateCone(float a_fRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color)
{
	if (a_nSubdivisions < 3)
		a_nSubdivisions = 3;
	if (a_nSubdivisions > 360)
		a_nSubdivisions = 360;

	Release();
	Init();

	//Your code starts here
	float fValue = 0.5f;
	//3--2
	//|  |
	//0--1
	std::vector<vector3> point;
	// angle for cos/sin
	float theta = 0;
	float steps = 2 * PI/ static_cast<float>(a_nSubdivisions);

	// the base of the cone
	point.push_back(vector3(0.0f, 0.0f, 0.0f));

	for (int i = 0; i < a_nSubdivisions; i++) {
		point.push_back(vector3(cos(theta), sin(theta), -a_fHeight));
		theta += steps;
	}

	for (int i = 1; i < a_nSubdivisions; i++) {
		AddTri(point[0], point[i], point[i + 1]);
	}

	AddTri(point[0], point[a_nSubdivisions], point[1]);

	for (int i = 0; i < a_nSubdivisions+1; i++) {
		point.pop_back();
	}

	// the actual cone - basically base with a different center point
	point.push_back(vector3(0.0f, 0.0f, -a_fHeight));

	for (int i = 0; i < a_nSubdivisions; i++) {
		point.push_back(vector3(cos(-theta), sin(-theta), -a_fHeight));
		theta += steps;
	}

	for (int i = 1; i < a_nSubdivisions; i++) {
		AddTri(point[0], point[i], point[i + 1]);
	}

	AddTri(point[0], point[a_nSubdivisions], point[1]);

	for (int i = 0; i < a_nSubdivisions; i++) {
		point.pop_back();
	}

	//Your code ends here
	CompileObject(a_v3Color);
}
void MyPrimitive::GenerateCylinder(float a_fRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color)
{
	if (a_nSubdivisions < 3)
		a_nSubdivisions = 3;
	if (a_nSubdivisions > 360)
		a_nSubdivisions = 360;

	Release();
	Init();

	//Your code starts here
	float fValue = 0.5f;
	//3--2
	//|  |
	//0--1
	std::vector<vector3> point;
	float theta = 0;
	float steps = 2 * PI / static_cast<float>(a_nSubdivisions);

	// first base of cylinder
	point.push_back(vector3(0.0f, 0.0f, 0.0f));

	for (int i = 0; i < a_nSubdivisions; i++) {
		point.push_back(vector3(cos(theta), sin(theta), 0));
		theta += steps;
	}

	for (int i = 1; i < a_nSubdivisions; i++) {
		AddTri(point[0], point[i], point[i + 1]);
	}

	AddTri(point[0], point[a_nSubdivisions], point[1]);

	for (int i = 0; i < a_nSubdivisions + 1; i++) {
		point.pop_back();
	}

	// second base of cylinder
	point.push_back(vector3(0.0f, 0.0f, -a_fHeight));

	for (int i = 0; i < a_nSubdivisions; i++) {
		point.push_back(vector3(cos(-theta), sin(-theta), -a_fHeight));
		theta += steps;
	}

	for (int i = 1; i < a_nSubdivisions; i++) {
		AddTri(point[0], point[i], point[i + 1]);
	}

	AddTri(point[0], point[a_nSubdivisions], point[1]);

	for (int i = 0; i < a_nSubdivisions+1; i++) {
		point.pop_back();
	}

	// the rest of the cylinder
	for (int i = 0; i < a_nSubdivisions + 1; i++) {
		point.push_back(vector3(cos(-theta), sin(-theta), 0));
		theta += steps;
	}

	for (int i = 0; i < a_nSubdivisions + 1; i++) {
		point.push_back(vector3(cos(-theta), sin(-theta), -a_fHeight));
		theta += steps;
	}

	for (int i = 0; i < a_nSubdivisions + 1; i++) {
		AddQuad(point[i], point[i + 1], point[a_nSubdivisions + i], point[a_nSubdivisions + 1 + i]);
	}

	for (int i = 0; i < a_nSubdivisions * 2 + 2; i++) {
		point.pop_back();
	}

	//Your code ends here
	CompileObject(a_v3Color);
}
void MyPrimitive::GenerateTube(float a_fOuterRadius, float a_fInnerRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color)
{
	if (a_nSubdivisions < 3)
		a_nSubdivisions = 3;
	if (a_nSubdivisions > 360)
		a_nSubdivisions = 360;

	Release();
	Init();

	//Your code starts here
	// valus for outer and inner radii
	float fValue = 1.0f * a_fOuterRadius;
	float gValue = 1.0f * a_fInnerRadius;
	//3--2
	//|  |
	//0--1
	//std::vector<vector3> point;
	float theta = 0;
	float steps = 2 * PI / static_cast<float>(a_nSubdivisions);

	// arrays of points for tube
	vector3* points1 = new vector3[a_nSubdivisions];
	vector3* points2 = new vector3[a_nSubdivisions];
	vector3* points3 = new vector3[a_nSubdivisions];
	vector3* points4 = new vector3[a_nSubdivisions];

	// setting the points
	for (int i = 0; i < a_nSubdivisions; i++) {
		points1[i] = vector3(fValue * cos(theta), fValue * sin(theta), -a_fHeight);
		points2[i] = vector3(gValue * cos(theta), gValue * sin(theta), -a_fHeight);
		points3[i] = vector3(fValue * cos(theta), fValue * sin(theta), 0);
		points4[i] = vector3(gValue * cos(theta), gValue * sin(theta), 0);
		theta += steps;
	}

	// connecting the points
	for (int i = 0; i < a_nSubdivisions - 1; i++) {
		AddQuad(points1[i + 1], points1[i], points2[i + 1], points2[i]);
		AddQuad(points3[i], points3[i + 1], points4[i], points4[i + 1]);
		AddQuad(points1[i], points1[i + 1], points3[i], points3[i + 1]);
		AddQuad(points2[i + 1], points2[i], points4[i + 1], points4[i]);
	}

	AddQuad(points1[0], points1[a_nSubdivisions - 1], points2[0], points2[a_nSubdivisions - 1]);
	AddQuad(points3[a_nSubdivisions - 1], points3[0], points4[a_nSubdivisions - 1], points4[0]);
	AddQuad(points1[a_nSubdivisions - 1], points1[0], points3[a_nSubdivisions - 1], points3[0]);
	AddQuad(points2[0], points2[a_nSubdivisions - 1], points4[0], points4[a_nSubdivisions - 1]);

	// memory leaks are bad
	delete[] points1;
	delete[] points2;
	delete[] points3;
	delete[] points4;

	//Your code ends here
	CompileObject(a_v3Color);
}
void MyPrimitive::GenerateTorus(float a_fOuterRadius, float a_fInnerRadius, int a_nSubdivisionsA, int a_nSubdivisionsB, vector3 a_v3Color)
{
	if (a_fOuterRadius <= a_fInnerRadius + 0.1f)
		return;

	if (a_nSubdivisionsA < 3)
		a_nSubdivisionsA = 3;
	if (a_nSubdivisionsA > 25)
		a_nSubdivisionsA = 25;

	if (a_nSubdivisionsB < 3)
		a_nSubdivisionsB = 3;
	if (a_nSubdivisionsB > 25)
		a_nSubdivisionsB = 25;

	Release();
	Init();

	//Your code starts here
	// F10 brings up torus
	float fValue = 0.5f;
	//3--2
	//|  |
	//0--1
	float stepsT = 2 * PI / static_cast<float>(a_nSubdivisionsB);
	float stepsP = 2 * PI / static_cast<float>(a_nSubdivisionsA);
	float r = a_fOuterRadius - a_fInnerRadius;
	float R = r + a_fInnerRadius;

	vector3 points1;
	vector3 points2;
	vector3 points3;
	vector3 points4;

	for (int i = 0; i < a_nSubdivisionsA; i++) {
		float phiL = stepsP * i;
		float phiR = stepsP * (i + 1);
		for (int j = 0; j < a_nSubdivisionsB; j++) {
			float thetaL = stepsT * j;
			float thetaR = stepsT * (j + 1);
			points1 = vector3((R + r * cos(thetaL)) * cos(phiL), (R + r * cos(thetaL)) * sin(phiL), r * sin(thetaL));
			points2 = vector3((R + r * cos(thetaL)) * cos(phiR), (R + r * cos(thetaL)) * sin(phiR), r * sin(thetaL));
			points3 = vector3((R + r * cos(thetaR)) * cos(phiL), (R + r * cos(thetaR)) * sin(phiL), r * sin(thetaR));
			points4 = vector3((R + r * cos(thetaR)) * cos(phiR), (R + r * cos(thetaR)) * sin(phiR), r * sin(thetaR));
			AddQuad(points1, points2, points3, points4);
		}
	}

	//Your code ends here
	CompileObject(a_v3Color);
}
void MyPrimitive::GenerateSphere(float a_fRadius, int a_nSubdivisions, vector3 a_v3Color)
{
	//Sets minimum and maximum of subdivisions
	if (a_nSubdivisions < 1)
	{
		GenerateCube(a_fRadius * 2, a_v3Color);
		return;
	}
	if (a_nSubdivisions > 6)
		a_nSubdivisions = 6;

	Release();
	Init();

	//Your code starts here
	float fValue = 0.5f;
	//3--2
	//|  |
	//0--1
	// T = Theta, P = Phi
	float stepsT = 2 * PI / static_cast<float>(a_nSubdivisions);
	float stepsP = PI / static_cast<float>(a_nSubdivisions);

	// points for sphere
	vector3 points1;
	vector3 points2;
	vector3 points3;
	vector3 points4;

	for (int i = 0; i < a_nSubdivisions; i++) {
		// L = Left, R = Right
		float phiL = stepsP * i;
		float phiR = stepsP * (i + 1);
		for (int j = 0; j < a_nSubdivisions; j++) {
			float thetaL = stepsT * j;
			float thetaR = stepsT * (j + 1);
			points1 = vector3(a_fRadius * cos(thetaL) * sin(phiL), a_fRadius * sin(thetaL) * sin(phiL), a_fRadius * cos(phiL));
			points2 = vector3(a_fRadius * cos(thetaL) * sin(phiR), a_fRadius * sin(thetaL) * sin(phiR), a_fRadius * cos(phiR));
			points3 = vector3(a_fRadius * cos(thetaR) * sin(phiL), a_fRadius * sin(thetaR) * sin(phiL), a_fRadius * cos(phiL));
			points4 = vector3(a_fRadius * cos(thetaR) * sin(phiR), a_fRadius * sin(thetaR) * sin(phiR), a_fRadius * cos(phiR));
			AddQuad(points1, points2, points3, points4);
		}
	}
	
	//Your code ends here
	CompileObject(a_v3Color);
}

void MyPrimitive::AddTri(vector3 a_vBottomLeft, vector3 a_vBottomRight, vector3 a_vTopLeft)
{
	AddVertexPosition(a_vBottomLeft);
	AddVertexPosition(a_vBottomRight);
	AddVertexPosition(a_vTopLeft);
}