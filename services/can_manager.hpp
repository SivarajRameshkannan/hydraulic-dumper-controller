/*
 * can_manager.hpp
 *
 *  Created on: 13-Feb-2026
 *      Author: Sivaraj
 */

#ifndef HCU_SERVICES_CAN_MANAGER_HPP_
#define HCU_SERVICES_CAN_MANAGER_HPP_

#include "can_manager.hpp"
#include "hal_COM.hpp"
#include "hal_can.hpp"
#include "ds_ring_buffer.hpp"
#include <array>
#include <cstdint>
#include <atomic>

enum class CM_Status : uint8_t
{
	TX_BUFFER_FULL = 0U,
	RX_BUFFER_EMPTY,
	OK,
	COUNT			
};

template<uint8_t queue_size, uint8_t frame_size>
class CAN_Manager
{
	public:
		using frame_type = std::array<uint8_t, frame_size>;
		
	    CAN_Manager(hal_CAN& CAN) 
	        : CAN(CAN) {}
	
	    void init(void) const;
	    void process(void);
		CM_Status read_msg(frame_type& data);
		CM_Status transmit_msg(const frame_type& data);
	
	private:	
	    hal_CAN& CAN;
		hal_CAN::EVENTS curr_event;
		    
	    RingBuffer<frame_type, queue_size> tx_queue;
	    RingBuffer<frame_type, queue_size> rx_queue;
	
	    void transmit_data(void);		    
	    void recv_data(void);

	    static void transmit_cplt_cb(void* ctx);
	    static void recv_cplt_cb(void* ctx);
	    static void transmit_half_cplt_cb(void* ctx);
	    static void recv_half_cplt_cb(void* ctx);
};

template<uint8_t queue_size, uint8_t frame_size>
void CAN_Manager<queue_size, frame_size>::init(void) const
{
	CAN.init();
	CAN.register_com_callback(transmit_cplt_cb, (void *) this, hal_CAN::EVENTS::FULL_TX_DONE);
	CAN.register_com_callback(recv_cplt_cb, (void *) this, hal_CAN::EVENTS::FULL_RX_DONE);
	CAN.register_com_callback(transmit_half_cplt_cb, (void *) this, hal_CAN::EVENTS::HALF_TX_DONE);
	CAN.register_com_callback(recv_half_cplt_cb, (void *) this, hal_CAN::EVENTS::FULL_RX_DONE);
}

template<uint8_t queue_size, uint8_t frame_size>
void CAN_Manager<queue_size, frame_size>::process(void)
{
#if 0
	if(new_data_received())
	{
		recv_data();
	}
#endif

	transmit_data();
	CAN.process();
}

template<uint8_t queue_size, uint8_t frame_size>
CM_Status CAN_Manager<queue_size, frame_size>::read_msg(frame_type& data)
{
    if (!rx_queue.dequeue(data))
    {
        return CM_Status::RX_BUFFER_EMPTY;
    }

    return CM_Status::OK;
}

template<uint8_t queue_size, uint8_t frame_size>
CM_Status CAN_Manager<queue_size, frame_size>::transmit_msg(const frame_type& data)
{
    if (!tx_queue.enqueue(data))
    {
        return CM_Status::TX_BUFFER_FULL;
    }

    return CM_Status::OK;
}

template<uint8_t queue_size, uint8_t frame_size>
void CAN_Manager<queue_size, frame_size>::transmit_data(void)
{
    frame_type frame;

    if (!tx_queue.dequeue(frame))
        return;

    CAN.send(frame.data(), frame_size);
}

template<uint8_t queue_size, uint8_t frame_size>
void CAN_Manager<queue_size, frame_size>::recv_data(void)
{
    frame_type frame;

    CAN.recv(frame.data(), frame_size);

    if (!rx_queue.enqueue(frame))
    {
        // handle overflow
    }
}

template<uint8_t queue_size, uint8_t frame_size>
void CAN_Manager<queue_size, frame_size>::transmit_cplt_cb(void* ctx)
{
    auto* self = static_cast<CAN_Manager<queue_size, frame_size>*>(ctx);
    //self->_tx_done = true;
}

template<uint8_t queue_size, uint8_t frame_size>
void CAN_Manager<queue_size, frame_size>::recv_cplt_cb(void* ctx)
{
    auto* self = static_cast<CAN_Manager<queue_size, frame_size>*>(ctx);
    //self->_rx_done = true;
}

template<uint8_t queue_size, uint8_t frame_size>
void CAN_Manager<queue_size, frame_size>::transmit_half_cplt_cb(void* ctx)
{
    auto* self = static_cast<CAN_Manager<queue_size, frame_size>*>(ctx);
    //self->_tx_half_done = true;
}

template<uint8_t queue_size, uint8_t frame_size>
void CAN_Manager<queue_size, frame_size>::recv_half_cplt_cb(void* ctx)
{
    auto* self = static_cast<CAN_Manager<queue_size, frame_size>*>(ctx);
    //self->_rx_half_done = true;
}

#endif /* MANAGED_COMPONENTS_HCU_SERVICES_CAN_MANAGER_HPP_ */
