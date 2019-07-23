#pragma once
#ifndef _DEVICE_MANAGER_H_
#define _DEVICE_MANAGER_H_

class DeviceManager
{
	DECLARE_SINGLETON(DeviceManager);

private:
	DeviceManager();
	~DeviceManager();

public:
	enum SCREEN_MODE {
		FULLSCREEN,
		WINDOWED
	};

public:
	void Release();

public:
	HRESULT InitDevice(
		HWND hWnd,
		const DWORD &dwWinWidth, const DWORD &dwWinHeight,
		SCREEN_MODE eScreenMode
	);

	void RenderBegin();
	void RenderEnd();

public:
	LPDIRECT3DDEVICE9 getDevice() const { return m_pGraphicDev; }
	LPD3DXSPRITE getSprite() const { return m_pSprite; }
	LPD3DXLINE getLine() const { return m_pLine; }

private:
	// ###############################################################################################################
	// ### Direct3D
	// - 3D ���� �ϵ��� �̿��Ͽ�, 3D ������ ǥ���� �� �ֵ��� ���ִ� ������ �׷��� API(Application Programming Interface)

	// Application -> Direct3D -> HAL -> Graphic Device

	// Direct3D�� ����� ��� �׷��� �ϵ����� ������ ���̶�� ������ No !!!!
	// So, Direct3D�� �׷��� ��ġ ���̿� HAL(Hardware Abstraction Layer - �ϵ���� �߻� ����)�� �����Ѵ�.
	// - �����簡 �ٸ� �׷��� ī����� �پ��� ������� �����ϱ� ������, Direct3D�� ���� �׷��� ��ġ�� ������ �� ����.
	//  �����翡�� HAL(�ּ����� ����� ���)�� �����ϵ��� �䱸�Ѵ�.
	// So, Direct3D�� �� ��ġ�� �������� �κ��� ������ �ʿ䰡 ��������, (�ϵ��� ������)�� ���� �ִ� !!!!

	// REF(Reference Rasterizer) ��ġ
	// - �׷��� ��ġ�� ���������� ������, Direct3D���� �����ϴ� ����� �̿��ؾ� �� �� !!!!
	//  Direct3D API�� ��� ����� ����Ʈ����� ������ �� �ִ� ��ġ?!

	// D3DDEVTYPE ������ (��ġ ���� �� �ݵ�� �ʿ��ϸ�, ��ġ�� Ÿ�� �����ϴ� enum ���)
	// - HAL ��ġ�� D3DDEVTYPE_HAL �� ������.
	// - REF ��ġ�� D3DDEVTYPE_REF �� ������.

	// COM(Component Object Model)
	// - DirectX�� (���α׷��� �� ������)�̰�, ���� ȣȯ���� ���� �� �ְ� �ϴ� ��� !!!!
	// - COM ��ü�� �������̽���� �θ���.
	// - �ٸ� COM �������̽��� �޼ҵ峪 Ư���� �Լ��� ���� COM �������̽��� �����͸� ��´� ?!
	// - new Ű����� �������̽��� ����� ���� �ƴϸ�, ����� ������ �ݵ�� �������̽��� Release() �޼ҵ带 ȣ��.
	// So, COM ��ü�� �ڽ��� �޸� ������ ������ �����Ѵ� !!!!

	// ǥ��(Surface)
	// - 2D �̹��� �����͸� �����ϴ� �� �̿�Ǵ� �ȼ�(Surface�� ���)�� ���
	// - ���� �迭�� �����ȴ�.
	// - Surface�� �ʺ�� ���̴� (�ȼ� ����)�� ���.
	// - ��ġ�� ����Ʈ�� ���Ǹ� �ʺ񺸴� �� ���� �ִ� !!!!
	// - IDirect3DSurface9 �������̽��� ǥ���� �̿��� �� �ִ�.
	// �Լ��Լ��Լ���...

	// ��Ƽ ���ø�(MultiSampling)
	// - Pixel Matrix�� �̹����� ǥ���� ��, ��ģ �̹����� �ε巴�� ����� �� �̿�Ǵ� ���.
	// ��ȭ�� Anti-Aliasing�� ���� ǥ�� ��Ƽ ���ø��� �ִ�.
	// - D3DMULTISAMPLE_TYPE ������ - ��Ƽ ���ø� ���� ���� (D3DMULTISAMPLE_NONE, ���ϰ� ���ϱ� ������ !!!!)
	// - ��Ƽ ���ø� Ÿ�԰� ����� ǰ�� ���� (DWORD - "0")

	// �ȼ� ����(Pixel Format)
	// Surface�� Texture�� ����� ���ؼ� Pixel Format�� �����ؾ� �Ѵ�.
	// D3DFORMAT ������ ��� - D3DFMT_A8R8G8B8 (32 ��Ʈ �ȼ� ����, 8��Ʈ�� ����,����,�׸�,����)
	// ������ ������������...

	// �޸� Ǯ(Memory Pool)
	// - �����̳� �� ���� �پ��� Direct3D �ڿ����� Memory Pool�� �����ȴ�.
	// ������ ������������...

	// ���� ü��(Swap Chain)�� ������ �ø���(Page Flipping)
	// - (���� 2~ 3���� Surface�� �ϳ��� �÷���)���� �����Ѵ�. (���� ü���̶�� �θ�?!)
	// IDirect3DSwapChain9 �������̽��� ���� �̿��� �� ������, ��κ��� �۾��� Direct3D�� ���� ����.
	// - Frame ���� �ε巯�� �ִϸ��̼��� �����ϱ� ���� Swap Chain, Page Flipping ����� ���δ�.
	// ex. 2���� Surface ������ Swap Chain
	// Surface 1 - ���� ���� (���� ����Ϳ��� ������ ������ �������� �ִ� ����)
	// Surface 2 - �ĸ� ���� (���� ó������ �������� �����Ǵ� ����

	// - ����Ͱ� ���� ������ �̹����� �ﰢ������ ������ �� �ִ� ���� �ƴϸ�,
	// 60Hz�� ������� ����ʹ� 1/60�� �����ǽð��� �ʿ��ϴ�.
	// - Application�� ���������� ������� ������� ����ȭ ���� �ʴ� ���,(Application�� ������ �������� �� ���� ��...)
	// ���� �������� ������ ���÷��� ���� ���� ���¿��� �ִϸ��̼��� ���� ���������� �����ϴ� ���� X...
	// �׷��ٰ� ���� ������ ���÷��̸� ��ĥ ������ �������� ���ߴ� �͵� X...
	//  So, ȭ�� ���� Surface(�ĸ� ����)�� �������� �����ϰ�, ���� ���� Surface�� ���÷��̰� �Ϸ�Ǹ�,
	// Swap Chain�� ������ ���ư� �ĸ� ���۸� ���� ���۷� ��ȯ�ϴ� ����� �̿��Ͽ� �ذ��մϴ� !!!!
	// �� ������ "Presenting - �ÿ�"�̶�� �մϴ�.
	// ����, �ĸ� ���۰� ���� ���۰� �ǰ�, ���� ���۰� �ĸ� ���۰� �Ǵ� �� cycle�� "Page Flipping - ������ �ø���"�̶�� �մϴ�.
	// ##################################
	// So, Swap Chain�� Page Flipping����
	// ##################################
	// �ĸ� ���� ������ - �ĸ� ���� �ÿ�(���� ���۰� �ȴ�) - ���� ü���� �޺κ����� �Ѿ��.


	// ���� ����(Depth Buffer)
	// - �̹��� �����Ͱ� �ƴ� Ư�� �ȼ��� ���� ������ �����ϴ� Surface�� ���մϴ�.
	// - ���� �������� �̹����� �� �ȼ��� �ش��ϴ� �׸��� �����մϴ�.
	// - Direct3D�� ��ü�� �ȼ��� �ٸ� �ȼ��� �������� ���θ� ����, "���� ���۸�(Depth Buffering), Z-Buffering"�� ����մϴ�.

	// ���� ���۸�(Depth Buffering, Z-Buffering)
	// - �� �ȼ��� ���� ���� ����ϰ�, ���� �׽�Ʈ�� �����մϴ�.
	// �� ���������� Ư�� �ȼ��� ��ġ���� �����ϴ� �ȼ��� ���̸� ���մϴ�.
	// - (ī�޶�� ���� ����� ���� ��)�� ������ �ȼ��� �̹����� �׷����ϴ� !!!!
	// - ���� ���� �ּ� "0"~ �ִ� "1"���� �ε��Ҽ��� ���� ���� �˴ϴ�...(�ʱ�ȭ�� ������ 1.0f)
	// - ���� ������ ������ ���� �׽�Ʈ�� ��Ȯ���� �ǹ��մϴ�. (Direct3D�� 32��Ʈ ���� ���۸� ����������...)
	//  D3dFMT_D24S8�� �ַ� ����մϴ�. (24bits ���� ����, 8bits Stencil ����)

	// Vertex Processing
	// - Vertex�� 3D ���� ��ü�� �����ϴ� �⺻ �����Դϴ�.
	// ó�� ����� �ϵ���� �Ǵ� ����Ʈ������ ���...
	// - �׷��� ī�尡 Hardware Vertex Processing�� �����Ѵٴ� ����...
	//  ��ȯ(Transformation)�� ���� ���(Lighting)�� �ϵ���������� ó���� �� �ִٴ� �ǹ�.

	// ��ġ Ư��
	// - Direct3D�� ��� ��ɵ��� D3DCAPS9 ����ü�� ������ ����� �����˴ϴ�.
	// So, �����ϰ� �ִ� �ϵ������ Ư���� ���� D3DCAPS9 �ν��Ͻ��� ����� �ʱ�ȭ �ؼ�,
	// Application�� D3DCAPS9 �ν��Ͻ��� �����͸� Ȯ���Ͽ� ��ġ�� Ư�� ����� �����ϴ��� �� �� �ֽ��ϴ�.

	// ex. Hardware Vertex Processing ���� ���� �Ǵ�
	// - D3DCAPS9::DevCaps�� ������ ������� D3DDEVCAPS_HWTRANSFORMANDLIGHT ��Ʈ�� ã���� �ȴ�.

	// cf) DevCaps ( Device Capabilities)

	// ###############################################################################################################

	// Direct3D �ʱ�ȭ ����
	// step 01. IDirect3D9 �������̽��� ������ ��´�.

	// step 02. "Default Display Adapter"�� Hardware Vertex Processing�� �����ϴ���, D3DCAPS9 ����ü�� Ȯ���Ѵ�.

	// step 03. D3DPRESENT_PARAMETERS ����ü �ν��Ͻ��� �ʱ�ȭ�Ѵ�. (������� �ϴ� IDirect3DDevice9 �ν��Ͻ��� Ư�� ����)

	// step 04. IDirect3DDevice9 ��ü�� �����. (�ʱ�ȭ�� D3DPRESENT_PARAMETERS�� ����...)

	// ###############################################################################################################


	// IDirect3D9	- ��ġ����(�ý����� �ϵ��� ���� ����, ����� �����ϴ��� ���� Ȯ��)
	//				- IDirect3DDevice9 COM ��ü�� �����ϴ� COM ��ü.
	LPDIRECT3D9				m_pSDK;

	// IDirect3DDevice9 - �׷��� ��ġ�� �����ϴ� COM ��ü.
	//					- 3D �׷����� ���÷����ϴ� �� �̿�� ���� �ϵ���� ��ġ.
	LPDIRECT3DDEVICE9		m_pGraphicDev;

	// ID3DXSprite	- Direct���� 2D �̹��� �������� �ʿ��� COM ��ü
	LPD3DXSPRITE			m_pSprite;

	// ID3DXLine - Line �������� �ʿ��� COM ��ü
	LPD3DXLINE				m_pLine;

	// COM (Component Object Model) - ��� ���� COM ��ü?!
};

#endif