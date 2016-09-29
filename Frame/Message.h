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
	enum class EMessageType:uint8_t
	{
		Unknown,
		NetworkData,//��������
		NetworkConnect,//����������Ϣ
		NetworkClose,//����Ͽ���Ϣ
		ModuleData,//Module����
		ModuleRPC,//
		ToClient//���͸��ͻ��˵�����
	};

	enum class EHeaderFlag:uint8_t
	{
		HasSessionID = 1 << 0,
		HasPlayerID = 1 << 1,
		HasRPCID = 1 << 2,
		ReadOnly = 1<<3
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

		/**
		* ��ȡ��Ϣ�ķ�����ID��һ����ϢҪô��Module֮��ͨѶ����Ϣ��Ҫô��������Ϣ
		* �ο� GetSessionID
		*/
		
		void									SetSender(ModuleID moduleID);
		ModuleID							GetSender() const;

		void									SetSessionID(SessionID id);
		bool									IsSessionID() const;
		SessionID							GetSessionID() const;
		/**
		* ������Ϣ�Ľ�����ID
		*/
		void									SetReceiver(ModuleID moduleID);
		ModuleID							GetReceiver() const;

		void									SetAccountID(uint64_t accountID);
		uint64_t							GetAccountID() const;

		/**
		*
		*/
		bool									IsPlayerID() const;
		void									SetPlayerID(uint64_t playerID);
		uint64_t							GetPlayerID() const;

		/**
		*
		*/
		bool									HasRPCID() const;
		void									SetRPCID(uint64_t rpcID);
		uint64_t							GetRPCID() const;

		bool									IsReadOnly() const;
		void									SetReadOnly();

		/**
		* ������Ϣ���ͣ��μ� EMessageType
		*/
		void									SetType(EMessageType type);
		EMessageType					GetType() const;

	
		const uint8_t*					Data() const
		{
			return m_Data->Data();
		}

		size_t								Size() const
		{
			return m_Data->Size();
		}

		MemoryStream&				ToStream() const
		{
			return *m_Data;
		}

		MemoryStreamPtr			ToStreamPointer() const
		{
			return m_Data;
		}

		Message*							Clone();

	protected:
		void									Init();

		bool									CheckFlag(EHeaderFlag) const;

		void									SetFlag(EHeaderFlag);

		void									ClearFlag(EHeaderFlag);
	protected:
		uint8_t								m_Flag;
		uint8_t								m_Type;
		ModuleID							m_Sender;
		ModuleID							m_Receiver;
		uint64_t							m_UserID;
		uint64_t							m_RpcID;
		MemoryStreamPtr			m_Data;
	};
};


