#pragma once
#ifndef _Z_RENDER_RECT_DRAWING_CONTEXT_H_
#define _Z_RENDER_RECT_DRAWING_CONTEXT_H_

#include "ElementDrawingContext.h"

namespace zRender
{
	/**
	 * @name	RectDrawingContext
	 * @brief	The drawing context use to draw Rect
	 **/
	class RectDrawingContext : public ElementDrawingContext
	{
	public:
		RectDrawingContext(int width, int height);

		virtual int apply(DxRender* render, ITextureResource* textures[], int textureCount,
			ID3D11Buffer* vtBuf, ID3D11Buffer* indexBuffer, ElementMetaData* metadata);


		/**
		 *	@name		setDisplayRegion
		 *	@brief		���ø���ʾ��������ʾ��������ϵ�е�λ��
		 *				�û���ͨ���������ø�λ�ôﵽ�ƶ���ʾ���ݵ�����
		 *	@param[in]	const RECT_f& displayReg	��ʾ��ʾ����ĵ�����ϵλ��
		 *	@param[in]	float zIndex ��ǰ��ʾԭʼ���ڶ����Z����ƫ��
		 *	@return		int 0--�ɹ� <0--ʧ��	�ò������Ϸ�ʱʧ��
		 **/
		virtual int setDisplayRegion(const RECT_f& displayReg, float zIndex);//�����ƶ����������ݵ���ʾλ��

		/**
		 *	@name		setZIndex
		 *	@brief		���ø���ʾ��������ʾ��������ϵ�е�λ�õ�Z����
		 *				�û���ͨ���������ø�λ�ôﵽ�ƶ���ʾ����Z���������
		 *	@param[in]	float zIndex ��ǰ��ʾԭʼ���ڶ����Z����ƫ��
		 *	@return		int 0--�ɹ� <0--ʧ��	�ò������Ϸ�ʱʧ��
		**/
		virtual int setZIndex(float zIndex);

		virtual float getZIndex() const;

		/**
		 *	@name		setDsplModel
		 *	@brief		����ʹ�õ�Display Model
		 *	@param[in]	ElemDsplModel<BasicEffect> * dsplModel ElemDsplModel����
		 *	@return		void
		 **/
		virtual void setDsplModel(ElemDsplModel<BasicEffect>* dsplModel) { m_dsplModel = dsplModel; }

		virtual void enableTransparent(bool enable) { m_isEnableTransparent = enable; }
		virtual bool isEnableTransparent() const { return m_isEnableTransparent; }

		/**
		 *	@name			setAlpha
		 *	@brief			������ʾ����͸���ȣ���Ч��Χ��1.0f -- 0.0f��
		 *	@param[in]		float alpha ͸���ȣ�1.0fΪ��͸���� 0.0fΪȫ͸��
		 **/
		virtual void setAlpha(float alpha);
		/**
		 *	@name			getAlpha
		 *	@brief			��ȡ��ǰ���õ�͸����
		 *	@return			float
		 **/
		virtual float getAlpha() const;
	private:

		XMFLOAT4X4			m_WorldTransformMat;
		XMFLOAT4X4			m_worldBaseTransform;
		XMFLOAT4X4			m_viewTransform;
		XMFLOAT4X4			m_projTransform;
		ElemDsplModel<BasicEffect>* m_dsplModel;
		float m_aspectRatio;
		float				m_alpha;
		bool				m_isEnableTransparent;
	};
}

#endif //_Z_RENDER_RECT_DRAWING_CONTEXT_H_