/**
 *	@author		zhuqingquan
 *	@date		2014-10-17
 *	@name		RenderDrawing.h
 *	@brief		the display module of a monitor
 */

#include <Windows.h>
#include <list>

#pragma once
#ifndef _SOA_RENDER_RENDERDRAWING_H_
#define _SOA_RENDER_RENDERDRAWING_H_

#include "BigScreenBackground.h"
#include "ElemDsplModel.h"

namespace zRender
{
	class DisplayElement;
	class DxRender;
	class BasicEffect;
}

namespace SOA
{
namespace Mirror
{
namespace Render
{
	class BigViewportPartition;

	/**
	 *	@name		RenderDrawing
	 *	@brief		BigScreen��һ��������������ʾ���ݵ���Ⱦ���������
	 **/
	class RenderDrawing
	{
	public:
		/**
		 *	@name		RenderDrawing
		 *	@brief		���췽����������BigScreen��һ�������Ӧ����ʾģ�飬��ģ����ʾ��������λ�ڸô������ڵ�BigViewport������
		 *	@param[in]	HWND attatchWnd �����ж�Ӧ�Ĵ��ڵľ��
		 *	@param[in]	float ltPointX ����������BigScreen�е����꣬���϶����X���ֵ
		 *	@param[in]	float ltPointY ����������BigScreen�е����꣬���϶����Y���ֵ
		 *	@param[in]	float rbPointX ����������BigScreen�е����꣬���¶����X���ֵ
		 *	@param[in]	float rbPointY ����������BigScreen�е����꣬���¶����Y���ֵ
		 **/
		RenderDrawing(HWND attatchWnd, float ltPointX, float ltPointY, float rbPointX, float rbPointY, BigScreenBackground* background);

		/**
		 *	@name		~RenderDrawing
		 *	@brief		���췽������Ⱦ�߳̽���ֹͣ����������Ⱦ���õ���Դ�����ͷ�
		 **/
		~RenderDrawing();

		/**
		 *	@name		start
		 *	@brief		������Ⱦ�̣߳���Ⱦ����Ҫ����Դ������Ⱦ�߳��д�������ԴҲֻ������Ⱦ��ʹ�����ͷ�
		 *	@return		int 0--�����ɹ�	<0--����ʧ��
		 **/
		int start(HANDLE timerHandle);

		/**
		 *	@name		stop
		 *	@brief		ֹͣ��Ⱦ�̣߳���Ⱦ�߳��д�������Դ�����ͷ�
		 *	@return		��
		 **/
		void stop();

		/**
		 *	@name		doRenderWork
		 *	@brief		��Ⱦ�̵߳�ʵ��ִ�еĴ��룬�ⲿ�û����ܵ��øú���
		 **/
		int doRenderWork();

		/**
		 *	@name		addBigViewportPartition
		 *	@brief		����зֺ��BigViewport�Ĳ�����ʾ���ݣ��ö�������Ⱦ��������ӵ�BigViewport����ʾ����
		 *				BigViewportPartition��DisplayElement�������󣬴Ӷ��ⲿ����ͨ��BigViewportPartition�Ľӿ��޸���ʾ������
		 *				��Ⱦ�̸߳����ͷ���ӵ�BigViewportPartition�����ڸö�������Ҫ��ʾʱ
		 *	@param[in]	BigViewportPartition* viewportPartition �зֺ��BigViewport�Ĳ�����ʾ����
		 *	@return		int	0--��ӳɹ�  <0--���ʧ��
		 **/
		int addBigViewportPartition(BigViewportPartition* viewportPartition);

		/**
		 *	@name		getRegOfBigScreen
		 *	@brief		��ȡ�ö�����ʾ��Ⱦ��������BigScreen�е�λ��
		 *	@param[out]	float& leftX ����������BigScreen�е����꣬���϶����X���ֵ
		 *	@param[out]	float& rightX ����������BigScreen�е����꣬���϶����Y���ֵ
		 *	@param[out]	float& topY ����������BigScreen�е����꣬���¶����X���ֵ
		 *	@param[out]	float& bottomY ����������BigScreen�е����꣬���¶����Y���ֵ
		 *	@return		int 0--�ɹ�  <0--ʧ��
		 **/
		int getRegOfBigScreen(float& leftX, float& rightX, float& topY, float& bottomY)
		{
			leftX = m_ltPointX;
			rightX = m_rbPointX;
			topY = m_ltPointY;
			bottomY = m_rbPointY;
			return 0;
		}

		/**
		 *	@name		getWidthInPixel
		 *	@brief		��ȡ�ö�����ʾ��Ⱦ��������ؿ��
		 *	@return		int >0--�ɹ� <=0--ʧ��
		 **/
		int getWidthInPixel() const;

		/**
		 *	@name		getHeightInPixel
		 *	@brief		��ȡ�ö�����ʾ��Ⱦ��������ظ߶�
		 *	@return		int >0--�ɹ� <=0--ʧ��
		 **/
		int getHeightInPixel() const;
		//int get

		zRender::DxRender* getDxRender() const { return m_render; }
	private:
		void addViewportPartition(BigViewportPartition* vpPartition);
		//void removeViewportPartition(BigViewportPartition* vpPartition);
		zRender::DisplayElement* createDisplayElement(BigViewportPartition* vpPartition);
		void drawBigViewportPartition(zRender::DxRender* render, BigViewportPartition* vpPartition);

		HWND m_hwnd;
		zRender::DxRender* m_render;
		HANDLE m_timerHandle;

		bool m_isRunning ;
		HANDLE m_thread;
		float m_ltPointX;
		float m_ltPointY;
		float m_rbPointX;
		float m_rbPointY;

		BigScreenBackground* m_background;

		std::list<BigViewportPartition*> m_vpPartitions;
	};
}
}
}

#endif //_SOA_RENDER_RENDERDRAWING_H_