/*
 *	@file		Process.h
 *	@data		2013-3-12 9:31
 *	@author		zhu qing quan
 *	@brief		���̲����ķ�װ��
 *  @Copyright	(C) 2012, by Ragile Corporation
 */

#pragma once
#ifndef _SOA_MIRROR_PROCESS_H_
#define _SOA_MIRROR_PROCESS_H_

namespace SOA
{
namespace Mirror
{
	/**
	 * @name	Process
	 * @brief	������ز����ķ�װ
	 */
	class Process
	{
	public:
		Process();
		/**
		 * Method		Process
		 * @brief		���캯��
		 *				���processExeName�������Ӧ�Ľ����Ѿ���ִ�У����ȡ�����ý��̵ľ����������start�ǾͲ�������һ���µĽ���
		 *				�����Ӧ�Ľ��̲����ڣ�����Process()һ��
		 * @param[in]	const char * processExeName ���̿�ִ���ļ������ƣ����ɼ�·��
		 *				�磺"sample.exe" 
		 */
		Process(const char* processExeName);
		~Process();

		/**
		 * Method		start
		 * @brief		��������
		 * @param[in]	const char * name ���̿�ִ���ļ�������
		 *				�磺"c:\\sample.exe"
		 *					".\\sample.exe"
		 *					"sample.exe"
		 * @return		bool
		 */
		bool start(const char* name);

		/**
		 * Method		close
		 * @brief		ͨ������̵������ڷ��͹ر���Ϣ���ر�ӵ���û�����Ľ��̡��ͷ���˽��̹�����������Դ��
		 * @return		bool
		 */
		bool close();

		/**
		 * Method		kill
		 * @brief		����ֹͣ����
		 * @return		void
		 */
		void kill();

		/**
		 * Method		isProcessRunning
		 * @brief		�����Ƿ�������
		 * @return		bool true--����  false--����ֹ
		 */
		bool isProcessRunning();
	private:
		void* m_startUpInfo;
		void* m_processInfo;

		void InitProcessInfoFromSystemExecutingProcess(const char* processExeName);
	};
}
}

#endif // _SOA_MIRROR_PROCESS_H_