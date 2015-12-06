#ifndef __d3dUtilityH__
#define __d3dUtilityH__

#include <d3dx9.h>
#include <string.h>

namespace d3d
{
    // 初始化.
	bool InitD3D(
		HINSTANCE hInstance,		// [in] Application instance.
		int width, int height,		// [in] Back buffer dimensions
		bool windowed,				// [in] Windowed (true) or full screen (false).
		D3DDEVTYPE deviceType,		// [in] HAL or REF.
		IDirect3DDevice9** device);	// [out] The created device.

	// 应用程序消息循环.
	int EnterMsgLoop(
		bool (*ptr_display)(float timeDelta));	// [in] Display function pointer.

	LRESULT CALLBACK WndProc(
		HWND hwnd,
		UINT msg,
		WPARAM wParam,
		LPARAM lParam);

	// 释放COM接口置为NULL.
	template<class T> void Release(T t)
	{
		if(t)
		{
			t->Release();
			t = 0;
		}
	}

	// 删除自由堆中的对象，置为NULL.
	template<class T> void Delete(T t)
	{
		if(t)
		{
			delete t;
			t = 0;
		}
	}

	//
	// Colors
	//

	const D3DXCOLOR      WHITE( D3DCOLOR_XRGB(255, 255, 255) );
	const D3DXCOLOR      BLACK( D3DCOLOR_XRGB(  0,   0,   0) );
	const D3DXCOLOR        RED( D3DCOLOR_XRGB(255,   0,   0) );
	const D3DXCOLOR      GREEN( D3DCOLOR_XRGB(  0, 255,   0) );
	const D3DXCOLOR       BLUE( D3DCOLOR_XRGB(  0,   0, 255) );
	const D3DXCOLOR     YELLOW( D3DCOLOR_XRGB(255, 255,   0) );
	const D3DXCOLOR       CYAN( D3DCOLOR_XRGB(  0, 255, 255) );
	const D3DXCOLOR    MAGENTA( D3DCOLOR_XRGB(255,   0, 255) );

	//
	// Lights
	//

	D3DLIGHT9 InitDirectionalLight(D3DXVECTOR3* direction, D3DXCOLOR* color);
	D3DLIGHT9 InitPointLight(D3DXVECTOR3* position, D3DXCOLOR* color);
	D3DLIGHT9 InitSpotLight(D3DXVECTOR3* position, D3DXVECTOR3* direction, D3DXCOLOR *color);

	//
	// Materials
	//

	D3DMATERIAL9 InitMtrl(D3DXCOLOR a, D3DXCOLOR d, D3DXCOLOR s, D3DXCOLOR e, float p);

	const D3DMATERIAL9 WHITE_MTRL	= InitMtrl(WHITE, WHITE, WHITE, BLACK, 2.0f);
	const D3DMATERIAL9 RED_MTRL	= InitMtrl(RED, RED, RED, BLACK, 2.0f);
	const D3DMATERIAL9 GREEN_MTRL = InitMtrl(GREEN, GREEN, GREEN, BLACK, 2.0f);
	const D3DMATERIAL9 BLUE_MTRL = InitMtrl(BLUE, BLUE, BLUE, BLACK, 2.0f);
	const D3DMATERIAL9 YELLOW_MTRL = InitMtrl(YELLOW, YELLOW, YELLOW, BLACK, 2.0f);

	//
	// Texture
	//

	IDirect3DTexture9* InitTex(IDirect3DDevice9* Device, char* filePath);
}

#endif // __d3dUtilityH__