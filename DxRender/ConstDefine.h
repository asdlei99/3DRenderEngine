#ifndef _DXRENDER_CONST_DEFINE_H_
#define _DXRENDER_CONST_DEFINE_H_
#pragma once

// ����ΪDxRender�з������÷���ֵ�����������
#define DXRENDER_RESULT_OK						0		//OK���ɹ�
#define DXRENDER_RESULT_FAILED					-20001	// ����ʧ��
#define DXRENDER_RESULT_NOT_INIT_YET			-20002	//δ��ʼ��
#define DXRENDER_RESULT_OPT_NOT_SUPPORT			-20003	//������֧��
#define DXRENDER_RESULT_FUNC_REENTRY_INVALID    -20004	//���õķ�����֧�����룬���粻��������������Lock����������Lock��Unlock
#define DXRENDER_RESULT_PARAM_INVALID			-20005  //�������Ϸ�
#define DXRENDER_RESULT_INTERNAL_ERR			-20006  //�ڲ�����
#endif //_DXRENDER_CONST_DEFINE_H_
