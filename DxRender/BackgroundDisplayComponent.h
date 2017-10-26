/**
 *	@author		zhuqingquan
 *	@date		2014-10-17
 *	@name		BackgroundDisplayComponent.h
 *	@brief		Interface of the display engine
 */

#pragma once
#ifndef _ZRENDER_BACKGROUND_DISPLAY_COMPONENT_H_
#define _ZRENDER_BACKGROUND_DISPLAY_COMPONENT_H_

//#include "DxZRenderDLLDefine.h"

namespace zRender
{
	class DisplayElement;
	class IDisplayContentProvider;

	/**
	 *	@name		BackgroundComponent
	 *	@brief		���汳�����ݵ�ģ�飬������ʾ������������Ҫ�������Ϣ
	 **/
	class BackgroundComponent
	{
	public:
		/**
		 *	@name		BackgroundComponent
		 *	@brief		���캯��������ʾ����������ϢΪ�������죬��ʾ���潫ʹ����Щ��Ϣ������Ⱦ
		 *	@param[in]	IDisplayContentProvider* contentProvider �������ݵ��ṩ��
		 *	@param[in]	DisplayElement* de ��Ⱦ��������Ҫ����Ϣ
		 **/
		BackgroundComponent(IDisplayContentProvider* contentProvider, DisplayElement* de)
		: m_ctPro(contentProvider), m_de(de)
		{}

		/**
		 *	@name	~BackgroundComponent
		 *	@brief	��������
		 **/
		~BackgroundComponent() { m_ctPro=0; m_de=0; }

		/**
		 *	@name		getContentProvider
		 *	@brief		��ȡ�������ݵ��ṩ��
		 *	@return		IDisplayContentProvider* �������ݵ��ṩ��
		 **/
		IDisplayContentProvider* getContentProvider() const { return m_ctPro; }

		/**
		 *	@name		getDisplayElement
		 *	@brief		��ȡ��Ⱦ��������Ҫ����Ϣ
		 *	@return		DisplayElement* ��Ⱦ��������Ҫ����Ϣ
		 **/
		DisplayElement* getDisplayElement() const { return m_de; }

	private:
		IDisplayContentProvider* m_ctPro;
		DisplayElement* m_de;
	};
}

#endif //_zRENDER_BACKGROUND_DISPLAY_COMPONENT_H_