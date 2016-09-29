#pragma once
#include "MacroDefine.h"

namespace moon
{
	class Message;

	class NetworkComponent
	{
	public:
		NetworkComponent();

		~NetworkComponent();

		/**
		* ��ʼ������
		*
		* @thread_num �����߳���
		*/
		void InitNet(int threadNum);

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

		void				SendNetMessage(SessionID sessionID, Message* msg);

		/**
		* ǿ�ƹر�һ����������
		*
		* @sessionID
		*/
		void	Close(SessionID sessionID);

	public:
		void OnEnter();

		void Update(uint32_t interval);

		void OnExit();

	public:
		/**
		* ������Ϣ����ص�
		*/
		std::function<void(Message*)> OnNetMessage;
	private:
		struct  NetworkComponentImp;
		std::shared_ptr<NetworkComponentImp>		m_NetworkComponentImp;
	};
}



