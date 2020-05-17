/**
 *	@author		zhuqingquan
 *	@date		2014-10-17
 *	@name		DxRender.h
 *	@brief		Interface of the display engine
 */

#pragma once
#ifndef _ZRENDER_DXRENDER_H_
#define _ZRENDER_DXRENDER_H_

#ifdef _WINDOWS
#include <Windows.h>
#include <D3D11.h>
#include <xnamath.h>
#endif
#include "DxZRenderDLLDefine.h"
#include "DxRenderCommon.h"

namespace zRender
{
#ifdef _WINDOWS
	class DxRender_D3D11;		//�����Windows�±��룬��ʹ��DxRender_D3D11������Ϊ�ײ�ʵ��
	class DisplayElement;
	class YUVTexture_Packed;
#endif

	class BackgroundComponent;
	class IDisplayContentProvider;
	class SharedTexture;
	class SharedResource;
	class IRawFrameTexture;
	class TextureResource;

	/**
	 *	@name		DxRender
	 *	@brief		��ʾ����ĺ���ģ��Ľӿ��࣬�ṩ������ʾ��Դ�Ľӿڣ���ִ����ʾ���Ʋ���
	 *				�����ʵ���ɴ���ʵ���������
	 **/
	class DX_ZRENDER_EXPORT_IMPORT DxRender
	{
	public:
		/**
		 *	@name	DxRender
		 *	@brief	���췽�������󴴽��������init��ʼ����Դ
		 */
		DxRender();

		/**
		 *	@name	~DxRender
		 *	@brief	�����������ͷ����д�������Դ
		 */
		~DxRender();

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
		 *				������������ʱOffscreenRenderTarget
		 *	@param[in]	int width ������
		 *	@param[in]	int height �ߣ�����
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

		int createTextureResource(TextureResource** ppOutTexRes, int width, int height, DXGI_FORMAT dxgiFmt, TEXTURE_USAGE usage, bool bShared, const char* initData = NULL, int dataLen = 0, int pitch = 0);
		
		/**
		 *	@name		createTextureResource
		 *	@brief		����Texture����
		 *				����TextureSourceDesc�е���Ϣ���д�������Ҫʱ��ʼ����
		 *	@param[out]	TextureResource** ppOutTexRes ����ɹ�������TextureResource����
		 *	@param[in]	const TextureSourceDesc& srcDesc Texture����Դ��������Ϣ
		 *	@return		int 0--�ɹ� ����--ʧ��  ����ԭ��ɲο�ConstDefine.h�еĶ���
		 */
		int createTextureResource(const TextureSourceDesc& srcDesc, TextureResource** ppOutTexRes);

		//int openSharedTextureResource(TextureResource** ppOutTexRes, HANDLE hSharedRes);
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
		//YUVTexture_Packed* createTexture(YUVFormat_Packed pixFmt, int width, int height, 
		//					unsigned char* initData = NULL, int initDataLen = 0, bool isShared = false);

		/**
		 *	@name		releaseTexture
		 *	@brief		�ͷ�Texture����
		 *				�ͷ�Texture�����е���Դ����ɾ�����󡣶����ͷŽ�������������ʾ�������³������
		 *	@param[in]	YUVTexture_Packed** texture ָ��Texture����ָ���ָ�룬Texture�����ͷųɹ������ָ�뱻��NULL
		 *	@return		int 0--�ɹ�   <0--ʧ��
		 **/
		//int releaseTexture(YUVTexture_Packed** texture);
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
		 *				���̰߳�ȫ
		 *	@param[in]	IDisplayContentProvider* contentProvider �����Ļ������ݵ��ṩ��
		 *	@param[in]	const RECT_f& displayReg �ñ�������������ϵ�е�λ��
		 *	@return		int 0--�ɹ�   <0--ʧ�ܣ����Ѿ�����ʱ�ڵ�������Ҳ������ʧ��
		 **/
		int setupBackground(IDisplayContentProvider* contentProvider, const RECT_f& displayReg);

		/**
		 *	@name		cancleBackground
		 *	@brief		ȡ������������ʾ
		 *				���̰߳�ȫ
		 *	@return		int 0--�ɹ�   <0--ʧ��
		 **/
		int cancleBackground();

		/**
		 *	@name		drawBackground
		 *	@brief		���Ʊ���
		 *				���̰߳�ȫ
		 *	@return		int 0--�ɹ�   <0--ʧ�ܣ�Ϊ���������������߱����������޷���ʾ
		 **/
		int drawBackground();

		/**
		 *	@name		draw
		 *	@brief		����DisplayElement�б��ֵ���ʾ����
		 *				DxRender������ȷ��ʼ��֮����ܵ��û��ƽӿڻ��Ƹ�����Դ����
		 *	@param[in]	DisplayElement* displayElem ��ʾ���ݶ��󣬸ö����еĶ��㡢Texture�Ƚ��ᱻ����
		 *	@return		int 0--�ɹ�   <0--ʧ��
		 */
		int draw(DisplayElement* displayElem);

		/**
		 *	@name		present
		 *	@brief		���Կ��е���������ʾ�豸�г���
		 *				DxRender������ȷ��ʼ��֮����ܵ��ó��ֽӿ�
		 *	@param[in]	int type	����
		 *	@return		int 0--�ɹ�   <0--ʧ��
		 */
		int present(int type);

		/**
		 *	@name		clear
		 *	@brief		��DxRender��������ʾ�����������ʾ������ɫ
		 *	@param[in]	DWORD color ������ɫ
		 *	@return		int 0--�ɹ�   <0--ʧ��
		 */
		int clear(DWORD color);

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

		void* getDevice() const;
		void* getContext() const;
		int getWidth();
		int getHeight();
		int resize(int new_width, int new_height);
		float getAspectRatio() const;

		const XMFLOAT4X4& getViewTransformMatrix() const;
		const XMFLOAT4X4& getProjectionTransformMatrix() const;

		int createOffscreenRenderTarget(int width, int height);
		void releaseOffscreenRenderTarget();
	private:
		DxRender(const DxRender&);
		DxRender& operator=(const DxRender&);

#ifdef _WINDOWS
		DxRender_D3D11* m_renderImp;
#endif
		BackgroundComponent* m_background;
	};
}

#endif //_zRENDER_DXRENDER_H_