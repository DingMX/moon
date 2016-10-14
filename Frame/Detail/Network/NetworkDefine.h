/****************************************************************************

Git <https://github.com/sniper00/MoonNetLua>
E-Mail <hanyongtao@live.com>
Copyright (c) 2015-2016 moon
Licensed under the MIT License <http://opensource.org/licenses/MIT>.

****************************************************************************/

#pragma once
#include "MacroDefine.h"
#include "ObjectCreateHelper.h"
#include "Common/MemoryStream.hpp"

namespace moon
{
	enum  class ESocketState
	{
		Ok,											//ok
		GetRemoteEndPointFailed,		//��ȡԶ�����Ӷ˿���Ϣʧ��
		Timeout,									//��ʱ
		ClientClose,								//�ͻ����˳�
		IllegalDataLength,					//�Ƿ����ݳ���
		ForceClose								//ǿ�ƹر�
	};

	enum class ESocketMessageType
	{
		Connect,
		Close,
		RecvData
	};

	DECLARE_SHARED_PTR(MemoryStream)

	using NetMessageDelegate = std::function<void(ESocketMessageType, SessionID, const MemoryStreamPtr&)>;

	typedef uint16_t msg_size_t;
	//�����Ϣ����
#define MAX_MSG_SIZE msg_size_t(-1)
}

