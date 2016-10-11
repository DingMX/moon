/****************************************************************************

Git <https://github.com/sniper00/MoonNetLua>
E-Mail <hanyongtao@live.com>
Copyright (c) 2015-2016 moon
Licensed under the MIT License <http://opensource.org/licenses/MIT>.

****************************************************************************/

#pragma once
#include "MacroDefine.h"
#include "Common/LoopThread.hpp"
#include "Common/AsyncEvent.hpp"
#include "Common/noncopyable.hpp"

namespace moon
{
	class Message;

	DECLARE_SHARED_PTR(Module)
	DECLARE_SHARED_PTR(Message)
	//�����߳�
	class Worker:public LoopThread,public AsyncEvent, noncopyable
	{
	public:
		Worker();

		~Worker();

		/**
		* ���������߳�
		*
		*/
		void Run();

		/**
		* ֹͣ�����߳�
		*
		*/
		void Stop();

		/**
		* �����߳����Module
		*
		*/
		void AddModule(const ModulePtr& m);

		/**
		* �Ƴ�Module
		*
		*/
		void RemoveModule(ModuleID id);

		/**
		* ��Ϣ�ַ�
		*/
		void DispatchMessage(const MessagePtr& msg);

		/**
		* ���Worker�е�����Module�㲥��Ϣ
		*/
		void Broadcast(const MessagePtr& msg);

		int	GetMessageFps();

		uint8_t		GetID();

		void			SetID(uint8_t id);
	private:
		void			Update(uint32_t interval);
	private:
		uint8_t																			m_WorkerID;
		std::unordered_map<ModuleID, ModulePtr>				m_Modules;
		//ģ�鴦�����
		std::deque<Module*>													m_HandleQueue;

		std::atomic<int>															_fps;
		uint32_t																		_msg_counter;
		uint32_t																		_timer;
	};
};


