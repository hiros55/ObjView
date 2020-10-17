#pragma once
class Obj {
public:
	struct  Vector3f
	{
		float x, y, z;
	};
	struct ObjDate {

		Vector3f* vertices;
		int vertices_count;

		Vector3f* normals;
		int normal_count;

		Vector3f* texcoords;
		int texcoord_count;

		int* tri_v_no;
		int* tri_vn_no;
		int* tri_vt_no;
		int tri_count;
	};
	Obj() {};
	~Obj() {};
	ObjDate* Load(const char* FileName);
	void RenderObj(ObjDate* objectDate);
	void FreeDate(Obj::ObjDate* objectDate);
};