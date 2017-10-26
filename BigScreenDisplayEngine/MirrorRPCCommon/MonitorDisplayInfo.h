/*
 *	@file		MonitorDisplay.h
 *	@data		2013-6-21 14:28
 *	@author		zhu qing quan
 *	@brief		��ȡ������ʾ������Ϣ�Լ����ӵ�һЩ��֮��صĲ���
 *  @Copyright	(C) 2013, by Ragile Corporation
 */

#pragma once
#ifndef _SOA_MIRROR_COMMON_MONITORDISPLAY_H_
#define _SOA_MIRROR_COMMON_MONITORDISPLAY_H_

#include <Windows.h>

namespace SOA
{
namespace Mirror
{
namespace Common
{
	struct MonitorDisplayInfo
	{
		LONGLONG id;				//��ʾ��ID
		RECT rect;				//��ʾ������������ϵͳ���������е�λ��
		HMONITOR handle;			//���ڲ�����ʾ���ľ��
		int refreshRate;			//��ʾ����ˢ����

		MonitorDisplayInfo()
			: id(0)
			, handle(NULL)
			, refreshRate(0)
		{

		}
	};

	struct MonitorDisplayInfoList
	{
		int count;					//����
		char* pBuf;					//MonitorDisplayInfo������׵�ַ

		MonitorDisplayInfoList ()
		:count(0),pBuf(NULL)
		{};
	};

	/**
	 * Method		getAllMonitorDispalyInfo
	 * @brief		��ȡ��ǰ���п��õ���ʾ����Ϣ
	 * @param[in]	MonitorDisplayInfoList & infoList ���п�����ʾ������Ϣ
	 *				���øú���ʱ�û���ʼ��infoList���磺
	 *				MonitorDispalyInfoList infoList;
	 *				infoList.count = 100; //��ʾ����������������ֵ
	 *				infoList.pBuf = (char*)malloc(100*sizeof(MonitorDisplayInfo));
	 *				�������óɹ������޸�infoList.count��ֵΪʵ����Ч����ʾ������Ϣ
	 *				infoList.pBufָ����ʾ����Ϣ��������׵�ַ
	 *				�û������ͷ�infoList.pBufָ����ڴ�
	 * @return		int 0--�ɹ�  <0--ʧ��
	 */
	int getAllMonitorDispalyInfo(MonitorDisplayInfoList& infoList);

	/**
	 * Method		compareMonitorDisplayInfoList
	 * @brief		�Ƚ�����MonitorDisplayInfoList�������Ƿ���ͬ
	 * @param[in]	const MonitorDisplayInfoList & left �Ⱥ����
	 * @param[in]	const MonitorDisplayInfoList & right �Ⱥ��ұ�
	 * @return		int 0--��ͬ  ����ֵ--��ͬ
	 */
	int compareMonitorDisplayInfoList(const MonitorDisplayInfoList& left, const MonitorDisplayInfoList& right);

	/**
	 * Method		extendDestopToMonitorDispaly
	 * @brief		��ϵͳ������չ�����е���ʾ����
	 * @return		int 0--�ɹ�  <0--ʧ��
	 */
	int extendDestopToMonitorDispaly();
}
}
}

#endif // _SOA_MIRROR_COMMON_MONITORDISPLAY_H_