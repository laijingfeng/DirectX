//
// 默认两个三角形，边长为2
//

#ifndef __myrectH__
#define __myrectH__

#include <d3dx9.h>
#include "d3dUtility.h"

class MyRect
{
public:
	MyRect();
	MyRect(IDirect3DDevice9* Device, 
		float z = 1.0f, 
		int w = 1, int h = 1, 
		float xyFactor = 1.0f, 
		char* texPath = 0, 
		D3DMATERIAL9 mtrl = d3d::WHITE_MTRL,
		D3DMATERIAL9* mtrl2 = 0);
	~MyRect();

	bool draw(D3DXMATRIX* world);
private:
	int _w; // 横向分化（2的幂）
	int _h; // 纵向分化（2的幂）
	float _z; // Z轴位置
	float _xyFactor; // XY轴放大倍数
	IDirect3DDevice9* _device;
	IDirect3DVertexBuffer9* _vb; // 点集
	D3DMATERIAL9 _mtrl;
	D3DMATERIAL9* _mtrl2;
	IDirect3DTexture9* _tex;
};

#endif // __myrectH__