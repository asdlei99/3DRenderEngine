/*
 *	@file		BigViewSnapshot.h
 *	@data		2013-4-2 11:24
 *	@author		zhu qing quan
 *	@brief		BigViewץͼ���ɵ�ͼƬ����
 *  @Copyright	(C) 2012, by Ragile Corporation
 */

#pragma once
#ifndef _SOA_MIRROR_RPC_BIGVIEW_SNAPSHOT_H_
#define _SOA_MIRROR_RPC_BIGVIEW_SNAPSHOT_H_

#include "msgpack.hpp"

namespace SOA
{
namespace Mirror
{
namespace RPC
{
	/**
	 *	BigViewץͼ���ļ����ͣ�����ֻ֧��BMP��JPEG����
	 *  Ϊ�˱�����ö��֮���ת�������ö�ٵ�ֵ��SOA::Mirror::Decoder::ImageFormatö�ٵ�ֵ����һ��
	 */
	typedef enum BigViewSnaphotFormat
	{
		BVSNPFMT_UNKNOW = 0,		//δ֪
		BVSNPFMT_BMP = 1,			//BMP
		BVSNPFMT_JPEG = 3,			//JPEG
	};

	/**
	 * @name	BigViewSnapshot
	 * @brief	bigview��ͼͼƬ����
	 */
	struct BigViewSnapshot
	{
		msgpack::type::raw_ref data;		///< ����
		unsigned long length;				///< ����
		int format;							///< ���� BigViewSnaphotFormat

		BigViewSnapshot()
			: length(0)
			, format(BVSNPFMT_UNKNOW)
			, DataFreeFunc(NULL)
		{

		}

		~BigViewSnapshot()
		{
			if(DataFreeFunc!=NULL)
				DataFreeFunc((char*)data.ptr);
		}

		void (*DataFreeFunc)(void* pData);		///< �ͷ����ݵĺ���ָ��

		MSGPACK_DEFINE(format, length, data);
	};
}
}
}

#endif // _SOA_MIRROR_RPC_BIGVIEW_SNAPSHOT_H_