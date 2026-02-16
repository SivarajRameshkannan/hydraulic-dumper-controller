/*
 * can_manager.hpp
 *
 *  Created on: 13-Feb-2026
 *      Author: Sivaraj
 */

#ifndef HCU_SERVICES_CAN_MANAGER_HPP_
#define HCU_SERVICES_CAN_MANAGER_HPP_

#include "can_manager.hpp"
#include "hal_can.hpp"
#include "ds_ring_buffer.hpp"
#include <array>
#include <cstdint>
#include <atomic>

template<uint8_t queue_size, uint8_t frame_size>
class CAN_Manager
{
	public:
		enum class CM_Status : uint8_t
		{
			TX_BUFFER_FULL = 0U,
			RX_BUFFER_EMPTY,
			OK,
			COUNT			
		};
		
		using frame_type = std::array<uint8_t, frame_size>;
		
	    CAN_Manager(hal_CAN& CAN) 
	        : CAN(CAN), _tx_done(false), _rx_done(false)
	    {}
	
	    void init(void) const
	    {
			CAN.init();
		}
	
	    void process(void)
	    {
			if(new_data_received())
			{
				recv_data();
			}
			
			transmit_data();
		}

		CM_Status read_msg(frame_type& data)
		{
		    if (!rx_queue.dequeue(data))
		    {
		        return CM_Status::RX_BUFFER_EMPTY;
		    }
		
		    return CM_Status::OK;
		}

		CM_Status transmit_msg(const frame_type& data)
		{
		    if (!tx_queue.enqueue(data))
		    {
		        return CM_Status::TX_BUFFER_FULL;
		    }
		
		    return CM_Status::OK;
		}


	    bool transmit_completed(void)
	    {
	        if (_tx_done)
	        {
	            _tx_done = false;
	            return true;
	        }
	        return false;
	    }
	
	    static void transmit_cplt_cb(void* ctx)
	    {
	        auto* self = static_cast<CAN_Manager<queue_size, frame_size>*>(ctx);
	        self->_tx_done = true;
	    }
	
	    static void recv_cplt_cb(void* ctx)
	    {
	        auto* self = static_cast<CAN_Manager<queue_size, frame_size>*>(ctx);
	        self->_rx_done = true;
	    }
	
	private:	
	    hal_CAN& CAN;
	
	    std::atomic<bool> _tx_done;
	    std::atomic<bool> _rx_done;
		    
	    RingBuffer<frame_type, queue_size> tx_queue;
	    RingBuffer<frame_type, queue_size> rx_queue;
	
	    bool new_data_received(void)
	    {
	        if (_rx_done)
	        {
	            _rx_done = false;
	            return true;
	        }
	        return false;
	    }

	    void transmit_data(void)
	    {
	        frame_type frame;
	
	        if (!tx_queue.dequeue(frame))
	            return;
	
	        CAN.send(frame.data(), frame_size);
	    }
	
	    void recv_data(void)
	    {
	        frame_type frame;
		
	        CAN.recv(frame.data(), frame_size);
	
	        if (!rx_queue.enqueue(frame))
	        {
	            // handle overflow
	        }
	    }
};


#endif /* MANAGED_COMPONENTS_HCU_SERVICES_CAN_MANAGER_HPP_ */
