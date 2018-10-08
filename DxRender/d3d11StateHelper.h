/**
 *	@file		d3d11StateHelper.h
 *	@brief		ʵ�ֽ�ID3D11DeviceContext�еĹ���״̬��state of dx pipeline)���浽�����л��ߴӶ����лָ�
 *	@author		zhuqingquan
 **/
#pragma once
#ifndef _D3D11_STATE_HELPER_H_
#define _D3D11_STATE_HELPER_H_

#include "D3D11.h"
#include <inttypes.h>

#define MAX_RENDER_TARGETS             D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT
#define MAX_SO_TARGETS                 4
#define MAX_CLASS_INSTS                256

namespace zRender
{
	struct d3d11_state {
		ID3D11GeometryShader           *geom_shader;
		ID3D11InputLayout              *vertex_layout;
		D3D11_PRIMITIVE_TOPOLOGY       topology;
		ID3D11Buffer                   *vertex_buffer;
		UINT                           vb_stride;
		UINT                           vb_offset;
		ID3D11BlendState               *blend_state;
		float                          blend_factor[4];
		UINT                           sample_mask;
		ID3D11DepthStencilState        *zstencil_state;
		UINT                           zstencil_ref;
		ID3D11RenderTargetView         *render_targets[MAX_RENDER_TARGETS];
		ID3D11DepthStencilView         *zstencil_view;
		ID3D11SamplerState             *sampler_state;
		ID3D11PixelShader              *pixel_shader;
		ID3D11ShaderResourceView       *resource;
		ID3D11RasterizerState          *raster_state;
		UINT                           num_viewports;
		D3D11_VIEWPORT                 *viewports;
		ID3D11Buffer                   *stream_output_targets[MAX_SO_TARGETS];
		ID3D11VertexShader             *vertex_shader;
		ID3D11ClassInstance            *gs_class_instances[MAX_CLASS_INSTS];
		ID3D11ClassInstance            *ps_class_instances[MAX_CLASS_INSTS];
		ID3D11ClassInstance            *vs_class_instances[MAX_CLASS_INSTS];
		UINT                           gs_class_inst_count;
		UINT                           ps_class_inst_count;
		UINT                           vs_class_inst_count;
	};

	/**
	 * @name		d3d11_save_state
	 * @brief		����ID3D11DeviceContext�е�ǰ�Ĺ���״̬
	 *				��Ҫ��d3d11_restore_state�ɶԵ���
	 * @param[out]	struct d3d11_state *state ���ڱ����ȡ�������еĹ���״̬
	 * @param[in]	ID3D11DeviceContext* d3d11Context ��Ҫ�����ID3D11DeviceContext
	 * @return		true--�ɹ� false--ʧ��
	 **/
	bool d3d11_save_state(struct d3d11_state *state, ID3D11DeviceContext* d3d11Context);

	/**
	* @name			d3d11_restore_state
	* @brief		������Ĺ���״̬�ָ���ID3D11DeviceContext��
	*				��Ҫ��d3d11_save_state�ɶԵ���
	* @param[in]	struct d3d11_state *state �����Ż�ȡ�������еĹ���״̬
	* @param[in]	ID3D11DeviceContext* d3d11Context ��Ҫ�ָ�״̬��ID3D11DeviceContext
	* @return		true--�ɹ� false--ʧ��
	**/
	bool d3d11_restore_state(struct d3d11_state *state, ID3D11DeviceContext* d3d11Context);
}

#endif //_D3D11_STATE_HELPER_H_
