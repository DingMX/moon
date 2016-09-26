/****************************************************************************

Git <https://github.com/sniper00/MoonNetLua>
E-Mail <hanyongtao@live.com>
Copyright (c) 2015-2016 moon
Licensed under the MIT License <http://opensource.org/licenses/MIT>.

****************************************************************************/
#pragma once
#include "NetworkDefine.h"

namespace moon
{
	/**
	* NetWorkFrame ʵ�������������ӿڡ� NetWorkFrame �������Ƿ��̰߳�ȫ�ġ�
	*/
	class NetWorkFrame
	{
	public:

		/**
		* NetWorkFrame ���캯��
		* @handler �����¼��ص���connect, recevie, close)
		* @net_thread_num �����߳�����
		* ע�⣺��������˶�������̣߳���ôhandler �ص������Ƿ��̰߳�ȫ�ġ�
		*/
		NetWorkFrame(const NetMessageDelegate& handler, uint8_t threadNum = 1);
		~NetWorkFrame();

		/**
		* ����ĳ���˿�
		* @listenAddress ip��ַ��������
		* @listenPort �˿�
		*/
		void							Listen(const std::string& ip, const std::string& port);

		/**
		* �첽����ĳ���˿�
		* @ip ip��ַ��������
		* @port �˿�
		*/
		void							AsyncConnect(const std::string& ip, const std::string& port);

		/**
		* ͬ������ĳ���˿�
		* @ip ip��ַ��������
		* @port �˿�
		* @return �������ӵ� socketID, �ɹ� socketID.value != 0, ʧ��socketID.value = 0
		*/
		SessionID			SyncConnect(const std::string& ip, const std::string& port);

		/**
		* ��ĳ�����ӷ�������, ����������̰߳�ȫ��
		* @sessionID ���ӱ�ʶ
		* @data ����
		*/
		void							Send(SessionID sessionID, const MemoryStreamPtr& msg);

		/**
		* �ر�һ������
		* @sessionID ���ӱ�ʶ
		* @state ����������һ��״̬������Ϊʲô�رգ����� ��ʱ�����ͷǷ����ݣ�
		*/
		void							CloseSession(SessionID sessionID, ESocketState state);

		/**
		* ��������� ��������������̣߳������������߳�
		*/
		void							Run();

		/**
		* ֹͣ�����
		*/
		void							Stop();

		/**
		* ��ȡ������
		*/
		int							GetErrorCode();

		/**
		* ��ȡ������Ϣ
		*/
		std::string					GetErrorMessage();

		/**
		* ���ù������ӵĳ�ʱ���
		* @timeout ��ʱʱ�� ����λ ms
		* @checkInterval ��ʱ���������λ ms
		*/
		void							SetTimeout(uint32_t timeout, uint32_t checkInterval);
	protected:
		/**
		* Ͷ���첽accept,������������
		*/
		void							PostAccept();

		/**
		* ��ʱ����̺߳���
		*/
		void							CheckTimeOut(uint32_t interval);
	protected:
		struct Imp;
		std::shared_ptr<Imp>  m_Imp;
		NetMessageDelegate   m_Delegate;
	};
};
