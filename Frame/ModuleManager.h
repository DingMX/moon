/****************************************************************************

Git <https://github.com/sniper00/MoonNetLua>
E-Mail <hanyongtao@live.com>
Copyright (c) 2015-2016 moon
Licensed under the MIT License <http://opensource.org/licenses/MIT>.

****************************************************************************/

#pragma once
#include "MacroDefine.h"
#include "Common/noncopyable.hpp"

namespace moon
{
	DECLARE_SHARED_PTR(Worker)
	DECLARE_SHARED_PTR(Module)
	DECLARE_SHARED_PTR(MemoryStream)

	//Module �����࣬����Module�Ĵ��������ȣ��Ƴ�
	class ModuleManager:public noncopyable
	{
	public:
		ModuleManager();
		~ModuleManager();

		/**
		* ��ʼ��
		* @config ��ʼ���ַ��� key-value��ʽ : machine_id:1;worker_num:2;
		*	machine_id Ĭ��ֵ��0�� worker_num���������߳���Ŀ�� Ĭ��ֵ�� 1
		*/
		void			Init(const std::string& config);

		/**
		* Ϊ�˿���� ModuleͨѶ ����MachineID,�������ֲ�ͬmachine,��������255��
		* MachineID �ᱣ���� ModuleID�ĸ�8λ
		*
		* @return ��ʼ��ʱ�����õ�machine_id,���� 0
		*/
		uint8_t		GetMachineID();

		/**
		* ����Module
		*
		* @config ����Module��������ã��ᴫ�ݸ�Module::Init
		*/
		template<typename TModule>
		void			CreateModule(const std::string& config);

		/**
		* ����ID�Ƴ�Module
		*
		* @moduleID 
		*/
		void			RemoveModule(ModuleID moduleID);

		/**
		* ��ĳ��Module������Ϣ
		*
		* @sender ������id
		* @receiver ������id
		* @msg ��Ϣ����
		*/
		void			Send(ModuleID sender, ModuleID receiver,const std::string& data, const std::string& userdata, uint64_t rpcID,uint8_t type);

		void			SendEx(ModuleID sender, ModuleID receiver, const MemoryStreamPtr& data,const std::string& userdata,uint64_t rpcID, uint8_t type);

		/**
		* ������Module�����˷����ߣ��㲥��Ϣ
		*
		* @sender	������id
		* @msg		��Ϣ����
		*/
		void			Broadcast(ModuleID sender, const std::string& data,const std::string& userdata,uint8_t type);

		/**
		* ��������Worker�߳�
		*
		*/
		void			Run();

		/**
		* �ر�����Worker�߳�
		*
		*/
		void			Stop();

	private:
		/**
		* ��ѯ��ȡWorker ID
		*/
		uint8_t		GetNextWorkerID();

		/**
		* ��Module��ӵ� Worker
		* @workerid 
		* @m
		*/
		void			AddModuleToWorker(uint8_t workerid,const ModulePtr& m);

		/**
		* ����Module ID ��ȡ���ڵ� workerID
		* @module id
		*/
		uint8_t		GetWorkerID(ModuleID id);

	private:
		std::atomic<uint8_t>													m_nextWorker;
		std::atomic<uint16_t>													m_IncreaseModuleID;
		
		std::vector<WorkerPtr>												m_Workers;
		uint8_t																			m_MachineID;

		std::mutex																	m_ModuleNamesLock;
		std::vector<std::string>												m_ModuleNames;
	};

	template<typename TModule>
	void ModuleManager::CreateModule(const std::string& config)
	{
		uint16_t	incID = m_IncreaseModuleID.fetch_add(1);
		uint8_t		workerID = GetNextWorkerID();
		uint32_t	moduleID = 0;
		moduleID |= (uint32_t(m_MachineID) << 24);//Module ID �� 32-25 bit����machineID
		moduleID |= (uint32_t(workerID) << 16);//Module ID �� 24-17 bit����workerID
		moduleID |= (incID);

		auto module = std::make_shared<TModule>();
		module->SetID(moduleID);
		module->SetManager(this);

		if(module->Init(config))
		AddModuleToWorker(workerID, module);
	}
};


