/****************************************************************************

Git <https://github.com/sniper00/MoonNetLua>
E-Mail <hanyongtao@live.com>
Copyright (c) 2015-2016 moon
Licensed under the MIT License <http://opensource.org/licenses/MIT>.

****************************************************************************/

#pragma once
#include "MacroDefine.h"
#include "Common/MemoryStream.hpp"

namespace moon
{
	//Module��Ϣ����
	enum class EMessageType :uint8_t
	{
		Unknown,
		NetworkData,//��������
		NetworkConnect,//����������Ϣ
		NetworkClose,//����Ͽ���Ϣ
		ModuleData,//Module����
		ModuleRPC,//Զ�̵�����Ϣ
		ToClient//���͸��ͻ��˵�����
	};

	DECLARE_SHARED_PTR(MemoryStream)

	//Module ��Ϣ
	class Message
	{
	public:
		using StreamType = MemoryStream;

		Message(size_t capacity = 64, size_t headreserved = 0);

		Message(const MemoryStreamPtr&);

		Message(const Message& msg) = default;

		Message(Message&& msg) = default;

		~Message();

		void									SetSender(ModuleID moduleID);
		ModuleID							GetSender() const;

		void									SetReceiver(ModuleID moduleID);
		ModuleID							GetReceiver() const;

		void									SetUserData(const std::string& userdata);
		const std::string&			GetUserData() const;

		void									SetRPCID(uint64_t rpcID);
		uint64_t							GetRPCID() const;

		/**
		* ������Ϣ���ͣ��μ� EMessageType
		*/
		void									SetType(EMessageType type);
		EMessageType					GetType() const;

	
		const uint8_t*					Data() const
		{
			return m_Data->Data();
		}

		std::string							Bytes() const
		{
			return std::string((char*)Data(), Size());
		}

		void									WriteData(const std::string& v)
		{
			m_Data->WriteBack(v.data(),0, v.size());
		}

		size_t								Size() const
		{
			return m_Data->Size();
		}

	protected:
		void									Init();
	protected:
		uint8_t								m_Flag;
		uint8_t								m_Type;
		ModuleID							m_Sender;
		ModuleID							m_Receiver;
		uint64_t							m_UserID;
		uint64_t							m_SubUserID;
		uint64_t							m_RPCID;
		std::string							m_UserData;
		MemoryStreamPtr			m_Data;
	};
};


