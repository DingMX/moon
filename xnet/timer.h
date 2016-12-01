/****************************************************************************

Git <https://github.com/sniper00/MoonNetLua>
E-Mail <hanyongtao@live.com>
Copyright (c) 2015-2016 moon
Licensed under the MIT License <http://opensource.org/licenses/MIT>.

****************************************************************************/
#pragma once
#include "macro_define.h"

namespace moon
{
	typedef   std::function<void()> timer_handler;

	class timer_context;
	typedef std::shared_ptr<timer_context> timer_context_ptr;

	class XNET_DLL timer
	{
	public:
		//ÿ��ʱ�����Ӵ�С�����255
		static const  uint8_t  WHEEL_SIZE = 255;
		//���� ms
		static const int32_t PRECISION = 10;

		timer();

		~timer();
		/**
		* ���һ��ִֻ��һ�εļ�ʱ��
		*
		* @duration ��ʱ����� ms
		* @callBack  �ص�����
		*  typedef   std::function<void()> timer_handler;
		* ���ؼ�ʱ��ID
		*/
		uint64_t  expired_once(int64_t duration, const timer_handler& callBack);

		/**
		* ����ظ�ִ�еļ�ʱ��
		*
		* @duration ��ʱ����� ms
		* @times �ظ�������(-1 ����ѭ��)
		* @callBack �ص�����
		*  typedef   std::function<void()> timer_handler;
		* ���ؼ�ʱ��ID
		*/
		uint64_t  repeat(int64_t duration, int32_t times, const timer_handler& callBack);

		/**
		* �Ƴ�һ����ʱ��
		*
		* @timerid ��ʱ�� ID
		*/
		void			remove(uint64_t timerid);

		//�߼��߳���Ҫ�������������������ʱ��
		void			update();

		void			stop_all_timer();

		void			start_all_timer();

		static int64_t millseconds();
	private:
		uint64_t 	add_new_timer(const timer_context_ptr& t);
		void			add_timer(const timer_context_ptr& t);
		void			expired(const std::vector<uint64_t>& timers);
		uint64_t	make_key(uint64_t id, uint32_t  slots);
		uint8_t		get_slot(uint64_t  key, int which_queue);
	private:
		struct timer_pool_imp;
		timer_pool_imp* imp_;
	};
}

