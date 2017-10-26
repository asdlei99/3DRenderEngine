#pragma once
#ifndef BSF_DATATYPE
#define BSF_DATATYPE
#include "MirrorTypes.h"
//#include "MemoryPool.h"
//#include <boost/pool/object_pool.hpp>
//#include "BSFDLLDefine.h"
//#include "SnapshotBuffer.h"

typedef unsigned __int64 ULONGLONG;
typedef unsigned char byte;

//#define		BSF_OPACITY_ROTATION

namespace SOA{
	namespace Mirror{
		namespace Render{

struct RectCoordinate
{
	float left;
	float top;
	float right;
	float bottom;
	float getWidth()
	{
		return right - left;
	}
	float getHeight()
	{
		return bottom - top;
	}

	RectCoordinate(float fLeft, float fRight, float fTop, float fBottom)
		: left(fLeft), right(fRight), top(fTop), bottom(fBottom)
	{

	}

	RectCoordinate()
		: left(0), right(0), top(0), bottom(0)
	{

	}
	/*
	 * �ж�һ�������Ƿ���ȷ����������Գ��ָ�����
	 */
	static int justRectParam(const RectCoordinate &rect)
	{
		if(rect.left >= rect.right ||
			rect.top >= rect.bottom)
		{
			return -1;
		}
		return 0;
	}

	/*
	 * �ж�һ�������Ƿ���ȷ�����Ҵ�����Ϊһ���������򣬲�����ָ�����
	 */
	static int justRectParamByPositive(const RectCoordinate &rect)
	{
		if(rect.left < 0 || rect.top < 0)
			return -1;
		if(rect.left >= rect.right ||
		rect.bottom <= rect.top)
		{
			return -2;
		}
		return 0;
	}

	/*
	 * �ж�һ�������Ƿ���ȷ�������ǹ�һ���������
	 */
	static int justRectParamByNormalized(const RectCoordinate &rect)
	{
		if( rect.left < 0 || rect.top < 0)
		{
			return -1;
		}
		if( 1 < rect.right || 1 < rect.bottom)
		{
			return -2;
		}
		if(rect.left >= rect.right ||
		rect.bottom <= rect.top)
		{
			return -3;
		}
		return 0;
	}
};

struct PaneInfo
{
	PaneInfo()
		: x(-1)
		, y(-1)
		, width(0)
		, height(0)
		, pixFormat(PIXFormat::PIXFMT_UNKOWN)
	{
	}
	PaneInfo(int xPosition, int yPosition, int nWidth, int nHeight, PIXFormat pf)
		: x(xPosition)
		, y(yPosition)
		, width(nWidth)
		, height(nHeight)
		, pixFormat(pf)
	{
	}
	~PaneInfo()
	{
		x = -2;
		y = -2;
		pixFormat = PIXFormat::PIXFMT_UNKOWN;
		width = 0;
		height = 0;
	}
	int x;	//������Screen�е�λ�á�
	int y;	//������Screen�е�λ�á�
	PIXFormat pixFormat;	//���յ����ݸ�ʽ��
	int width;	//����ķֱ���
	int height;	//����ķֱ���
};
//
//struct BSF_DLL_EXPORT_IMPORT SnapShotParam
//{
//private:
//	SnapShotParam()
//		: pucData(NULL)
//		, iDataLen(0)
//	{
//	}
//public:
//	~SnapShotParam()
//	{
//	}
//
//	static SnapShotParam* CreateSnapshotParam(int xPosition, int yPosition, int nWidth, int nHeight, PIXFormat pf);
//	
//	static void FreeSnapshotParam(SnapShotParam* sp, bool isNeedFreeData);
//	
//	PaneInfo	paneInfo;
//	ULONGLONG	time;//ץͼʱ����ϵͳ��ʱ�䡣���롣
//	unsigned char *pucData;//���յ�����
//	int			iDataLen;
//
//	SOA::Mirror::RPC::SnapshotBuffer snpbuffer;
//};

struct Size
{
	Size()
		: width(0)
		, height(0)
	{

	}

	Size(unsigned int w, unsigned int h)
		: width(w)
		, height(h)
	{

	}

	bool isIllegal()
	{
		return width==0xFFFFFFFF || height==0xFFFFFFFF;
	}

	unsigned int width;
	unsigned int height;
};
		}
	}
}

#endif