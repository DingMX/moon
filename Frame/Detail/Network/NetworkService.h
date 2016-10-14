/****************************************************************************

Git <https://github.com/sniper00/MoonNetLua>
E-Mail <hanyongtao@live.com>
Copyright (c) 2015-2016 moon
Licensed under the MIT License <http://opensource.org/licenses/MIT>.

****************************************************************************/

#pragma once

#include "asio.hpp"
#include "asio/steady_timer.hpp"
#include "NetworkDefine.h"

namespace moon
{
	DECLARE_SHARED_PTR(Session);
	DECLARE_SHARED_PTR(memory_stream);
	//asio::io_services �ķ�װ �� һ���߳�һ��NetworkService
	class NetworkService
	{
	public:
		NetworkService();
		~NetworkService(void);

		void Run();

		void Stop();

		/**
		* ��ȡasio::io_services
		*
		* @return asio::io_services
		*/
		asio::io_service&	GetIoService();
		/**
		* �����NetworkService��� Session
		*
		* @session 
		*/
		void			AddSession(const SessionPtr& session);

		/**
		* �Ƴ�Session
		*
		* @sessionID Session��Ψһ��ʶ��
		*/
		void			RemoveSession(SessionID sessionID);

		/**
		* ���ó�ʱ���
		*
		* @timeout ��ʱ��� s
		*/
		void			SetTimeout(uint32_t timeout);

		/**
		* ��ĳ��socket���� ��������
		*
		* @socketID
		* @buffer_ptr ����
		*/
		void			Send(SessionID sessionID, const MemoryStreamPtr& msg);

		/**
		* �ر�ĳ��socket����
		*
		* @sessionID 
		* @state ���ùر�״̬
		*/
		void			CloseSession(SessionID sessionID, ESocketState why);

		/**
		* ��ȡserviceID
		*
		*/

		PROPERTY_READWRITE(uint32_t, m_ID, ID)
	private:
		/**
		* ��ʱ���
		*
		*/
		void			TimeoutChecker(const asio::error_code&);

	private:
		asio::io_service																m_IoService;
		asio::io_service::work													m_IoWork;
		asio::steady_timer														m_Checker;
		std::unordered_map<SessionID, SessionPtr>				m_Sessions;
		uint32_t																		m_TimeOut;
		uint32_t																		m_IncreaseSessionID;
	};
}




