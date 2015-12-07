#include "d3dUtility.h"
#include "myrect.h"
#include "vertex.h"
#include "cube.h"
#include "myLog.h"

#pragma region Globals(全局变量)

// D3D
IDirect3DDevice9* Device = 0;

// 窗口的宽
const int Width		= 512;

// 窗口的高
const int Heigth	= 512;

#pragma region Variable(变量)

// 灯光
D3DLIGHT9 spotLight;

// 背景图1
MyRect* Bkg = 0;

// 背景图2
MyRect* Pic = 0;

// 立方体

Cube* cube = 0;

#pragma endregion Variable(变量)

#pragma endregion Globals(全局变量)

#pragma region FrameworkFunctions(框架函数)

// 设置
bool Setup()
{
	//
	// Rect.
	//

	cube = new Cube(Device);

	D3DMATERIAL9 mtrl = d3d::WHITE_MTRL;
	D3DMATERIAL9 mtrl1 = d3d::WHITE_MTRL;
	Bkg = new MyRect(Device, 1.01f, 64, 64, 10.0f, "bkg.png", d3d::WHITE_MTRL, &mtrl);
	Pic = new MyRect(Device, 1.00f, 32, 32, 5.0f, "pic.png", d3d::WHITE_MTRL, &mtrl1);
	
	//
	// Light.
	//

	D3DXCOLOR color = d3d::WHITE;
	spotLight = d3d::InitSpotLight(&D3DXVECTOR3(0.0f, 0.0f, -10.0f), &D3DXVECTOR3(0.0f, 0.0f, 1.0f), &color);

	Device->SetLight(0, &spotLight);
	Device->LightEnable(0, true);

	Device->SetRenderState(D3DRS_NORMALIZENORMALS, true);
	Device->SetRenderState(D3DRS_SPECULARENABLE, true);

	//
	// Useful switch.
	//

	Device->SetRenderState(D3DRS_LIGHTING, false);
	//Device->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	Device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	Device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	Device->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
	
	//
	// View matrix.
	//

	D3DXVECTOR3 pos(0.0f, 0.0f, -10.0f);
	D3DXVECTOR3 target(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);
	D3DXMATRIX V;
	D3DXMatrixLookAtLH(&V, &pos, &target, &up);
	Device->SetTransform(D3DTS_VIEW, &V);

	//
	// Set the projection matrix.
	//

	D3DXMATRIX proj;
	D3DXMatrixPerspectiveFovLH(
		&proj,
		D3DX_PI * 0.5,
		(float)Width / (float)Heigth,
		1.0f,
		1000.0f);

	Device->SetTransform(D3DTS_PROJECTION, &proj);

	return true;
}

// 清理
void Cleanup()
{
	d3d::Delete<MyRect*>(Bkg);
	d3d::Delete<MyRect*>(Pic);
	d3d::Delete<Cube*>(cube);
}

// 显示
bool Display(float timeDelta)
{
	if(Device)
	{
#pragma region BeforeDrawSetting(绘制前设置)

		//
		// KeyBoard
		//

		if( ::GetAsyncKeyState(VK_LEFT) & 0x8000f )
		{
			spotLight.Direction.x -= 0.5f * timeDelta;
		}

		if( ::GetAsyncKeyState(VK_RIGHT) & 0x8000f )
		{
			spotLight.Direction.x += 0.5f * timeDelta;
		}

		if( ::GetAsyncKeyState(VK_DOWN) & 0x8000f )
		{
			spotLight.Direction.y -= 0.5f * timeDelta;
		}

		if( ::GetAsyncKeyState(VK_UP) & 0x8000f )
		{
			spotLight.Direction.y += 0.5f * timeDelta;
		}

		if( ::GetAsyncKeyState('B') & 0x8000f )
		{
			spotLight.Direction.z -= 0.5f * timeDelta;
		}

		if( ::GetAsyncKeyState('F') & 0x8000f )
		{
			spotLight.Direction.z += 0.5f * timeDelta;
		}

		//  
		// update the light
		//

		Device->SetLight(0, &spotLight);
		Device->LightEnable(0, true);
		
		//
		// World matrix.
		//

		///*
		static float y = 0.0f;
		D3DXMATRIX Rx, Ry, Trans, I, p;
		D3DXMatrixIdentity(&Rx); // 单位矩阵
		D3DXMatrixIdentity(&Ry);
		D3DXMatrixIdentity(&Trans);
		D3DXMatrixIdentity(&I);
		D3DXMatrixIdentity(&p);
		
		D3DXMatrixRotationX(&Rx, D3DX_PI * 0.2f);
		D3DXMatrixRotationY(&Ry, y);
		D3DXMatrixTranslation(&Trans, -1.25f, 0.0f, 0.0f);
		y += timeDelta;
		if(y > 6.28f)
		{
			y = 0.0f;
		}
		
		p = Rx * Ry * Trans;
		Device->SetTransform(D3DTS_WORLD, &p);
		//*/

#pragma endregion BeforeDrawSetting(绘制前设置)
		
		Device->Clear(0, 0, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER , 0x00000000, 1.0f, 0);//0x00000000//0xffffffff

		Device->BeginScene();

#pragma region Draw(绘制)

	    if(cube)
	    {
		    cube->draw(0, 0, d3d::InitTex(Device, "pic.png"));
	    }
	
	    if(Bkg)
	    {	
		    Bkg->draw(0);
	    }	

	    //Device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	
	    if(Pic)
	    {
		    Pic->draw(0);
	    }
	
	    //Device->SetRenderState(D3DRS_ALPHABLENDENABLE, false);

#pragma endregion Draw(绘制)

		Device->EndScene();

		Device->Present(0, 0, 0, 0);
	}
	return true;
}

// 消息处理
LRESULT CALLBACK d3d::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg)
	{
	case WM_DESTROY:
		::PostQuitMessage(0);
		break;
	case WM_KEYDOWN:
        // Esc退出
		if(wParam == VK_ESCAPE)
		{
			::DestroyWindow(hwnd);
		}
        else if(wParam == VK_ADD)
        {
            MyLog::Log("hello,my name is %d %s\n",1,"lai");
        }
		break;
	}

	return ::DefWindowProc(hwnd, msg, wParam, lParam);
}

// main
int WINAPI WinMain( HINSTANCE instance, HINSTANCE prevInstance, LPSTR cmdLine, int showCmd )
{
	if(!d3d::InitD3D(instance, Width, Heigth, true, D3DDEVTYPE_HAL, &Device))
	{
		::MessageBox(0, "InitD3D() - FAILED", 0, 0);
		return 0;
	}

	if(!Setup())
	{
		::MessageBox(0, "Setup() - FAILED", 0, 0);
		return 0;
	}

	d3d::EnterMsgLoop(Display);

	Cleanup();

	Device->Release();

	return 0;
}

#pragma endregion FrameworkFunctions(框架函数)
