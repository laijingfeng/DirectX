#include "myrect.h"
#include "vertex.h"
#include "d3dUtility.h"

MyRect::MyRect()
{

}

MyRect::MyRect(IDirect3DDevice9* Device, 
	float z /*= 1.0f*/, 
	int w /*= 1*/, int h /*= 1*/, 
	float xyFactor /*= 1.0f*/, 
	char* texPath /*= 0*/, 
	D3DMATERIAL9 mtrl /*= d3d::WHITE_MTRL*/,
	D3DMATERIAL9* mtrl2 /* = 0 */)
{
	_device = Device;
	_z = z;
	_w = w;
	_h = h;
	_xyFactor = xyFactor;
	_mtrl = mtrl;
	_mtrl2 = mtrl2;

	//
	// Texture.
	//

	if(texPath)
	{
		D3DXCreateTextureFromFile(
			Device,
			texPath,
			&_tex);
	}
	else
	{
		_tex = 0;
	}

	_device->CreateVertexBuffer(
		6 * _w * _h * sizeof(Vertex),
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX,
		D3DPOOL_MANAGED,
		&_vb,
		0);

	Vertex* v = 0;
	_vb->Lock(0, 0, (void**)&v, 0);

	int i, j, iIndex; 
	for(i = 0, iIndex = 0; i < _w ; i++)
	{
		for(j = 0; j < _h ; j++)
		{
			float fXBase = -1.0f;
			float fYBase = +1.0f;

			v[iIndex++] = Vertex((fXBase + (i + 0) * 2.0f / _w) * _xyFactor, (fYBase - ((j + 1) * 2.0f / _h) ) * _xyFactor, _z, 0.0f, 0.0f, -1.0f, (i + 0) * 1.0f / _w, (j + 1) * 1.0f / _h); // 0
			v[iIndex++] = Vertex((fXBase + (i + 0) * 2.0f / _w) * _xyFactor, (fYBase - ((j + 0) * 2.0f / _h) ) * _xyFactor, _z, 0.0f, 0.0f, -1.0f, (i + 0) * 1.0f / _w, (j + 0) * 1.0f / _h); // 1
			v[iIndex++] = Vertex((fXBase + (i + 1) * 2.0f / _w) * _xyFactor, (fYBase - ((j + 0) * 2.0f / _h) ) * _xyFactor, _z, 0.0f, 0.0f, -1.0f, (i + 1) * 1.0f / _w, (j + 0) * 1.0f / _h); // 2

			v[iIndex++] = Vertex((fXBase + (i + 0) * 2.0f / _w) * _xyFactor, (fYBase - ((j + 1) * 2.0f / _h) ) * _xyFactor, _z, 0.0f, 0.0f, -1.0f, (i + 0) * 1.0f / _w, (j + 1) * 1.0f / _h); // 0
			v[iIndex++] = Vertex((fXBase + (i + 1) * 2.0f / _w) * _xyFactor, (fYBase - ((j + 0) * 2.0f / _h) ) * _xyFactor, _z, 0.0f, 0.0f, -1.0f, (i + 1) * 1.0f / _w, (j + 0) * 1.0f / _h); // 2
			v[iIndex++] = Vertex((fXBase + (i + 1) * 2.0f / _w) * _xyFactor, (fYBase - ((j + 1) * 2.0f / _h) ) * _xyFactor, _z, 0.0f, 0.0f, -1.0f, (i + 1) * 1.0f / _w, (j + 1) * 1.0f / _h); // 3
		}
	}
	_vb->Unlock();
}

MyRect::~MyRect()
{
	if(_vb)
	{
		_vb->Release();
		_vb = 0;
	}

	if(_tex)
	{
		_tex->Release();
		_tex = 0;
	}
}

bool MyRect::draw(D3DXMATRIX* world)
{
	if(world)
	{
		_device->SetTransform(D3DTS_WORLD, world);
	}

	if(&_mtrl)
	{
		_device->SetMaterial(&_mtrl);
		//_device->SetMaterial(_mtrl2);
	}

	if(_tex)
	{
		_device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
		_device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
		_device->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);

		_device->SetTexture(0, _tex);
	}

	_device->SetStreamSource(0, _vb, 0, sizeof(Vertex));
	_device->SetFVF(FVF_VERTEX);
	_device->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2 * _w * _h);

	return true;
}