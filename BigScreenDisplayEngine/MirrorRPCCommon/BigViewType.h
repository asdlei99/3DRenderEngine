/*
 *	@file		BigViewType.h
 *	@data		12:6:2012   15:40
 *	@author		zhu qing quan	
 *	@brief		BigView���͵�ö��	
 *  @Copyright	(C) 2012, by Ragile Corporation
 */

#pragma once

#ifndef _BIG_VIEW_TYPE_
#define _BIG_VIEW_TYPE_

namespace SOA
{
namespace Mirror
{
namespace RPC
{
	enum BigViewType
	{
		ImageOnly = 1,	//ֻ��ͼƬ,�������ڴ��У�����OSD����ͼ����Կ�ʱ�Ͽ�
		OwnerDraw,		//�����������Ļ滭,�������Դ��У�����OSD��ͨ��Texture������ͼ����Կ�ʱ��ImageOnly��һЩ
	};
}
}
}

#endif