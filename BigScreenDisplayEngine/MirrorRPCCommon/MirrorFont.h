
#pragma once
#ifndef _SOA_MIRROR_RPC_BIGFONT_H_
#define _SOA_MIRROR_RPC_BIGFONT_H_

#include "msgpack.hpp"

namespace SOA
{
	namespace Mirror
	{
		namespace RPC
		{
enum FontWeightType
{
	FWT_DONTCARE		 = 0,
	FWT_THIN			 = 100,
	FWT_EXTRALIGHT       = 200,
	FWT_LIGHT            = 300,
	FWT_NORMAL           = 400,
	FWT_MEDIUM           = 500,
	FWT_SEMIBOLD         = 600,
	FWT_BOLD             = 700,
	FWT_EXTRABOLD        = 800,
	FWT_HEAVY            = 900,
};
struct MirrorFont
{
public:
	int width;//�ַ��Ŀ�ȣ�����
	int height;//�ַ��ĸ߶ȣ����ء�
	bool italic;//�Ƿ�б��
	//WeightType weightType;//����������ȡ�
	//FontType fontType;//����
	int fontWeightType;//����������ȡ�
	//FontType fontType;//����
	string pFacename;
	MSGPACK_DEFINE(width,height,italic,fontWeightType,pFacename);
};
		}
	}
}
#endif