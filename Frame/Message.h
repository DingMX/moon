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
		NetTypeEnd,
		ModuleData,//Module����
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

		/**
		* ��ȡ��Ϣ�ķ�����ID��һ����ϢҪô��Module֮��ͨѶ����Ϣ��Ҫô��������Ϣ
		* �ο� GetSessionID
		*/
		ModuleID						GetSender() const;
		void									SetSender(ModuleID moduleID);

		/**
		* ��Ϣ��socketID
		*/
		bool									HasSessionID() const;
		SessionID							GetSessionID() const;
		void									SetSessionID(SessionID sessionID);

		/**
		* ������Ϣ�Ľ�����ID
		*/
		void									SetReceiver(ModuleID moduleID);
		ModuleID						GetReceiver() const;

		/**
		* 
		*/
		bool									HasAccountID() const;
		void									SetAccountID(uint64_t accountID);
		uint64_t							GetAccountID() const;

		/**
		*
		*/
		bool									HasPlayerID() const;
		void									SetPlayerID(uint64_t playerID);
		uint64_t							GetPlayerID() const;

		/**
		*
		*/
		bool									HasSenderRPC() const;
		void									SetSenderRPC(uint64_t senderRPC);
		uint64_t							GetSenderRPC() const;

		/**
		*
		*/
		bool									HasReceiverRPC() const;
		void									SetReceiverRPC(uint64_t receiverRPC);
		uint64_t							GetReceiverRPC() const;

		/**
		* ������Ϣ���ͣ��μ� EMessageType
		*/
		void									SetType(EMessageType type);

		/**
		* ��ȡ��Ϣ���ͣ��μ� EMessageType
		*/
		EMessageType					GetType() const;

		const uint8_t*					Data() const
		{
			return m_Data->Data();
		}

		size_t								Size() const
		{
			return m_Data->Size();
		}

		MemoryStream&			ToStream() const
		{
			return *m_Data;
		}

		MemoryStreamPtr			ToStreamPointer() const
		{
			return m_Data;
		}
	protected:
		bool CheckFlag(uint8_t pos) const;

		void SetFlag(uint8_t pos);

		void ClearFlag(uint8_t pos);

	protected:
		uint8_t																			m_Flag;
		uint8_t																			m_Type;
		mutable ModuleID														m_Sender;
		mutable ModuleID														m_Receiver;
		mutable uint64_t														    m_AccountID;
		mutable uint64_t														    m_PlayerID;
		mutable uint64_t															m_SenderRPCID;
		mutable uint64_t															m_ReceiverRPCID;
		MemoryStreamPtr														m_Data;
	};
};


