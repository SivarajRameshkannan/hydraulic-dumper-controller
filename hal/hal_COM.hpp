/*
 * hal_COM.hpp
 *
 *  Created on: 21-Feb-2026
 *      Author: Sivaraj
 */

#ifndef HCU_HAL_HAL_COM_HPP_
#define HCU_HAL_HAL_COM_HPP_

class hal_COM
{
	public:
		hal_COM(void) : curr_e(EVENTS::NONE) {};
		~hal_COM(void) = default;
		
		using Callback = void (*)(void* ctx);

		enum class COM_status : uint8_t
		{
			OK = 0,
			FAILURE,
			MAX_STATUS
		};
		
		enum class EVENTS : uint8_t
		{
			HALF_TX_DONE = 0U,
			FULL_TX_DONE,
			HALF_RX_DONE,
			FULL_RX_DONE,
			NONE,
			COUNT
		}; 
		
		void register_com_callback(Callback cb, void* ctx, EVENTS e)
		{
			_cb[static_cast<size_t>(e)] = cb;
			_ctx[static_cast<size_t>(e)] = ctx;
		}
		
		virtual void process(void)
		{
			size_t e = static_cast<size_t>(curr_e);
			
			if(_cb[e])
			{
				_cb[e](_ctx[e]);
			}
		}
		
		virtual void init(void) const = 0;
		virtual COM_status send(uint8_t*, size_t size) const = 0;
		virtual COM_status recv(uint8_t*, size_t size) const = 0;
    private:
    	EVENTS curr_e;
    	Callback _cb[static_cast<size_t>(EVENTS::COUNT)]{nullptr};
    	void* _ctx[static_cast<size_t>(EVENTS::COUNT)]{nullptr}; 
};

#endif /* MANAGED_COMPONENTS_HCU_HAL_HAL_COM_HPP_ */
