#include <vector>
#include <GL/glut.h>
#include "ObjView.h"
#define MAX_VERTICES_SIZE 4096

Obj::ObjDate* Obj::Load(const char* FileName) {

	FILE* file;

	file = fopen(FileName, "r");
	if (file == NULL)
		return NULL;


	Obj::ObjDate* Obj = new Obj::ObjDate();
	Obj->vertices = new Obj::Vector3f[MAX_VERTICES_SIZE];
	Obj->vertices_count = 0;
	Obj->normals = new Obj::Vector3f[MAX_VERTICES_SIZE];
	Obj->normal_count = 0;
	Obj->texcoords = new Obj::Vector3f[MAX_VERTICES_SIZE];
	Obj->texcoord_count = 0;
	Obj->tri_v_no = new int[MAX_VERTICES_SIZE * 3];
	Obj->tri_vn_no = new int[MAX_VERTICES_SIZE * 3];
	Obj->tri_vt_no = new int[MAX_VERTICES_SIZE * 3];
	Obj->tri_count = 0;

	char  s[256];//fgetsで読み込んだ文字列

	//一時代入用変数
	Obj::Vector3f vec;//頂点・法線・テクスチャ
	int v_no[4], vt_no[4], vn_no[4];
	//カウント
	int f_count;
	int i, j;

	while (!feof(file))
	{
		fgets(s, 256, file);

		if (s[0] == 'v') {

			if (s[1] == 'n') {
				sscanf(s, "vn %f %f %f", &vec.x, &vec.y, &vec.z);

				if (Obj->normal_count < MAX_VERTICES_SIZE) {
					Obj->normals[Obj->normal_count] = vec;
					Obj->normal_count++;
				}

			}
			else if (s[1] == 't') {
				sscanf(s, "vt %f %f %f", &vec.x, &vec.y, &vec.z);

				if (Obj->texcoord_count < MAX_VERTICES_SIZE) {
					Obj->texcoords[Obj->texcoord_count] = vec;
					Obj->texcoord_count++;
				}
			}
			else {
				sscanf(s, "v %f %f %f", &vec.x, &vec.y, &vec.z);

				if (Obj->vertices_count < MAX_VERTICES_SIZE) {
					Obj->vertices[Obj->vertices_count] = vec;
					Obj->vertices_count++;
				}
			}

		}

		if (s[0] == 'f') {
			f_count = sscanf(s, "f %d//%d %d//%d %d//%d", &v_no[0], &vn_no[0], &v_no[1], &vn_no[1], &v_no[2], &vn_no[2]);

			if (f_count == 6) {
				i = Obj->tri_count * 3;
				for (j = 0; j < 3; j++) {
					Obj->tri_v_no[i + j] = v_no[j] - 1;
					Obj->tri_vn_no[i + j] = vn_no[j] - 1;
					Obj->tri_vt_no[i + j] = vt_no[j] - 1;
				}
				Obj->tri_count++;

			}

			if (Obj->tri_count >= MAX_VERTICES_SIZE)
				break;
		}
	};
	fclose(file);
	return Obj;
}


void Obj::RenderObj(Obj::ObjDate* objectDate) {
	int i = 0, j = 0, no;
	glColor3f(1, 0, 0);
	glBegin(GL_TRIANGLES);
	for (i = 0; i < objectDate->tri_count; i++) {

		for (j = 0; j < 3; j++) {
			no = objectDate->tri_vn_no[i * 3 + j];
			Vector3f& vn = objectDate->normals[no];

			glNormal3f(vn.x, vn.y, vn.z);

			no = objectDate->tri_v_no[i * 3 + j];
			Vector3f& v = objectDate->vertices[no];

			glVertex3f(v.x, v.y, v.z);
		}
	}
	glEnd();
}

void Obj::FreeDate(Obj::ObjDate* objectDate) {
	delete objectDate;
}

//未実装


/*void LoadMaterial(FILE * file) {

}*/

/*float Truncation(float x) {
	int num;
	float ans, ans_at;
	num = (int)x;

	if (x >= 0) {
		ans = x - num;
		for (int l = 0; l < 2; l++) {
			ans = ans * 10;
			num = (int)ans;
			ans = ans - num;
		}
		roundf(ans);
	}
	else {
		ans = x + num;//-0.145
		ans = 1 + ans;
	}

	return roundf(ans);
}*/