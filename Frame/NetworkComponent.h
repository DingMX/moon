#pragma once
#include "MacroDefine.h"

namespace moon
{
	DECLARE_SHARED_PTR(Message)

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
		void InitNet(int netThreadNum);

		/**
		* ��������ĵ�ַ
		*
		* @ip
		* @port
		*/
		bool	Listen(const std::string& ip, const std::string& port);

		/**
		* �첽���ӷ������������Ӷ����
		*
		* @ip
		* @port
		*/
		void	Connect(const std::string& ip, const std::string& port);

		SessionID SyncConnect(const std::string& ip, const std::string& port);

		void SendNetMessage(SessionID sessionID, const MessagePtr& msg);

		/**
		* ǿ�ƹر�һ����������
		*
		* @sessionID
		*/
		void	Close(SessionID sessionID);

		/**
		* ������Ϣ����ص�
		*
		*/
		std::function<void(const MessagePtr&)> OnNetMessage;

	//protected:
		void OnEnter();

		void Update(uint32_t interval);

		void OnExit();
	private:
		struct  NetworkComponentImp;
		std::shared_ptr<NetworkComponentImp>		m_NetworkComponentImp;
	};
}



