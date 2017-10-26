/*
 *	@file		BigScreenLayout.h
 *	@data		4:7:2012   16:28
 *	@author		zhu qing quan	
 *	@brief		BigScreen�Ĳ��֣�������ֱ�ʾ����ĳһ̨������������BigScreen�еĲ��ֱ�ʾ
				�統ǰ�������������BigScreen�е�1��3��5��������BigscreenLayout���������Щ��Ϣ������
 *  @Copyright	(C) 2012, by Ragile Corporation
 */

#pragma once
#ifndef _SOA_MIRROR_RPC_BIGSCREEN_LAYOUT_H_
#define _SOA_MIRROR_RPC_BIGSCREEN_LAYOUT_H_

#include "msgpack.hpp"
#include "MirrorTypes.h"
#include "Size.h"

namespace SOA
{
namespace Mirror
{
namespace RPC
{
	/*
	 * ÿ���������Ϣ
	 */
	struct WindowPane
	{
		WindowPane(float x, float y, int width, int height, PIXFormat format)
			: X(x)
			, Y(y)
			, resolution(width, height)
			, pixelFormat(format)
		{}
		WindowPane()
		{}

		int adapter;
		float X;					//��BigScreen�е����X��
		float Y;					//��BigScreen�е����Y��
		Size resolution;			//����ʾ��ͼ��ķֱ���
		int pixelFormat;	//��ʾ��ͼ������ظ�ʽ
		MSGPACK_DEFINE(adapter,X, Y, resolution, pixelFormat);
	};

	class BigscreenLayout
	{
	public:
		Size m_size;			//����Bigscreen�Ĵ�С��N*M
		std::vector<WindowPane> panes;			//���д�����Ϣ���б�

		BigscreenLayout(int width, int height)
			: m_size(width, height)
		{}
		BigscreenLayout()
		{}

		void addPane(const WindowPane& pane)
		{
			panes.push_back(pane);
		}
		MSGPACK_DEFINE(m_size, panes);
	};
}
}
}

#endif