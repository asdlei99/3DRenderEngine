/*
 *	@file		BigScreenSnapshotData.h
 *	@data		2013-8-6 17:31
 *	@author		zhu qing quan
 *	@brief		BigScreenʵʱץͼ��ȡ������
 *  @Copyright	(C) 2013, by Ragile Corporation
 */

#pragma once
#ifndef _SOA_MIRROR_RPC_BIGSCREEN_SNAPSHOT_DATA_H_
#define _SOA_MIRROR_RPC_BIGSCREEN_SNAPSHOT_DATA_H_

#include "msgpack.hpp"
#include <vector>

namespace SOA
{
namespace Mirror
{
namespace RPC
{
	/**
	 * @name	DataBuffer
	 * @brief	�����ڴ��
	 */
	struct DataBuffer
	{
		DataBuffer(const char* dataptr, int datalen, int fmt)
			: buffer(dataptr, datalen)
			, length(datalen)
			, format(fmt)
		{

		}

		msgpack::type::raw_ref buffer;		///< ����
		unsigned long length;				///< ����
		int format;							///< ���� �����ǲ�ͬ��ö��ֵ
	};

	/**
	 * @name	BigScreenSnapshotData
	 * @brief	BigScreen�ĵ�������ץͼ����
	 */
	struct BigScreenSnapshotData
	{
		BigScreenSnapshotData(const char* dataptr, int dataLen, int fmt, int xOfBigScreen, int yOfBigScreen)
			: data(dataptr, dataLen, fmt)
			, XOfBigScreen(xOfBigScreen)
			, YOfBigScreen(yOfBigScreen)
		{

		}
		BigScreenSnapshotData()
			: data(NULL, 0, 0)
			, XOfBigScreen(0)
			, YOfBigScreen(0)
		{

		}

		BigScreenSnapshotData(const BigScreenSnapshotData& robj)
			: data(robj.data.buffer.ptr, robj.data.buffer.size, robj.data.format)
			, XOfBigScreen(robj.XOfBigScreen)
			, YOfBigScreen(robj.YOfBigScreen)
		{

		}
		int XOfBigScreen;
		int YOfBigScreen;
		DataBuffer data;
		long long id;

		MSGPACK_DEFINE(XOfBigScreen, YOfBigScreen, data.buffer, data.length, data.format, id);
	};

	/**
	 * @name	BigScreenSnapshotDataCollection
	 * @brief	BigScreen�������ݵļ���
	 */
	struct BigScreenSnapshotDataCollection
	{
		std::vector<BigScreenSnapshotData> snapshotDatas;

		MSGPACK_DEFINE(snapshotDatas);
	};

	/**
	 * @name	BigScreenGetSnapshotCommand
	 * @brief	��ȡ���յ���������
	 */
 	struct BigScreenGetSnapshotCommand
 	{
 		BigScreenGetSnapshotCommand(const char* cmd)
 			: command(cmd)
 		{
 
 		}

		BigScreenGetSnapshotCommand()
			: command()
		{

		}

 		std::string command; 
 
 		bool operator==(const BigScreenGetSnapshotCommand& othCommand) const
 		{
 			return this->command==othCommand.command;
 		}
 		MSGPACK_DEFINE(command);
 	};
 
	/**
	 * @name	BigScreenGetSnapshotCommand_isSnapshotValid 
	 * @brief	�鿴�����Ƿ��ȡ�ɹ�����������
	 */
 	struct BigScreenGetSnapshotCommand_isSnapshotValid : public BigScreenGetSnapshotCommand
 	{
 		BigScreenGetSnapshotCommand_isSnapshotValid()
 			: BigScreenGetSnapshotCommand("isSnapshotValid")
 		{
 
 		}
	};
 
	/**
	 * @name	BigScreenGetSnapshotCommand_getSnapshotData
	 * @brief	��ȡ���յ���������
	 */
	struct BigScreenGetSnapshotCommand_getSnapshotData : public BigScreenGetSnapshotCommand
	{
		BigScreenGetSnapshotCommand_getSnapshotData()
			: BigScreenGetSnapshotCommand("getSnapshotData")
		{

		}
	};
}
}
}

#endif // _SOA_MIRROR_RPC_BIGSCREEN_SNAPSHOT_DATA_H_