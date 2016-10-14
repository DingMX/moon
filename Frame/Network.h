#pragma once
#include "MacroDefine.h"

namespace moon
{
	class Message;

	class Network
	{
	public:
		Network();

		~Network();

		/**
		* ��ʼ������
		*
		* @threadNum �����߳���
		*/
		void				InitNet(int threadNum);

		/**
		* ��������ĵ�ַ
		*
		* @ip
		* @port
		*/
		bool				Listen(const std::string& ip, const std::string& port);

		/**
		* �첽���ӷ������������Ӷ����
		*
		* @ip
		* @port
		*/
		void				Connect(const std::string& ip, const std::string& port);

		/**
		* ͬ�����ӷ�����
		*
		* @ip
		* @port
		* @return ����������id
		*/
		SessionID		SyncConnect(const std::string& ip, const std::string& port);

		/**
		* ��ĳ�����ӷ�����Ϣ
		*
		* @sessionID
		*/
		void				Send(SessionID sessionID,const std::string& data);

		/**
		* ǿ�ƹر�һ����������
		*
		* @sessionID
		*/
		void				Close(SessionID sessionID);

		/**
		* ����Session�ĳ�ʱ���
		* @timeout ��ʱʱ�� ����λ s
		*/
		void				SetTimeout(uint32_t timeout);

		/**
		* ������Ϣ����ص�
		*/
		void				SetHandler(const std::function<void(uint32_t, const std::string&, uint8_t)>&);
	public:
		void				Start();

		void				Update(uint32_t interval);

		void				Destory();
	private:
		struct  NetworkImp;
		std::shared_ptr<NetworkImp>											m_NetworkImp;
	};
}



