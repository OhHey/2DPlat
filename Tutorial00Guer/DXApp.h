#pragma once

#include <Windows.h>
#include <string>
#include "DXUtil.h"
#include "Input.h"
#include "GameTimer.h"

class DXApp
{
public:
	DXApp(HINSTANCE hInstance);
	virtual ~DXApp(void);

	//MAIN APPLICATION LOOP
	int Run();

	//FRAMEWORK METHODS
	virtual bool Init();
	virtual void Update(float dt) = 0;
	virtual void Render(float dt) = 0;
	virtual LRESULT MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

protected:

	//WIN32 ATTRIBUTES
	HWND		m_hAppWnd;
	HINSTANCE	m_hAppInstance;
	UINT		m_ClientWidth;
	UINT		m_ClientHeight;
	std::string m_AppTitle;
	DWORD		m_WndStylel;

	//DIRECTX ATTRIBUTES
	ID3D11Device*			m_pDevice;
	ID3D11DeviceContext*	m_pImmediateContext;
	IDXGISwapChain*			m_pSwapChain;
	ID3D11RenderTargetView*	m_pRenderTargetView;
	D3D_DRIVER_TYPE			m_DriverType;
	D3D_FEATURE_LEVEL		m_FeatureLevel;
	D3D11_VIEWPORT			m_Viewport;



	//Input Class
	Inputer theInput;

	//Timer Class
	GameTimer theTimer;

protected:

	//INITIALIZE THE WIN32 WINDOW
	bool InitWindow();

	//INITIALIZE DIRECT3D
	bool InitDirect3D();
};

