#include "msgpack.hpp"
#include "MirrorTypes.h"
struct BigScreenPaneInfo
{
	BigScreenPaneInfo()
	{
		x = -1;
		y = -1;
		pixFormat = SOA::Mirror::PIXFormat::PIXFMT_UNKOWN;
		width = 0;
		height = 0;	
	}
	~BigScreenPaneInfo()
	{
		x = -2;
		y = -2;
		pixFormat = SOA::Mirror::PIXFormat::PIXFMT_UNKOWN;
		width = 0;
		height = 0;
	}
	int x;	//������Screen�е�λ�á�
	int y;	//������Screen�е�λ�á�
	int pixFormat;	//���յ����ݸ�ʽ��
	int width;	//����ķֱ���
	int height;	//����ķֱ���
	MSGPACK_DEFINE(x,y,pixFormat,width,height);
};

struct BigScreenSnapShotParam
{
	BigScreenSnapShotParam()
	{
		snapTime=0;
	}

	bool isValid()
	{
		return snapTime>0;
	}

	BigScreenPaneInfo panelInfo;
	long snapTime;
	MSGPACK_DEFINE(panelInfo,snapTime);
};