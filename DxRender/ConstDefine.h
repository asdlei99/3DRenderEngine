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
#define DXRENDER_RESULT_SUBCOMPONENT_INIT_FAILED -20007 //��ģ���ʼ��ʧ��
#define DXRENDER_RESULT_ERROR_IN_MODEL			-20008	//ElemDsplModelδ���û���״̬����ȷ
#define DXRENDER_RESULT_EFFECT_INVALID			-20009	//Effect������
#define DXRENDER_RESULT_METADATA_INVALID		-200010 //DisplayElement������MetaData������
#define DXRENDER_RESULT_CREATE_BUF_FAILED		-200011 //����Buffer��Դʧ��
#endif //_DXRENDER_CONST_DEFINE_H_
