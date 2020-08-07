#include "common.h"

#include "Quaternion.h"
#include "VuVector.h"

// TODO: move more stuff into here


void TransformPoint(CVuVector &out, const CMatrix &mat, const CVuVector &in)
{
#ifdef GTA_PS2
	__asm__ __volatile__("\n\
		lqc2    vf01,0x0(%2)\n\
		lqc2    vf02,0x0(%1)\n\
		lqc2    vf03,0x10(%1)\n\
		lqc2    vf04,0x20(%1)\n\
		lqc2    vf05,0x30(%1)\n\
		vmulax.xyz	ACC,   vf02,vf01\n\
		vmadday.xyz	ACC,   vf03,vf01\n\
		vmaddaz.xyz	ACC,   vf04,vf01\n\
		vmaddw.xyz	vf06,vf05,vf00\n\
		sqc2    vf06,0x0(%0)\n\
		": : "r" (&out) , "r" (&mat) ,"r" (&in): "memory");
#else
	out = mat * in;
#endif
}

void TransformPoint(CVuVector &out, const CMatrix &mat, const RwV3d &in)
{
#ifdef GTA_PS2
	__asm__ __volatile__("\n\
		ldr	$8,0x0(%2)\n\
		ldl	$8,0x7(%2)\n\
		lw	$9,0x8(%2)\n\
		pcpyld	$10,$9,$8\n\
		qmtc2	$10,vf01\n\
		lqc2    vf02,0x0(%1)\n\
		lqc2    vf03,0x10(%1)\n\
		lqc2    vf04,0x20(%1)\n\
		lqc2    vf05,0x30(%1)\n\
		vmulax.xyz	ACC,   vf02,vf01\n\
		vmadday.xyz	ACC,   vf03,vf01\n\
		vmaddaz.xyz	ACC,   vf04,vf01\n\
		vmaddw.xyz	vf06,vf05,vf00\n\
		sqc2    vf06,0x0(%0)\n\
		": : "r" (&out) , "r" (&mat) ,"r" (&in): "memory");
#else
	out = mat * in;
#endif
}

void TransformPoints(CVuVector *out, int n, const CMatrix &mat, const RwV3d *in, int stride)
{
#ifdef GTA_PS3
	__asm__ __volatile__("\n\
		paddub	$3,%4,$0\n\
		lqc2    vf02,0x0(%2)\n\
		lqc2    vf03,0x10(%2)\n\
		lqc2    vf04,0x20(%2)\n\
		lqc2    vf05,0x30(%2)\n\
		ldr	$8,0x0(%3)\n\
		ldl	$8,0x7(%3)\n\
		lw	$9,0x8(%3)\n\
		pcpyld	$10,$9,$8\n\
		qmtc2	$10,vf01\n\
	1:	vmulax.xyz	ACC,   vf02,vf01\n\
		vmadday.xyz	ACC,   vf03,vf01\n\
		vmaddaz.xyz	ACC,   vf04,vf01\n\
		vmaddw.xyz	vf06,vf05,vf00\n\
		add	%3,%3,$3\n\
		ldr	$8,0x0(%3)\n\
		ldl	$8,0x7(%3)\n\
		lw	$9,0x8(%3)\n\
		pcpyld	$10,$9,$8\n\
		qmtc2	$10,vf01\n\
		addi	%1,%1,-1\n\
		addiu	%0,%0,0x10\n\
		sqc2    vf06,-0x10(%0)\n\
		bnez	%1,1b\n\
		": : "r" (out) , "r" (n), "r" (&mat), "r" (in), "r" (stride): "memory");
#else
	while(n--){
		*out = mat * *in;
		in = (RwV3d*)((uint8*)in + stride);
		out++;
	}
#endif
}

void TransformPoints(CVuVector *out, int n, const CMatrix &mat, const CVuVector *in)
{
#ifdef GTA_PS2
	__asm__ __volatile__("\n\
		lqc2    vf02,0x0(%2)\n\
		lqc2    vf03,0x10(%2)\n\
		lqc2    vf04,0x20(%2)\n\
		lqc2    vf05,0x30(%2)\n\
		lqc2    vf01,0x0(%3)\n\
		nop\n\
	1:	vmulax.xyz	ACC,   vf02,vf01\n\
		vmadday.xyz	ACC,   vf03,vf01\n\
		vmaddaz.xyz	ACC,   vf04,vf01\n\
		vmaddw.xyz	vf06,vf05,vf00\n\
		lqc2	vf01,0x10(%3)\n\
		addiu	%3,%3,0x10\n\
		addi	%1,%1,-1\n\
		addiu	%0,%0,0x10\n\
		sqc2    vf06,-0x10(%0)\n\
		bnez	%1,1b\n\
		": : "r" (out) , "r" (n), "r" (&mat) ,"r" (in): "memory");
#else
	while(n--){
		*out = mat * *in;
		in++;
		out++;
	}
#endif
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

	m_matrix.right.x = cZ * cY - (sZ * sX) * sY;
	m_matrix.right.y = (cZ * sX) * sY + sZ * cY;
	m_matrix.right.z = -cX * sY;

	m_matrix.up.x = -sZ * cX;
	m_matrix.up.y = cZ * cX;
	m_matrix.up.z = sX;

	m_matrix.at.x = (sZ * sX) * cY + cZ * sY;
	m_matrix.at.y = sZ * sY - (cZ * sX) * cY;
	m_matrix.at.z = cX * cY;

	m_matrix.pos.x = 0.0f;
	m_matrix.pos.y = 0.0f;
	m_matrix.pos.z = 0.0f;
}

void
CMatrix::Rotate(float x, float y, float z)
{
	// TODO? do this directly without creating another matrix
	CMatrix rot;
	rot.SetRotate(x, y, z);
	*this = rot * *this;
}

void
CMatrix::RotateX(float x)
{
	Rotate(x, 0.0f, 0.0f);
}

void
CMatrix::RotateY(float y)
{
	Rotate(0.0f, y, 0.0f);
}

void
CMatrix::RotateZ(float z)
{
	Rotate(0.0f, 0.0f, z);
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

CMatrix&
Invert(const CMatrix &src, CMatrix &dst)
{
	// TODO: VU0 code
	// GTA handles this as a raw 4x4 orthonormal matrix
	// and trashes the RW flags, let's not do that
	// actual copy of librw code:
	RwMatrix *d = &dst.m_matrix;
	const RwMatrix *s = &src.m_matrix;
	d->right.x = s->right.x;
	d->right.y = s->up.x;
	d->right.z = s->at.x;
	d->up.x = s->right.y;
	d->up.y = s->up.y;
	d->up.z = s->at.y;
	d->at.x = s->right.z;
	d->at.y = s->up.z;
	d->at.z = s->at.z;
	d->pos.x = -(s->pos.x*s->right.x +
	               s->pos.y*s->right.y +
	               s->pos.z*s->right.z);
	d->pos.y = -(s->pos.x*s->up.x +
	               s->pos.y*s->up.y +
	               s->pos.z*s->up.z);
	d->pos.z = -(s->pos.x*s->at.x +
	               s->pos.y*s->at.y +
	               s->pos.z*s->at.z);
	d->flags = rwMATRIXTYPEORTHONORMAL;
	return dst;
}

CVector
operator*(const CMatrix &mat, const CVector &vec)
{
	// TODO: VU0 code
	return CVector(
		mat.m_matrix.right.x * vec.x + mat.m_matrix.up.x * vec.y + mat.m_matrix.at.x * vec.z + mat.m_matrix.pos.x,
		mat.m_matrix.right.y * vec.x + mat.m_matrix.up.y * vec.y + mat.m_matrix.at.y * vec.z + mat.m_matrix.pos.y,
		mat.m_matrix.right.z * vec.x + mat.m_matrix.up.z * vec.y + mat.m_matrix.at.z * vec.z + mat.m_matrix.pos.z);
}

CMatrix
operator*(const CMatrix &m1, const CMatrix &m2)
{
	// TODO: VU0 code
	CMatrix out;
	RwMatrix *dst = &out.m_matrix;
	const RwMatrix *src1 = &m1.m_matrix;
	const RwMatrix *src2 = &m2.m_matrix;
	dst->right.x = src1->right.x*src2->right.x + src1->up.x*src2->right.y + src1->at.x*src2->right.z;
	dst->right.y = src1->right.y*src2->right.x + src1->up.y*src2->right.y + src1->at.y*src2->right.z;
	dst->right.z = src1->right.z*src2->right.x + src1->up.z*src2->right.y + src1->at.z*src2->right.z;
	dst->up.x    = src1->right.x*src2->up.x    + src1->up.x*src2->up.y    + src1->at.x*src2->up.z;
	dst->up.y    = src1->right.y*src2->up.x    + src1->up.y*src2->up.y    + src1->at.y*src2->up.z;
	dst->up.z    = src1->right.z*src2->up.x    + src1->up.z*src2->up.y    + src1->at.z*src2->up.z;
	dst->at.x    = src1->right.x*src2->at.x    + src1->up.x*src2->at.y    + src1->at.x*src2->at.z;
	dst->at.y    = src1->right.y*src2->at.x    + src1->up.y*src2->at.y    + src1->at.y*src2->at.z;
	dst->at.z    = src1->right.z*src2->at.x    + src1->up.z*src2->at.y    + src1->at.z*src2->at.z;
	dst->pos.x   = src1->right.x*src2->pos.x   + src1->up.x*src2->pos.y   + src1->at.x*src2->pos.z + src1->pos.x;
	dst->pos.y   = src1->right.y*src2->pos.x   + src1->up.y*src2->pos.y   + src1->at.y*src2->pos.z + src1->pos.y;
	dst->pos.z   = src1->right.z*src2->pos.x   + src1->up.z*src2->pos.y   + src1->at.z*src2->pos.z + src1->pos.z;
	return out;
}

CMatrix&
CMatrix::operator*=(CMatrix const &rhs)
{
	// TODO: VU0 code
	*this = *this * rhs;
	return *this;
}

const CVector
Multiply3x3(const CMatrix &mat, const CVector &vec)
{
	// TODO: VU0 code
	return CVector(
		mat.m_matrix.right.x * vec.x + mat.m_matrix.up.x * vec.y + mat.m_matrix.at.x * vec.z,
		mat.m_matrix.right.y * vec.x + mat.m_matrix.up.y * vec.y + mat.m_matrix.at.y * vec.z,
		mat.m_matrix.right.z * vec.x + mat.m_matrix.up.z * vec.y + mat.m_matrix.at.z * vec.z);
}

const CVector
Multiply3x3(const CVector &vec, const CMatrix &mat)
{
	return CVector(
		mat.m_matrix.right.x * vec.x + mat.m_matrix.right.y * vec.y + mat.m_matrix.right.z * vec.z,
		mat.m_matrix.up.x * vec.x + mat.m_matrix.up.y * vec.y + mat.m_matrix.up.z * vec.z,
		mat.m_matrix.at.x * vec.x + mat.m_matrix.at.y * vec.y + mat.m_matrix.at.z * vec.z);
}


void
CQuaternion::Slerp(const CQuaternion &q1, const CQuaternion &q2, float theta, float invSin, float t)
{
	if(theta == 0.0f)
		*this = q2;
	else{
		float w1, w2;
		if(theta > PI/2){
			theta = PI - theta;
			w1 = Sin((1.0f - t) * theta) * invSin;
			w2 = -Sin(t * theta) * invSin;
		}else{
			w1 = Sin((1.0f - t) * theta) * invSin;
			w2 = Sin(t * theta) * invSin;
		}
		// TODO: VU0 code
		*this = w1*q1 + w2*q2;
	}
}

void
CQuaternion::Set(RwV3d *axis, float angle)
{
	float halfCos = Cos(angle*0.5f);
	float halfSin = Sin(angle*0.5f);
	x = axis->x*halfSin;
	y = axis->y*halfSin;
	z = axis->z*halfSin;
	w = halfCos;
}

void
CQuaternion::Get(RwMatrix *matrix)
{
	float x2 = x+x;
	float y2 = y+y;
	float z2 = z+z;

	float x_2x = x * x2;
	float x_2y = x * y2;
	float x_2z = x * z2;
	float y_2y = y * y2;
	float y_2z = y * z2;
	float z_2z = z * z2;
	float w_2x = w * x2;
	float w_2y = w * y2;
	float w_2z = w * z2;

	matrix->right.x = 1.0f - (y_2y + z_2z);
	matrix->up.x = x_2y - w_2z;
	matrix->at.x = x_2z + w_2y;
	matrix->right.y = x_2y + w_2z;
	matrix->up.y = 1.0f - (x_2x + z_2z);
	matrix->at.y = y_2z - w_2x;
	matrix->right.z = x_2z - w_2y;
	matrix->up.z = y_2z + w_2x;
	matrix->at.z = 1.0f - (x_2x + y_2y);
}
