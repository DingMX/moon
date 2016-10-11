/****************************************************************************

Git <https://github.com/sniper00/MoonNetLua>
E-Mail <hanyongtao@live.com>
Copyright (c) 2015-2016 moon
Licensed under the MIT License <http://opensource.org/licenses/MIT>.

****************************************************************************/

#include "Worker.h"
#include "Module.h"
#include "ModuleManager.h"
#include "Message.h"
#include "Detail/Log/Log.h"
#include "Common/Time.hpp"

namespace moon
{
	Worker::Worker()
		: m_WorkerID(0),
		_fps(0),
		_msg_counter(0),
		_timer(0)
	{

	}


	Worker::~Worker()
	{

	}


	void Worker::Run()
	{
		Interval(20);
		onUpdate = std::bind(&Worker::Update, this, std::placeholders::_1);
		LoopThread::Run();

		CONSOLE_TRACE("Worker [%d] Run", m_WorkerID);
	}

	void Worker::Stop()
	{
		Post([this]() {
			for (auto& iter : m_Modules)
			{
				iter.second->Destory();
				CONSOLE_TRACE("Module [%s:%u] Destory", iter.second->GetName().c_str(), iter.second->GetID());
			}
			m_Modules.clear();
		});

		AsyncEvent::exit();

		while (GetEventsSize() != 0) 
		{
			thread_sleep(10);
		}

		LoopThread::Stop();

		CONSOLE_TRACE("Worker [%d] Stop", m_WorkerID);
	}

	void Worker::AddModule(const ModulePtr& module)
	{
		Post([this, module]() {
			auto iter = m_Modules.find(module->GetID());
			assert(iter == m_Modules.end());
			CONSOLE_TRACE("Module [%s:%u] Start", module->GetName().c_str(), module->GetID());
			module->Start();
			m_Modules.emplace(module->GetID(), module);
		});
	}

	void Worker::RemoveModule(ModuleID moduleID)
	{
		Post([this, moduleID]() {
			auto iter = m_Modules.find(moduleID);
			assert(iter != m_Modules.end());
			iter->second->Destory();
			CONSOLE_TRACE("Module [%s:%u] Destory", iter->second->GetName().c_str(), iter->second->GetID());
			m_Modules.erase(moduleID);	
		});
	}

	void Worker::DispatchMessage(const MessagePtr& msg)
	{
		Post([this, msg]() {
			auto t = m_Modules.find(msg->GetReceiver());
			if (t != m_Modules.end())
			{
				t->second->PushMessage(msg);
			}
		});
	}

	void Worker::Broadcast(const MessagePtr& msg)
	{
		Post([this, msg]() {
			for (auto& iter : m_Modules)
			{
				if (iter.second->GetID() == msg->GetSender())
					continue;
				iter.second->PushMessage(msg);
			}
		});
	}

	int Worker::GetMessageFps()
	{
		return _fps.load();
	}

	uint8_t Worker::GetID()
	{
		return m_WorkerID;
	}

	void Worker::SetID(uint8_t id)
	{
		m_WorkerID = id;
	}

	//��Ϣ����
	void Worker::Update(uint32_t interval)
	{
		_timer += interval;
		auto t1 = time::millsecond();
		//1.����Ͷ�ݵ��첽�¼�
		UpdateEvents();
		auto t2 = time::millsecond();
		//2.���¸���Modules
		for (auto& Iter : m_Modules)
		{
			if (Iter.second->IsEnableUpdate())
			{
				Iter.second->Update(interval);
			}
			//���Module����Ϣ���г��� ����0����Ѹ�Module���浽��Ϣ�������
			if (Iter.second->GetMQSize() != 0)
			{
				m_HandleQueue.push_back(Iter.second.get());
			}
		}
		auto t3 = time::millsecond();
		//3.ѭ��������Ϣ�������
		while (m_HandleQueue.size() != 0)
		{
			auto module = m_HandleQueue.front();
			m_HandleQueue.pop_front();

			_msg_counter++;
			//�����Module������Ϣδ����������Module�嵽��β
			if (module->PeekMessage())
			{
				m_HandleQueue.push_back(module);
			}
		}
		auto t4 = time::millsecond();

		assert(m_HandleQueue.size() == 0);

		if (_timer > 3000)
		{
			_fps = _msg_counter;
			_msg_counter = 0;
			_timer = 0;

			//CONSOLE_TRACE("Message fps [%d] , event [%lld ms], copy[%lld ms], work[%lld ms]",_fps.load(), t2 - t1, t3 - t2, t4 - t3);
		}
	}
};

