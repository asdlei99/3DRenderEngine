/**
 *	@author		zhuqingquan
 *	@date		2015-1-10
 *	@name		VideoContentProvider.h
 *	@brief		��ʾ���ݵ��ṩ�ߵ�ʵ����֮һ���̳�IDisplayContentProvider�ӿ�
 *				����ֻ������һ֡ͼ�����ݵĽ�����������ݣ����в�����ԭʼ���ݡ��������ֻ��ʹ��ͼ�����ݵ�һ������������ʾ�������Ǿ������򣬲�֧��������״
 **/

#pragma once
#ifndef _ZRENDER_VIDEO_CP_H_
#define _ZRENDER_VIDEO_CP_H_

#include "IDisplayContentProvider.h"

namespace zRender
{
	class DX_ZRENDER_EXPORT_IMPORT VideoContentProvider : public IDisplayContentProvider
	{
	public:
		VideoContentProvider(TextureDataSource* dataSrc);

		~VideoContentProvider();

		bool isVertexUpdated(int identify) const { return m_vertexIdentify>identify; }

		int getVertexs(VertexVector** vv, int& vvCount, int& identify);

		virtual int setRotation(int rotate);
		virtual int setRotation_x(int rotate);
		virtual int setRotation_y(int rotate);

		TextureDataSource* getTextureDataSource() { return m_dataSrc; }
		void* getShader();

		void increaseAuthorization();

		void decreaseAuthorization();
	private:
		TextureDataSource* m_dataSrc;
		int m_vertexIdentify;
		VertexVector* m_vv;
		int m_vvCount;

		int m_rotate;
		int m_rotateX;
		int m_rotateY;
	};

}

#endif //_ZRENDER_FRAME_DATA_REF_CP_H_