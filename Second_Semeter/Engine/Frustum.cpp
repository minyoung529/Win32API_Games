#include "pch.h"
#include "Frustum.h"
#include "Camera.h"

void Frustum::FinalUpdate()
{
	Matrix matViewInv = Camera::s_MatView.Invert();	// view 역행렬
	Matrix matProjInv = Camera::s_MatProjection.Invert();	// 프로젝션 역행렬
	Matrix matInv =  matProjInv * matViewInv;	// world

	vector<Vec3> worldPos =
	{
		::XMVector3TransformCoord(Vec3(-1.f, 1.f, 0.f), matInv),
		::XMVector3TransformCoord(Vec3(1.f, 1.f, 0.f), matInv),
		::XMVector3TransformCoord(Vec3(1.f, -1.f, 0.f), matInv),
		::XMVector3TransformCoord(Vec3(-1.f, -1.f, 0.f), matInv),

		::XMVector3TransformCoord(Vec3(-1.f, 1.f, 1.f), matInv),
		::XMVector3TransformCoord(Vec3(1.f, 1.f, 1.f), matInv),
		::XMVector3TransformCoord(Vec3(1.f, -1.f, 1.f), matInv),
		::XMVector3TransformCoord(Vec3(-1.f, -1.f, 1.f), matInv),
	};

	m_planes[PLANE_FRONT] = ::XMPlaneFromPoints(worldPos[0], worldPos[1], worldPos[2]);
	m_planes[PLANE_BACK] =	::XMPlaneFromPoints(worldPos[4], worldPos[7], worldPos[5]);
	m_planes[PLANE_UP] =	::XMPlaneFromPoints(worldPos[4], worldPos[5], worldPos[1]);
	m_planes[PLANE_DOWN] =	::XMPlaneFromPoints(worldPos[7], worldPos[3], worldPos[6]);
	m_planes[PLANE_LEFT] =	::XMPlaneFromPoints(worldPos[4], worldPos[0], worldPos[7]);
	m_planes[PLANE_RIGHT] = ::XMPlaneFromPoints(worldPos[5], worldPos[6], worldPos[1]);
}

bool Frustum::ContainsSphere(const Vec3& pos, float radius)
{
	for (const Vec4& plane : m_planes)
	{
		Vec3 normal = Vec3(plane.x, plane.y, plane.z);

		// d = plane.w (ax + by + cz + d)
		if (normal.Dot(pos) + plane.w > radius)	// 밖에 있는 것
		{
			return false;
		}
	}

	return true;
}
