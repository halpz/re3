#pragma once

struct CColModel;

#define MAX_MODEL_NAME (21)

enum ModelInfoType
{
	MITYPE_NA,
	MITYPE_SIMPLE,
	MITYPE_MLO,	// unused but still in enum
	MITYPE_TIME,
	MITYPE_WEAPON,
	MITYPE_CLUMP,
	MITYPE_VEHICLE,
	MITYPE_PED,
	MITYPE_XTRACOMPS,	// unused but still in enum
	MITYPE_HAND	// xbox and mobile
};

class C2dEffect;

class CBaseModelInfo
{
protected:
	char         m_name[MAX_MODEL_NAME];
	uint8        m_type;
	uint8        m_num2dEffects;
	bool         m_bOwnsColModel;
	CColModel   *m_colModel;
	int16        m_2dEffectsID;
	int16        m_objectId;
	uint16       m_refCount;
	int16        m_txdSlot;

public:
	CBaseModelInfo(ModelInfoType type);
	virtual ~CBaseModelInfo() {}
	virtual void Shutdown(void);
	virtual void DeleteRwObject(void) = 0;
	virtual RwObject *CreateInstance(void) = 0;
	virtual RwObject *CreateInstance(RwMatrix *) = 0;
	virtual RwObject *GetRwObject(void) = 0;
	virtual void SetAnimFile(const char *file) {}
	virtual void ConvertAnimFileIndex(void) {}
	virtual int GetAnimFileIndex(void) { return -1; }

	// one day it becomes virtual
	uint8 GetModelType() const { return m_type; }
	bool IsBuilding(void) { return m_type == MITYPE_SIMPLE || m_type == MITYPE_TIME; }
	bool IsSimple(void) { return m_type == MITYPE_SIMPLE || m_type == MITYPE_TIME || m_type == MITYPE_WEAPON; }
	bool IsClump(void) { return m_type == MITYPE_CLUMP || m_type == MITYPE_PED || m_type == MITYPE_VEHICLE;	}
	char *GetModelName(void) { return m_name; }
	void SetModelName(const char *name) { strncpy(m_name, name, MAX_MODEL_NAME); }
	void SetColModel(CColModel *col, bool owns = false){
		m_colModel = col; m_bOwnsColModel = owns; }
	CColModel *GetColModel(void) { return m_colModel; }
	bool DoesOwnColModel(void) { return m_bOwnsColModel; }
	void DeleteCollisionModel(void);
	void ClearTexDictionary(void) { m_txdSlot = -1; }
	int16 GetObjectID(void) { return m_objectId; }
	void SetObjectID(int16 id) { m_objectId = id; }
	int16 GetTxdSlot(void) { return m_txdSlot; }
	void AddRef(void);
	void RemoveRef(void);
	void SetTexDictionary(const char *name);
	void AddTexDictionaryRef(void);
	void RemoveTexDictionaryRef(void);
	void Init2dEffects(void);
	void Add2dEffect(C2dEffect *fx);
	C2dEffect *Get2dEffect(int n);
	uint8 GetNum2dEffects() const { return m_num2dEffects; }
	uint16 GetNumRefs() const { return m_refCount; }
};
