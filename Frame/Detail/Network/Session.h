/****************************************************************************

Git <https://github.com/sniper00/MoonNetLua>
E-Mail <hanyongtao@live.com>
Copyright (c) 2015-2016 moon
Licensed under the MIT License <http://opensource.org/licenses/MIT>.

****************************************************************************/

#pragma once
#include "asio.hpp"
#include "NetworkDefine.h"


namespace moon
{
	DECLARE_SHARED_PTR(Session);

	constexpr int32_t			IO_BUFFER_SIZE = 8192;

	//asio::socket �ķ�װ
	class NetworkService;
	class Session :public std::enable_shared_from_this<Session>,private asio::noncopyable
	{	
	public:

		Session(NetMessageDelegate& netDelegate,NetworkService& serv);

		~Session(void);

		/**
		* ���ӳɹ�����ô˺�����������һЩ��ʼ������
		*
		* @return ,if return true will add to NetworkService else will close
		*/
		bool											Start();

		/**
		* ǿ�ƹرո�socket����
		*
		* @state ����һ���ر�״̬
		*/
		void											Close(ESocketState state);

		/**
		* ���socket���ӷ�������
		*
		*/
		void											Send(const MemoryStreamPtr& data);

		/**
		* ��ȡasio::ip::tcp::socket
		*
		*/
		asio::ip::tcp::socket&				GetSocket() { return m_Socket; };

		/**
		* ��ȡ������Ϣ
		*
		*/
		std::string									GetErrorMessage() { return m_ErrorCode.message(); }

		/**
		* �������������ӵ�״̬
		*
		*/
		bool											IsOk();
	private:
		/**
		* Ͷ���첽������
		*
		*/
		void											PostRead();

		/**
		* Ͷ���첽д����
		*
		*/
		void											PostSend();

		/**
		* ��ȡ��ɻص�
		*
		*/
		void											HandleRead(const asio::error_code& e, std::size_t bytes_transferred);

		/**
		* д��ɻص�
		*
		*/
		void											HandleSend(const asio::error_code& e, std::size_t bytes_transferred);
	
		/**
		* ˢ�������յ������ݵ�ʱ��
		*
		*/
		void											RefreshLastRecevieTime();

		/**
		* ���ӳɹ�,���͹ر���Ϣ��ģ��
		*
		*/
		void											OnConnect();

		/**
		* ���յ���Ϣ,���͹ر���Ϣ��ģ��
		*
		*/
		void											OnMessage(const uint8_t* data,size_t len);

		/**
		* ���ӽ�Ҫ�ر�,���͹ر���Ϣ��ģ��
		*
		*/
		void											OnClose();

		/**
		* ����Զ�̵ĵ�ַ
		*
		*/
		void											ParseRemoteEndPoint();


		ESocketState							GetState() { return m_State; }
	public:
		//SessionID high 8 bit is NetworkService id.
		PROPERTY_READWRITE(SessionID, m_ID, ID)
		PROPERTY_READONLY(int64_t, m_LastRecevieTime, LastRecevieTime)
		PROPERTY_READONLY(std::string, m_RemoteIP, RemoteIP)
		PROPERTY_READONLY(uint16_t, m_RemotePort, RemotePort)
	private:
		//��Ϣ����������
		NetMessageDelegate&			m_Delegate;

		NetworkService&						m_Service;

		asio::ip::tcp::socket					m_Socket;
		//�첽���ջ�����
		uint8_t										m_RecvBuffer[IO_BUFFER_SIZE];
		//������Ϣ������
		MemoryStream						m_RecvMemoryStream;
		//���ͻ�����
		MemoryStream						m_SendMemoryStream;
		//������Ϣ���Ͷ���
		std::deque<MemoryStreamPtr>	m_SendQueue;
		//�Ƿ����ڷ���
		bool											m_IsSending;
		//�������
		asio::error_code						m_ErrorCode;

		ESocketState							 m_State;
	};
};





