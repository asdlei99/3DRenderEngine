/**
 *	@author		zhuqingquan
 *	@date		2014-10-17
 *	@name		DxRender_D3D11.h
 *	@brief		The Display engine impleted in DirextX11 3D
 */

#pragma once
#ifndef _ZRENDER_DXRENDER_D3D11_H_
#define _ZRENDER_DXRENDER_D3D11_H_

//because this display engine is impletemented by directx11 3D
//so it can only compile in windows
#ifdef _WINDOWS

#include <Windows.h>
#include <d3d11.h>
#include <xnamath.h>
#include <map>
#include "DxRenderCommon.h"
#include "DisplayElement.h"
#include "Effects.h"
#include "BackgroundDisplayComponent.h"
#include "rendertextureclass.h"

namespace zRender
{
	class SharedResource;
	class SharedTexture;
	class D3D11TextureRender;
	class BackbufferRenderTarget;

	/**
	 *	@name	DxRender_D3D11
	 *	@brief	ʹ��DirectX11 3D����ʵ�ֵ���ʾ����
	 */
	class DxRender_D3D11
	{
	public:
		/**
		 *	@name	DxRender_D3D11
		 *	@brief	���췽�������󴴽��������init��ʼ����Դ
		 */
		DxRender_D3D11();

		/**
		 *	@name	~DxRender_D3D11
		 *	@brief	�����������ͷ����д�������Դ
		 */
		~DxRender_D3D11();

		/**
		 *	@name		setVisibleRegion
		 *	@brief		���ø�Device��ʾ����ϵ�е�����ֻ������������ڵ�������ܱ���ʾ
		 *	@param[in]	RECT_f& visibleReg ����ϵ�е����򣬲�����z����
		 *	@return		int 0--�ɹ�  ��0--ʧ��
		 */
		int setVisibleRegion(const RECT_f& visibleReg);

		/**
		 *	@name	getVisibleREgion
		 *	@brief	��ȡ��Device��ʾ����ϵ�е�����
		 **/
		RECT_f getVisibleRegion() const;

		/**
		 *	@name		init
		 *	@brief		��ʼ����ʾ���棬������ʾ�������Դ
		 *				���ַ�ʽ��������ʾ���潫Ĭ�ϴ���Swapchainֱ���봰��hWnd�������û����Ƶ�����Ĭ��ֱ����Ⱦ�ڴ�����
		 *	@param[in]	HWND hWnd ������ʾ���ݵ�Windows���ھ��
		 *	@param[in]	isEnable4XMSAA �Ƿ�֧��MSAA��Ĭ��Ϊfalse
		 *				����ò���Ϊtrue����isSDICompatible����Ϊtrue
		 *	@param[in]	isSDICompatible �Ƿ�֧�ֻ�ȡHDC�������GDI��Ⱦ
		 *				����ò���Ϊfalse����lockBackbufferHDC�ӿڵ���ʧ��
		 *				����ò���Ϊtrue����isEnable4XMSAA����Ϊtrue
		 *	@return		int 0--�ɹ�  ��0--ʧ��
		 */
		int init(HWND hWnd, bool isEnable4XMSAA = false, bool isSDICompatible = false);

		
		/**
		 *	@name		init
		 *	@brief		��ʼ����ʾ���棬������ʾ�������Դ
		 *				��������������Offscreen RenderTarget����������Դ����adapterָ�����Կ��ϴ���
		 *	@param[in]	int width ������
		 *	@param[in]	int height �ߣ�����
		 *	@param[in]	int adapter �Կ����
		 *	@param[in]	isSDICompatible �Ƿ�֧�ֻ�ȡHDC�������GDI��Ⱦ
		 *				����ò���Ϊfalse����lockBackbufferHDC�ӿڵ���ʧ��
		 *				����ò���Ϊtrue����isEnable4XMSAA����Ϊtrue
		 *	@return		int 0--�ɹ�  ��0--ʧ��
		 */
		int init(int width, int height, int adapter = 0, bool isSDICompatible = false);

		/**
		 *	@name		init
		 *	@brief		�÷�����ʹ��hmonitor�������ӵ�Adapter�ϴ���Device
		 *				�÷���ֻ����Device��������������present�������Դ��������������createSharedTexture�ӿڵĵ���
		 *	@param[in]	HMONITOR hmonitor ϵͳ����ľ��
		 *	@return		int 0--�ɹ�  ��0--ʧ��
		 */
		int init(HMONITOR hmonitor);

		/**
		 *	@name		deinit
		 *	@brief		�ͷ���ʾ�����д�������Դ
		 */
		void deinit();

		/**
		 *	@name		createDisplayElement
		 *	@brief		����DisplayElement���󣬴���һ����ʾ������
		 *				����ʱ����DisplayElement��Ӧ����Դ��δ��������Դ�ڵ���DisplayElement�Ľӿ�ʱ����
		 *				DxRender������ȷ��ʼ��֮����ܵ��ô����ӿڴ���������Դ����
		 *	@param[in]	const RECT_f& displayReg ����ʾ������������ϵ�е�λ��
		 *	@param[in]	int zIndex ��ǰ��ʾԭʼ���ڶ����Z����ƫ��
		 *	@return		DisplayElement* ����ָ�룬ʧ��ʱΪNULL��������displayReg��ʾ��λ�ò��ڱ�Render�Ŀ���������ʱ����ʧ��
		 */
		DisplayElement* createDisplayElement(const RECT_f& displayReg, int zIndex, DxRender* dxRender);
		
		/**
		 *	@name		releaseDisplayElement
		 *	@brief		�ͷ�DisplayElement����
		 *				�ͷ�DisplayElement�����е���Դ����ɾ������
		 *	@param[in]	DisplayElement** displayElement ָ��DisplayElement����ָ���ָ�룬DisplayElement�����ͷųɹ������ָ�뱻��NULL
		 *	@return		int 0--�ɹ�   <0--ʧ��
		 */
		int releaseDisplayElement(DisplayElement** displayElement);

		int createTextureResource(TextureResource** ppOutTexRes, int width, int height, DXGI_FORMAT dxgiFmt, TEXTURE_USAGE usage, bool bShared, const char* initData= NULL, int dataLen = 0, int pitch = 0);
		int createTextureResource(const TextureSourceDesc& srcDesc, TextureResource** ppOutTexRes);

		int openSharedTextureResource(TextureResource** ppOutTexRes, HANDLE hSharedRes);
		void releaseTextureResource(TextureResource** ppOutTexRes);

		/**
		 *	@name		createTexture
		 *	@brief		����Texture����
		 *				Texture���������һ��������ͼƬ����ͼƬ��һ���֣�Texture������ID3D11Texture2D��Դ
		 *				DxRender������ȷ��ʼ��֮����ܵ��ô����ӿڴ���������Դ����
		 *	@param[in]	YUVFormat_Packed pixFmt Texture�е����ظ�ʽ
		 *	@param[in]	int width Texture�����ؿ�
		 *	@param[in]	int height Texture�����ظ�
		 *	@param[in]	unsigned char* initData ��ʼ��Texture�����ݣ�Ĭ��ΪNULL
		 *	@param[in]	int initDataLen ��ʼ��Texture�����ݵĳ��ȣ�Ĭ��Ϊ0
		 *	@param[in]	bool isShared ��ʾ������Texture�Ƿ���ڶ��ID3D11Device�����й���
		 *	@return		YUVTexture_Packed* Texture�����ָ�룬ʧ��ΪNULL�����������Ϸ������Կ���Դ����ʱ������ʧ��
		 */
		IRawFrameTexture* createTexture(PIXFormat pixFmt, int width, int height, 
							unsigned char* initData = NULL, int initDataLen = 0, bool isShared = false);

		IRawFrameTexture* createTexture(PIXFormat pixfmt, int width, int height, TEXTURE_USAGE usage, bool bShared, unsigned char* initData, int dataLen, int pitch);

		IRawFrameTexture* openSharedTexture(IRawFrameTexture* sharedTexture);

		/**
		 *	@name		releaseTexture
		 *	@brief		�ͷ�Texture����
		 *				�ͷ�Texture�����е���Դ����ɾ�����󡣶����ͷŽ�������������ʾ�������³������
		 *	@param[in]	YUVTexture_Packed** texture ָ��Texture����ָ���ָ�룬Texture�����ͷųɹ������ָ�뱻��NULL
		 *	@return		int 0--�ɹ�   <0--ʧ��
		 **/
		int releaseTexture(IRawFrameTexture** texture);

		/**
		 *	@name		createVertexBuffer
		 *	@brief		����������Ϣ��ID3D11Buffer��Դ������Դ���Կ��������Դ�
		 *				��������ԴΪD3D11_USAGE_IMMUTABLE���͵ģ������޸�
		 *	@param[in]	int byteCount ��������Դ�����ֽ���
		 *	@param[in]	const unsigned char* initData ��ʼ�����ݣ��ò�������ΪNULL����Ϊ������������D3D11_USAGE_IMMUTABLE
		 *	@param[in]	int initDataLen ��ʼ�����ݵĳ��ȣ�����>=byteCount
		 *	@return		ID3D11Buffer* ���ش�����ID3D11Buffer����ָ�룬ʧ�ܷ���NULL
		 **/
		ID3D11Buffer* createVertexBuffer(int byteCount, const unsigned char* initData, int initDataLen);

		/**
		 *	@name		createVertexBuffer
		 *	@brief		����С����Ϣ��ID3D11Buffer��Դ������Դ���Կ��������Դ�
		 *				��������ԴΪD3D11_USAGE_IMMUTABLE���͵ģ������޸�
		 *	@param[in]	int byteCount ��������Դ�����ֽ���
		 *	@param[in]	const unsigned char* initData ��ʼ�����ݣ��ò�������ΪNULL����Ϊ������������D3D11_USAGE_IMMUTABLE
		 *	@param[in]	int initDataLen ��ʼ�����ݵĳ��ȣ�����>=byteCount
		 *	@return		ID3D11Buffer* ���ش�����ID3D11Buffer����ָ�룬ʧ�ܷ���NULL
		 **/
		ID3D11Buffer* createIndexBuffer(int byteCount, const unsigned char* initData, int initDataLen);

		/**
		 *	@name		releaseBuffer
		 *	@brief		�ͷ�ID3D11Buffer����ͨ��createVertexBuffer�Ƚӿڴ�����ID3D11Buffer��Դͳһͨ���ýӿ��ͷ�
		 *				�ͷ�ID3D11Buffer�����е���Դ����ɾ�����󡣶����ͷŽ��������ã������³������
		 *	@param[in]	ID3D11Buffer** buffer ָ��ID3D11Buffer����ָ���ָ�룬ID3D11Buffer�����ͷųɹ������ָ�뱻��NULL
		 *	@return		int 0--�ɹ�   <0--ʧ��
		 **/
		int releaseBuffer(ID3D11Buffer** buffer);

		/**
		 *	@name		setupBackground
		 *	@brief		���ò����ñ����Ļ������ݵ��ṩ���Լ��������������潫���ṩ���ṩ��������ʾ��displayReg��ʾ��������
		 *	@param[in]	IDisplayContentProvider* contentProvider �����Ļ������ݵ��ṩ��
		 *	@param[in]	const RECT_f& displayReg �ñ�������������ϵ�е�λ��
		 *	@return		int 0--�ɹ�   <0--ʧ�ܣ����Ѿ�����ʱ�ڵ�������Ҳ������ʧ��
		 **/
		//int setupBackground(BackgroundComponent* bgComponent);

		/**
		 *	@name		cancleBackground
		 *	@brief		ȡ������������ʾ
		 *	@return		int 0--�ɹ�   <0--ʧ��
		 **/
		//int cancleBackground();

		/**
		 *	@name		draw
		 *	@brief		����DisplayElement�б��ֵ���ʾ����
		 *				DxRender������ȷ��ʼ��֮����ܵ��û��ƽӿڻ��Ƹ�����Դ����
		 *	@param[in]	DisplayElement* displayElem ��ʾ���ݶ��󣬸ö����еĶ��㡢Texture�Ƚ��ᱻ����
		 *	@return		int 0--�ɹ�   <0--ʧ��
		 */
		int draw(DisplayElement* displayElem);

		/**
		 *	@name		draw
		 *	@brief		ֱ�ӽ�TextureResource�����ݻ��Ƶ�RenderTarget��
		 *				û�в�εĴ�����������ص��������»��ƵĽ�����ǰ����Ƶ�����
		 *	@param[in]	TextureResource * texture Texture��Դ
		 *	@param[in]	const RECT & region texture���Ƶ�����
		 *	@return		int 0--�ɹ� <0--ʧ��
		 **/
		int draw(TextureResource* texture, const RECT& region);

		/**
		 *	@name		clear
		 *	@brief		��DxRender��������ʾ�����������ʾ������ɫ
		 *	@param[in]	DWORD color ������ɫ
		 *	@return		int 0--�ɹ�   <0--ʧ��
		 */
		int clear(DWORD color);

		/**
		 *	@name		clear
		 *	@brief		��DxRender���ض��������ʾ�����������ʾ������ɫ
		 *	@param[in]	const RECT_f& clearReg DxRender�е���ʾ����
		 *	@param[in]	DWORD color ������ɫ
		 *	@return		int 0--�ɹ�   <0--ʧ��
		 */
		//int clear(const RECT_f& clearReg, DWORD color);  // fixme

		/**
		 *	@name		present
		 *	@brief		���Կ��е���������ʾ�豸�г���
		 *				DxRender������ȷ��ʼ��֮����ܵ��ó��ֽӿ�
		 *	@param[in]	int type	����
		 *	@return		int 0--�ɹ�   <0--ʧ��
		 */
		int present(int type);

		/**
		 *	@name			lockBackbufferHDC
		 *	@brief			��ȡBackBuffer��HDC���������ʾGDI����
		 *					����˵�����Բο�IDXGISwapChain::GetDC��˵��
		 *	@param[in]		BOOL Discard 
		 *	@param[in]		HDC * outHDC 
		 *	@ThreadSafe		No
		 *	@return			int 0--�ɹ� ����--ʧ��
		 **/
		int lockBackbufferHDC(BOOL Discard, HDC* outHDC);
		/**
		 *	@name			unlockBackbufferHDC
		 *	@brief			�ͷ�ͨ��lockBackbufferHDC��ȡ��HDC���
		 *					����lockBackbufferHDC��HDCʹ����֮�������øýӿڽ����ͷ�
		 *	@param[in]		HDC hdc 
		 *	@ThreadSafe		No
		 *	@return			int 0--�ɹ� ����--ʧ��
		 **/
		int unlockBackbufferHDC(HDC hdc);

		/**
		 *	@name			getSnapshot
		 *	@brief			Get the snapshot of the current view for RenderTarget
		 *	@param[out]		unsigned char * pData Destination buffer use to save the picture data of snapshot
		 *	@param[in,out]	UINT & datalen The total length of the destination buffer and save the data length valid when get snapshot success
		 *	@param[out]		int & w Picture width of snapshot
		 *	@param[out]		int & h Picture height of snapshot
		 *	@param[out]		int & pixfmt Picture data pixel format of snapshot
		 *	@param[out]		int & pitch Picture data pitch of snapshot
		 *	@return			bool 0--success other--failed
		 **/
		int getSnapshot(unsigned char* pData, UINT& datalen, int& w, int& h, int& pixfmt, int& pitch);
		/**
		*	@name			getSnapshot
		*	@brief			��RenderTarget�е����ݿ�������
		*					���е���createOffscreenRenderTarget�ɹ�ʱ��ͨ�������ж�ʱ��Ҫ��ȡOffscreen texture����Backbuffer��Texture
		*	@param[in]		TEXTURE_USAGE usage The texture usage type for saved the snapshot
		*	@param[in]		bool bShared Is the result texture can be shared
		*	@param[in]		bool fromOffscreenTexture True for get the snapshot of Offscreen texture, otherwise get Backbuffer snapshot
		*					if createOffscreenRenderTarget never called success, allways get the snapshot of Offscreen texture
		*	@return			TextureResource* result of Texture saved the snapshot.NULL for failed.
		**/
		TextureResource* getSnapshot(TEXTURE_USAGE usage, bool bShared, bool fromOffscreenTexture);

		int createOffscreenRenderTarget(int width, int height);
		void releaseOffscreenRenderTarget();

		void* getDevice() const;
		void* getContext() const { return m_context; }
		int getWidth();
		int getHeight();
		float getAspectRatio() const { return m_aspectRatio; }
		int resize(int new_width, int new_height);

		const XMFLOAT4X4& getViewTransformMatrix() const { return m_viewTransform; }
		const XMFLOAT4X4& getProjectionTransformMatrix() const { return m_projTransform; }
	private:
		DxRender_D3D11(const DxRender_D3D11&);
		DxRender_D3D11& operator=(const DxRender_D3D11&);

		ID3D11Buffer* createBuffer(int byteCount, const unsigned char* initData, int initDataLen,
									D3D11_USAGE usage, UINT bindFlag);

		int setRenderTargetTexture();
		int setRenderTargetBackbuffer();

		int drawOffscreenRenderTarget(); 
		int clearBackbuffer(DWORD color);
		int clearRenderTargetTexture(DWORD color);

		ID3D11Texture2D* getRenderTargetTexture();

		// �ж��Ƿ�RenderTarget��ʼ�����óɹ�
		bool isRenderTargetSetted();

		bool CreateTransparentBlendState();
	private:
		IDXGIAdapter* m_adapter;
		ID3D11Device* m_device;
		ID3D11DeviceContext* m_context;
		ID3D11RenderTargetView* m_renderTargetView;
		D3D11_VIEWPORT m_viewport;

		HWND m_hWnd;
		RECT_f m_visibleReg;
		float m_aspectRatio;

		XMFLOAT4X4 m_viewTransform;
		XMFLOAT4X4 m_projTransform;
		//Material m_material;
		IDXGISurface1* m_bkbufDxgiSurface;
		ID3D11BlendState* m_TransparentBS;

		//BackgroundComponent* m_backgroundComponent;
		DWORD m_color;
		BackbufferRenderTarget* m_bkbufRT;
		RenderTextureClass* m_renderTargetTexture;//Offscreen Render Target Texture
		D3D11TextureRender* m_offscreenRttRender;	//��������offscreen��rendertarget������Ⱦ��Offscreen֮����ͨ���������ʵ�ֽ�offscreen��RTT��Ⱦ��Backbuffer��
	};
}
#endif

#endif //_zRENDER_DXRENDER_D3D11_H_
