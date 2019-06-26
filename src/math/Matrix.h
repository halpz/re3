#pragma once

class CMatrix
{
public:
	RwMatrix m_matrix;
	RwMatrix *m_attachment;
	bool m_hasRwMatrix;	// are we the owner?

	CMatrix(void){
		m_attachment = nil;
		m_hasRwMatrix = false;
	}
	CMatrix(CMatrix const &m){
		m_attachment = nil;
		m_hasRwMatrix = false;
		*this = m;
	}
	CMatrix(RwMatrix *matrix, bool owner = false){
		m_attachment = nil;
		Attach(matrix, owner);
	}
	~CMatrix(void){
		if(m_hasRwMatrix && m_attachment)
			RwMatrixDestroy(m_attachment);
	}
	void Attach(RwMatrix *matrix, bool owner = false){
		if(m_hasRwMatrix && m_attachment)
			RwMatrixDestroy(m_attachment);
		m_attachment = matrix;
		m_hasRwMatrix = owner;
		Update();
	}
	void AttachRW(RwMatrix *matrix, bool owner = false){
		if(m_hasRwMatrix && m_attachment)
			RwMatrixDestroy(m_attachment);
		m_attachment = matrix;
		m_hasRwMatrix = owner;
		UpdateRW();
	}
	void Detach(void){
		if(m_hasRwMatrix && m_attachment)
			RwMatrixDestroy(m_attachment);
		m_attachment = nil;
	}
	void Update(void){
		m_matrix = *m_attachment;
	}
	void UpdateRW(void){
		if(m_attachment){
			*m_attachment = m_matrix;
			RwMatrixUpdate(m_attachment);
		}
	}
	void operator=(CMatrix const &rhs){
		m_matrix = rhs.m_matrix;
		if(m_attachment)
			UpdateRW();
	}

	CVector *GetPosition(void){ return (CVector*)&m_matrix.pos; }
	CVector *GetRight(void) { return (CVector*)&m_matrix.right; }
	CVector *GetForward(void) { return (CVector*)&m_matrix.up; }
	CVector *GetUp(void) { return (CVector*)&m_matrix.at; }
	void SetScale(float s){
		m_matrix.right.x = s;
		m_matrix.right.y = 0.0f;
		m_matrix.right.z = 0.0f;

		m_matrix.up.x = 0.0f;
		m_matrix.up.y = s;
		m_matrix.up.z = 0.0f;

		m_matrix.at.x = 0.0f;
		m_matrix.at.y = 0.0f;
		m_matrix.at.z = s;

		m_matrix.pos.x = 0.0f;
		m_matrix.pos.y = 0.0f;
		m_matrix.pos.z = 0.0f;
	}
	void SetRotateXOnly(float angle){
		float c = cos(angle);
		float s = sin(angle);

		m_matrix.right.x = 1.0f;
		m_matrix.right.y = 0.0f;
		m_matrix.right.z = 0.0f;

		m_matrix.up.x = 0.0f;
		m_matrix.up.y = c;
		m_matrix.up.z = s;

		m_matrix.at.x = 0.0f;
		m_matrix.at.y = -s;
		m_matrix.at.z = c;
	}
	void SetRotateX(float angle){
		SetRotateXOnly(angle);
		m_matrix.pos.x = 0.0f;
		m_matrix.pos.y = 0.0f;
		m_matrix.pos.z = 0.0f;
	}
	void SetRotateYOnly(float angle){
		float c = cos(angle);
		float s = sin(angle);

		m_matrix.right.x = c;
		m_matrix.right.y = 0.0f;
		m_matrix.right.z = -s;

		m_matrix.up.x = 0.0f;
		m_matrix.up.y = 1.0f;
		m_matrix.up.z = 0.0f;

		m_matrix.at.x = s;
		m_matrix.at.y = 0.0f;
		m_matrix.at.z = c;
	}
	void SetRotateY(float angle){
		SetRotateYOnly(angle);
		m_matrix.pos.x = 0.0f;
		m_matrix.pos.y = 0.0f;
		m_matrix.pos.z = 0.0f;
	}
	void SetRotateZOnly(float angle){
		float c = cos(angle);
		float s = sin(angle);

		m_matrix.right.x = c;
		m_matrix.right.y = s;
		m_matrix.right.z = 0.0f;

		m_matrix.up.x = -s;
		m_matrix.up.y = c;
		m_matrix.up.z = 0.0f;

		m_matrix.at.x = 0.0f;
		m_matrix.at.y = 0.0f;
		m_matrix.at.z = 1.0f;
	}
	void SetRotateZ(float angle){
		SetRotateZOnly(angle);
		m_matrix.pos.x = 0.0f;
		m_matrix.pos.y = 0.0f;
		m_matrix.pos.z = 0.0f;
	}
	void SetRotate(float xAngle, float yAngle, float zAngle) {
		float cX = cos(xAngle);
		float sX = sin(xAngle);
		float cY = cos(yAngle);
		float sY = sin(yAngle);
		float cZ = cos(zAngle);
		float sZ = sin(zAngle);

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
	void Reorthogonalise(void){
		CVector &r = *GetRight();
		CVector &f = *GetForward();
		CVector &u = *GetUp();
		u = CrossProduct(r, f);
		u.Normalise();
		r = CrossProduct(f, u);
		r.Normalise();
		f = CrossProduct(u, r);
	}
	void CopyOnlyMatrix(CMatrix *other){
		m_matrix = other->m_matrix;
	}
};

inline CMatrix&
Invert(const CMatrix &src, CMatrix &dst)
{
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

inline CMatrix
Invert(const CMatrix &matrix)
{
	CMatrix inv;
	return Invert(matrix, inv);
}

inline CVector
operator*(const CMatrix &mat, const CVector &vec)
{
	return CVector(
		mat.m_matrix.right.x * vec.x + mat.m_matrix.up.x * vec.y + mat.m_matrix.at.x * vec.z + mat.m_matrix.pos.x,
		mat.m_matrix.right.y * vec.x + mat.m_matrix.up.y * vec.y + mat.m_matrix.at.y * vec.z + mat.m_matrix.pos.y,
		mat.m_matrix.right.z * vec.x + mat.m_matrix.up.z * vec.y + mat.m_matrix.at.z * vec.z + mat.m_matrix.pos.z);
}

inline CMatrix
operator*(const CMatrix &m1, const CMatrix &m2)
{
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

inline CVector
MultiplyInverse(const CMatrix &mat, const CVector &vec)
{
	CVector v(vec.x - mat.m_matrix.pos.x, vec.y - mat.m_matrix.pos.y, vec.z - mat.m_matrix.pos.z);
	return CVector(
		mat.m_matrix.right.x * v.x + mat.m_matrix.right.y * v.y + mat.m_matrix.right.z * v.z,
		mat.m_matrix.up.x * v.x + mat.m_matrix.up.y * v.y + mat.m_matrix.up.z * v.z,
		mat.m_matrix.at.x * v.x + mat.m_matrix.at.y * v.y + mat.m_matrix.at.z * v.z);
}

inline CVector
Multiply3x3(const CMatrix &mat, const CVector &vec)
{
	return CVector(
		mat.m_matrix.right.x * vec.x + mat.m_matrix.up.x * vec.y + mat.m_matrix.at.x * vec.z,
		mat.m_matrix.right.y * vec.x + mat.m_matrix.up.y * vec.y + mat.m_matrix.at.y * vec.z,
		mat.m_matrix.right.z * vec.x + mat.m_matrix.up.z * vec.y + mat.m_matrix.at.z * vec.z);
}

class CCompressedMatrixNotAligned
{
	CVector m_vecPos;
	int8 m_rightX;
	int8 m_rightY;
	int8 m_rightZ;
	int8 m_upX;
	int8 m_upY;
	int8 m_upZ;
public:
	void CompressFromFullMatrix(CMatrix &other)
	{
		m_rightX = 127.0f * other.GetRight()->x;
		m_rightY = 127.0f * other.GetRight()->y;
		m_rightZ = 127.0f * other.GetRight()->z;
		m_upX = 127.0f * other.GetForward()->x;
		m_upY = 127.0f * other.GetForward()->y;
		m_upZ = 127.0f * other.GetForward()->z;
		m_vecPos = *other.GetPosition();
	}
	void DecompressIntoFullMatrix(CMatrix &other)
	{
		other.GetRight()->x = m_rightX / 127.0f;
		other.GetRight()->y = m_rightY / 127.0f;
		other.GetRight()->z = m_rightZ / 127.0f;
		other.GetForward()->x = m_upX / 127.0f;
		other.GetForward()->y = m_upY / 127.0f;
		other.GetForward()->z = m_upZ / 127.0f;
		*other.GetUp() = CrossProduct(*other.GetRight(), *other.GetForward());
		*other.GetPosition() = m_vecPos;
		other.Reorthogonalise();
	}
};