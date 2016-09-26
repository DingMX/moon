/****************************************************************************

Git <https://github.com/sniper00/MoonNetLua>
E-Mail <hanyongtao@live.com>
Copyright (c) 2015-2016 moon
Licensed under the MIT License <http://opensource.org/licenses/MIT>.

****************************************************************************/

#pragma once
#include <unordered_map>
#include <memory>
#include <vector>

#include "TimerWheel.hpp"
#include "TimerContext.hpp"

namespace moon
{
	class TimerPool
	{	
	public:
		//ÿ��ʱ�����Ӵ�С�����255
		static const  uint8_t  wheel_size = 255;
		//���� ms
		static const int32_t PRECISION = 15;

		TimerPool();

		~TimerPool();
		/**
		* ���һ��ִֻ��һ�εļ�ʱ��
		*
		* @duration ��ʱ����� ms
		* @callBack  �ص�����
		*  typedef   std::function<void()> timer_handler;
		* ���ؼ�ʱ��ID
		*/
		uint32_t  expiredOnce(int64_t duration,const timer_handler& callBack);

		uint32_t  expiredOnce(int64_t duration,timer_handler&& callBack);

		/**
		* ����ظ�ִ�еļ�ʱ��
		*
		* @duration ��ʱ����� ms
		* @times �ظ�������(-1 ����ѭ��)
		* @callBack �ص�����
		*  typedef   std::function<void()> timer_handler;
		* ���ؼ�ʱ��ID
		*/
		uint32_t  repeat(int64_t duration, int32_t times, timer_handler&& callBack);

		uint32_t  repeat(int64_t duration, int32_t times, const timer_handler& callBack);

		/**
		* �Ƴ�һ����ʱ��
		*
		* @timerid ��ʱ�� ID
		*/
		void remove(uint32_t timerid);
		
		//�߼��߳���Ҫ�������������������ʱ��
		void update();

		void stopAllTimer();

		void startAllTimer();

		static int64_t millseconds();
	private:
		uint32_t 	addNewTimer(const timer_context_ptr& t);
		void		addTimer(const timer_context_ptr& t);
		void		expired(const std::vector<uint64_t>& timers);
		uint64_t	makeKey(uint32_t id, uint32_t  slots);
		uint8_t		getSlot(uint64_t  key, int which_queue);	
	private:
		std::vector < TimerWheel<std::vector<uint64_t>, wheel_size>> m_wheels;
		std::unordered_map<uint32_t, timer_context_ptr>		m_timers;
		std::vector<timer_context_ptr>										m_new;
		int64_t																				m_tick;
		uint32_t																			m_inc;
		bool																					m_Stop;
	};
}

