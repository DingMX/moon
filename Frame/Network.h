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
		void Start();

		void Update(uint32_t interval);

		void Destory();

	public:
		/**
		* ������Ϣ����ص�
		*/
		std::function<void(Message*)>		OnNetMessage;
	private:
		struct  NetworkImp;
		std::shared_ptr<NetworkImp>		m_NetworkImp;
	};
}



