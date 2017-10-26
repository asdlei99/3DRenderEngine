/*
 *	@file		Size.h
 *	@data		12:6:2012   15:23
 *	@author		zhu qing quan	
 *	@brief		�洢��һ����������ԣ���ʾ���еĿ�Ⱥ͸߶�	
 *  @Copyright	(C) 2012, by Ragile Corporation
 */

#ifndef _SOA_MIRROR_RPC_SIZE_
#define _SOA_MIRROR_RPC_SIZE_

#include "msgpack.hpp"
//#include "MirrorRPCClientDLLDefine.h"

namespace SOA
{
namespace Mirror
{
namespace RPC
{
	class  Size
	{
	public:
		Size()
			: m_width(0)
			, m_height(0)
		{
		}
		Size(int width, int height)
			: m_width(width)
			, m_height(height)
		{
		};
		Size(const Size& robj)
		{
			this->m_height = robj.m_height;
			this->m_width = robj.m_width;
		};
		Size operator=(const Size& robj)
		{
			this->m_height = robj.m_height;
			this->m_width = robj.m_width;
			return *this;
		};
		~Size()
		{

		};

		bool isIlligal() const
		{
			return m_width<0 || m_height<0;
		}
		MSGPACK_DEFINE(m_width, m_height);
	public:
		int m_width;
		int m_height;
	};
}
}
}

#endif