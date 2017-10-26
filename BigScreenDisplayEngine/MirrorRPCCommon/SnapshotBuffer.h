/*
 *	@file		SnapshotBuffer.h
 *	@data		2013-1-11 9:43
 *	@author		zhu qing quan
 *	@brief		Snapshot���ݿ顣�ڴ˵�ʵ���У����ݿ�ʹ��Windows�Ĺ����ڴ�ʵ�֡�
 *  @Copyright	(C) 2012, by Ragile Corporation
 */

#pragma once
#ifndef _SNAPSHOT_BUFFER_H_
#define _SNAPSHOT_BUFFER_H_

#include "MirrorTypes.h"
#include <Windows.h>

namespace SOA
{
namespace Mirror
{
namespace RPC
{
	struct SnapshotBuffer
	{
		size_t size;
		char   addr[64];
		void*  handle;

		ULONGLONG timestamp;
		int x;	//������Screen�е�λ�á�
		int y;	//������Screen�е�λ�á�
		SOA::Mirror::PIXFormat pixFormat;	//���յ����ݸ�ʽ��
		int width;	//����ķֱ���
		int height;	//����ķֱ���

		char* lockData();
		void unlockData();

	private:
		void* openHandle;
		void* pData;
	};

	void SetSnapshotBufferInit(SnapshotBuffer* buffer, size_t size, void* handle, const char* name);

	bool InitSnapshotBuffer(SnapshotBuffer* buffer, const char* shareMemoryName, size_t size, const char* data = NULL);

	void ReleaseSnapshotBuffer(SnapshotBuffer* buffer);
}
}
}

#endif // _SNAPSHOT_BUFFER_H_