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
		 *	@param[in]	const wchar_t* effectFileName ��ʾ�����Shader�ļ���effect�ļ���·������
		 *				���������·�����߾���·��
		 *	@param[in]	isEnable4XMSAA �Ƿ�֧��MSAA��Ĭ��Ϊfalse
		 *				����ò���Ϊtrue����isSDICompatible����Ϊtrue
		 *	@param[in]	isSDICompatible �Ƿ�֧�ֻ�ȡHDC�������GDI��Ⱦ
		 *				����ò���Ϊfalse����lockBackbufferHDC�ӿڵ���ʧ��
		 *				����ò���Ϊtrue����isEnable4XMSAA����Ϊtrue
		 *	@return		int 0--�ɹ�  ��0--ʧ��
		 */
		int init(HWND hWnd, const wchar_t* effectFileName, bool isEnable4XMSAA = false, bool isSDICompatible = false);

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
		DisplayElement* createDisplayElement(const RECT_f& displayReg, int zIndex);
		
		/**
		 *	@name		releaseDisplayElement
		 *	@brief		�ͷ�DisplayElement����
		 *				�ͷ�DisplayElement�����е���Դ����ɾ������
		 *	@param[in]	DisplayElement** displayElement ָ��DisplayElement����ָ���ָ�룬DisplayElement�����ͷųɹ������ָ�뱻��NULL
		 *	@return		int 0--�ɹ�   <0--ʧ��
		 */
		int releaseDisplayElement(DisplayElement** displayElement);

		IRawFrameTexture * createTexture(PIXFormat pixfmt, int width, int height, TEXTURE_USAGE usage, bool bShared, unsigned char * initData, int dataLen, int pitch);

		IRawFrameTexture* openSharedTexture(IRawFrameTexture* sharedTexture);

		void releaseTexture(IRawFrameTexture** rawFrameTexture);

		int createSharedTexture(SharedTexture** ppSharedTex, PIXFormat pixfmt);

		int releaseSharedTexture(SharedTexture** ppSharedTex);

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
		int getSnapshot(SharedTexture** outSharedTexture);
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

		int getWidth();
		int getHeight();
		int resize(int new_width, int new_height);

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