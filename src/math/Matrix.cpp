#include "common.h"

CMatrix::CMatrix(void)
{
	m_attachment = nil;
	m_hasRwMatrix = false;
}

CMatrix::CMatrix(CMatrix const &m)
{
	m_attachment = nil;
	m_hasRwMatrix = false;
	*this = m;
}

CMatrix::CMatrix(RwMatrix *matrix, bool owner)
{
	m_attachment = nil;
	Attach(matrix, owner);
}

CMatrix::~CMatrix(void)
{
	if (m_hasRwMatrix && m_attachment)
		RwMatrixDestroy(m_attachment);
}

void
CMatrix::Attach(RwMatrix *matrix, bool owner)
{
#ifdef FIX_BUGS
	if (m_attachment && m_hasRwMatrix)
#else
	if (m_hasRwMatrix && m_attachment)
#endif
		RwMatrixDestroy(m_attachment);
	m_attachment = matrix;
	m_hasRwMatrix = owner;
	Update();
}

void
CMatrix::AttachRW(RwMatrix *matrix, bool owner)
{
	if (m_hasRwMatrix && m_attachment)
		RwMatrixDestroy(m_attachment);
	m_attachment = matrix;
	m_hasRwMatrix = owner;
	UpdateRW();
}

void
CMatrix::Detach(void)
{
	if (m_hasRwMatrix && m_attachment)
		RwMatrixDestroy(m_attachment);
	m_attachment = nil;
}

void
CMatrix::Update(void)
{
	right = m_attachment->right;
	forward = m_attachment->up;
	up = m_attachment->at;
	pos = m_attachment->pos;
}

void
CMatrix::UpdateRW(void)
{
	if (m_attachment) {
		m_attachment->right = right;
		m_attachment->up = forward;
		m_attachment->at = up;
		m_attachment->pos = pos;
		RwMatrixUpdate(m_attachment);
	}
}

void
CMatrix::operator=(CMatrix const &rhs)
{
	memcpy(this, &rhs, sizeof(f));
	if (m_attachment)
		UpdateRW();
}

void
CMatrix::CopyOnlyMatrix(const CMatrix &other)
{
	memcpy(this, &other, sizeof(f));
}

CMatrix &
CMatrix::operator+=(CMatrix const &rhs)
{
	right += rhs.right;
	forward += rhs.forward;
	up += rhs.up;
	pos += rhs.pos;
	return *this;
}

void
CMatrix::SetUnity(void)
{
	right.x = 1.0f;
	right.y = 0.0f;
	right.z = 0.0f;
	forward.x = 0.0f;
	forward.y = 1.0f;
	forward.z = 0.0f;
	up.x = 0.0f;
	up.y = 0.0f;
	up.z = 1.0f;
	pos.x = 0.0f;
	pos.y = 0.0f;
	pos.z = 0.0f;
}

void
CMatrix::ResetOrientation(void)
{
	right.x = 1.0f;
	right.y = 0.0f;
	right.z = 0.0f;
	forward.x = 0.0f;
	forward.y = 1.0f;
	forward.z = 0.0f;
	up.x = 0.0f;
	up.y = 0.0f;
	up.z = 1.0f;
}

void
CMatrix::SetScale(float s)
{
	right.x = s;
	right.y = 0.0f;
	right.z = 0.0f;

	forward.x = 0.0f;
	forward.y = s;
	forward.z = 0.0f;

	up.x = 0.0f;
	up.y = 0.0f;
	up.z = s;

	pos.x = 0.0f;
	pos.y = 0.0f;
	pos.z = 0.0f;
}

void
CMatrix::SetTranslate(float x, float y, float z)
{
	right.x = 1.0f;
	right.y = 0.0f;
	right.z = 0.0f;

	forward.x = 0.0f;
	forward.y = 1.0f;
	forward.z = 0.0f;

	up.x = 0.0f;
	up.y = 0.0f;
	up.z = 1.0f;

	pos.x = x;
	pos.y = y;
	pos.z = z;
}

void
CMatrix::SetRotateXOnly(float angle)
{
	float c = Cos(angle);
	float s = Sin(angle);

	right.x = 1.0f;
	right.y = 0.0f;
	right.z = 0.0f;

	forward.x = 0.0f;
	forward.y = c;
	forward.z = s;

	up.x = 0.0f;
	up.y = -s;
	up.z = c;
}

void
CMatrix::SetRotateYOnly(float angle)
{
	float c = Cos(angle);
	float s = Sin(angle);

	right.x = c;
	right.y = 0.0f;
	right.z = -s;

	forward.x = 0.0f;
	forward.y = 1.0f;
	forward.z = 0.0f;

	up.x = s;
	up.y = 0.0f;
	up.z = c;
}

void
CMatrix::SetRotateZOnly(float angle)
{
	float c = Cos(angle);
	float s = Sin(angle);

	right.x = c;
	right.y = s;
	right.z = 0.0f;

	forward.x = -s;
	forward.y = c;
	forward.z = 0.0f;

	up.x = 0.0f;
	up.y = 0.0f;
	up.z = 1.0f;
}

void
CMatrix::SetRotateX(float angle)
{
	SetRotateXOnly(angle);
	pos.x = 0.0f;
	pos.y = 0.0f;
	pos.z = 0.0f;
}


void
CMatrix::SetRotateY(float angle)
{
	SetRotateYOnly(angle);
	pos.x = 0.0f;
	pos.y = 0.0f;
	pos.z = 0.0f;
}

void
CMatrix::SetRotateZ(float angle)
{
	SetRotateZOnly(angle);
	pos.x = 0.0f;
	pos.y = 0.0f;
	pos.z = 0.0f;
}

void
CMatrix::SetRotate(float xAngle, float yAngle, float zAngle)
{
	float cX = Cos(xAngle);
	float sX = Sin(xAngle);
	float cY = Cos(yAngle);
	float sY = Sin(yAngle);
	float cZ = Cos(zAngle);
	float sZ = Sin(zAngle);

	right.x = cZ * cY - (sZ * sX) * sY;
	right.y = (cZ * sX) * sY + sZ * cY;
	right.z = -cX * sY;

	forward.x = -sZ * cX;
	forward.y = cZ * cX;
	forward.z = sX;

	up.x = (sZ * sX) * cY + cZ * sY;
	up.y = sZ * sY - (cZ * sX) * cY;
	up.z = cX * cY;

	pos.x = 0.0f;
	pos.y = 0.0f;
	pos.z = 0.0f;
}

void
CMatrix::RotateX(float x)
{
	float c = Cos(x);
	float s = Sin(x);

	float ry = right.y;
	float rz = right.z;
	float uy = forward.y;
	float uz = forward.z;
	float ay = up.y;
	float az = up.z;
	float py = pos.y;
	float pz = pos.z;

	right.y = c * ry - s * rz;
	right.z = c * rz + s * ry;
	forward.y = c * uy - s * uz;
	forward.z = c * uz + s * uy;
	up.y = c * ay - s * az;
	up.z = c * az + s * ay;
	pos.y = c * py - s * pz;
	pos.z = c * pz + s * py;
}

void
CMatrix::RotateY(float y)
{
	float c = Cos(y);
	float s = Sin(y);

	float rx = right.x;
	float rz = right.z;
	float ux = forward.x;
	float uz = forward.z;
	float ax = up.x;
	float az = up.z;
	float px = pos.x;
	float pz = pos.z;

	right.x = c * rx + s * rz;
	right.z = c * rz - s * rx;
	forward.x = c * ux + s * uz;
	forward.z = c * uz - s * ux;
	up.x = c * ax + s * az;
	up.z = c * az - s * ax;
	pos.x = c * px + s * pz;
	pos.z = c * pz - s * px;
}

void
CMatrix::RotateZ(float z)
{
	float c = Cos(z);
	float s = Sin(z);

	float ry = right.y;
	float rx = right.x;
	float uy = forward.y;
	float ux = forward.x;
	float ay = up.y;
	float ax = up.x;
	float py = pos.y;
	float px = pos.x;

	right.x = c * rx - s * ry;
	right.y = c * ry + s * rx;
	forward.x = c * ux - s * uy;
	forward.y = c * uy + s * ux;
	up.x = c * ax - s * ay;
	up.y = c * ay + s * ax;
	pos.x = c * px - s * py;
	pos.y = c * py + s * px;

}

void
CMatrix::Rotate(float x, float y, float z)
{
	float cX = Cos(x);
	float sX = Sin(x);
	float cY = Cos(y);
	float sY = Sin(y);
	float cZ = Cos(z);
	float sZ = Sin(z);
	
	float rx = right.x;
	float ry = right.y;
	float rz = right.z;
	float ux = forward.x;
	float uy = forward.y;
	float uz = forward.z;
	float ax = up.x;
	float ay = up.y;
	float az = up.z;
	float px = pos.x;
	float py = pos.y;
	float pz = pos.z;

	float x1 = cZ * cY - (sZ * sX) * sY;
	float x2 = (cZ * sX) * sY + sZ * cY;
	float x3 = -cX * sY;
	float y1 = -sZ * cX;
	float y2 = cZ * cX;
	float y3 = sX;
	float z1 = (sZ * sX) * cY + cZ * sY;
	float z2 = sZ * sY - (cZ * sX) * cY;
	float z3 = cX * cY;

	right.x = x1 * rx + y1 * ry + z1 * rz;
	right.y = x2 * rx + y2 * ry + z2 * rz;
	right.z = x3 * rx + y3 * ry + z3 * rz;
	forward.x = x1 * ux + y1 * uy + z1 * uz;
	forward.y = x2 * ux + y2 * uy + z2 * uz;
	forward.z = x3 * ux + y3 * uy + z3 * uz;
	up.x = x1 * ax + y1 * ay + z1 * az;
	up.y = x2 * ax + y2 * ay + z2 * az;
	up.z = x3 * ax + y3 * ay + z3 * az;
	pos.x = x1 * px + y1 * py + z1 * pz;
	pos.y = x2 * px + y2 * py + z2 * pz;
	pos.z = x3 * px + y3 * py + z3 * pz;
}

CMatrix &
CMatrix::operator*=(CMatrix const &rhs)
{
	// TODO: VU0 code
	*this = *this * rhs;
	return *this;
}

void
CMatrix::Reorthogonalise(void)
{
	CVector &r = GetRight();
	CVector &f = GetForward();
	CVector &u = GetUp();
	u = CrossProduct(r, f);
	u.Normalise();
	r = CrossProduct(f, u);
	r.Normalise();
	f = CrossProduct(u, r);
}

CMatrix
operator*(const CMatrix &m1, const CMatrix &m2)
{
	// TODO: VU0 code
	CMatrix out;
	out.right.x = m1.right.x * m2.right.x + m1.forward.x * m2.right.y + m1.up.x * m2.right.z;
	out.right.y = m1.right.y * m2.right.x + m1.forward.y * m2.right.y + m1.up.y * m2.right.z;
	out.right.z = m1.right.z * m2.right.x + m1.forward.z * m2.right.y + m1.up.z * m2.right.z;
	out.forward.x = m1.right.x * m2.forward.x + m1.forward.x * m2.forward.y + m1.up.x * m2.forward.z;
	out.forward.y = m1.right.y * m2.forward.x + m1.forward.y * m2.forward.y + m1.up.y * m2.forward.z;
	out.forward.z = m1.right.z * m2.forward.x + m1.forward.z * m2.forward.y + m1.up.z * m2.forward.z;
	out.up.x = m1.right.x * m2.up.x + m1.forward.x * m2.up.y + m1.up.x * m2.up.z;
	out.up.y = m1.right.y * m2.up.x + m1.forward.y * m2.up.y + m1.up.y * m2.up.z;
	out.up.z = m1.right.z * m2.up.x + m1.forward.z * m2.up.y + m1.up.z * m2.up.z;
	out.pos.x = m1.right.x * m2.pos.x + m1.forward.x * m2.pos.y + m1.up.x * m2.pos.z + m1.pos.x;
	out.pos.y = m1.right.y * m2.pos.x + m1.forward.y * m2.pos.y + m1.up.y * m2.pos.z + m1.pos.y;
	out.pos.z = m1.right.z * m2.pos.x + m1.forward.z * m2.pos.y + m1.up.z * m2.pos.z + m1.pos.z;
	return out;
}

CMatrix &
Invert(const CMatrix &src, CMatrix &dst)
{
	// TODO: VU0 code
	// GTA handles this as a raw 4x4 orthonormal matrix
	// and trashes the RW flags, let's not do that
	dst.f[3][0] = dst.f[3][1] = dst.f[3][2] = 0.0f;
#ifndef FIX_BUGS
	dst.f[3][3] = src.f[3][3];
#endif

	dst.f[0][0] = src.f[0][0];
	dst.f[0][1] = src.f[1][0];
	dst.f[0][2] = src.f[2][0];
#ifndef FIX_BUGS
	dst.f[0][3] = src.f[3][0];
#endif
	dst.f[1][0] = src.f[0][1];
	dst.f[1][1] = src.f[1][1];
	dst.f[1][2] = src.f[2][1];
#ifndef FIX_BUGS
	dst.f[1][3] = src.f[3][1];
#endif
	dst.f[2][0] = src.f[0][2];
	dst.f[2][1] = src.f[1][2];
	dst.f[2][2] = src.f[2][2];
#ifndef FIX_BUGS
	dst.f[2][3] = src.f[3][2];
#endif

	dst.f[3][0] += dst.f[0][0] * src.f[3][0];
	dst.f[3][1] += dst.f[0][1] * src.f[3][0];
	dst.f[3][2] += dst.f[0][2] * src.f[3][0];
#ifndef FIX_BUGS
	dst.f[3][3] += dst.f[0][3] * src.f[3][0];
#endif

	dst.f[3][0] += dst.f[1][0] * src.f[3][1];
	dst.f[3][1] += dst.f[1][1] * src.f[3][1];
	dst.f[3][2] += dst.f[1][2] * src.f[3][1];
#ifndef FIX_BUGS
	dst.f[3][3] += dst.f[1][3] * src.f[3][1];
#endif

	dst.f[3][0] += dst.f[2][0] * src.f[3][2];
	dst.f[3][1] += dst.f[2][1] * src.f[3][2];
	dst.f[3][2] += dst.f[2][2] * src.f[3][2];
#ifndef FIX_BUGS
	dst.f[3][3] += dst.f[2][3] * src.f[3][2];
#endif

	dst.f[3][0] = -dst.f[3][0];
	dst.f[3][1] = -dst.f[3][1];
	dst.f[3][2] = -dst.f[3][2];
#ifndef FIX_BUGS
	dst.f[3][3] = src.f[3][3] - dst.f[3][3];
#endif

	return dst;
}

CMatrix
Invert(const CMatrix &matrix)
{
	CMatrix inv;
	return Invert(matrix, inv);
}

void
CCompressedMatrixNotAligned::CompressFromFullMatrix(CMatrix &other)
{
	m_rightX = 127.0f * other.GetRight().x;
	m_rightY = 127.0f * other.GetRight().y;
	m_rightZ = 127.0f * other.GetRight().z;
	m_upX = 127.0f * other.GetForward().x;
	m_upY = 127.0f * other.GetForward().y;
	m_upZ = 127.0f * other.GetForward().z;
	m_vecPos = other.GetPosition();
}

void
CCompressedMatrixNotAligned::DecompressIntoFullMatrix(CMatrix &other)
{
	other.GetRight().x = m_rightX / 127.0f;
	other.GetRight().y = m_rightY / 127.0f;
	other.GetRight().z = m_rightZ / 127.0f;
	other.GetForward().x = m_upX / 127.0f;
	other.GetForward().y = m_upY / 127.0f;
	other.GetForward().z = m_upZ / 127.0f;
	other.GetUp() = CrossProduct(other.GetRight(), other.GetForward());
	other.GetPosition() = m_vecPos;
	other.Reorthogonalise();
}