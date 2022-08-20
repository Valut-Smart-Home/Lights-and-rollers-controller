#include "twi.h"

#include <avr/io.h>

enum class twi_status : uint8_t
{
  Start_OK = 0x08,
  Repeated_Start_OK = 0x10,
  SLA_W_Transmited_ACK = 0x18,
  SLA_W_Transmited_NO_ACK = 0x20,
  Data_Transmited_ACK = 0x28,
  Data_Transmited_NO_ACK = 0x30,
  Arbitration_Lost = 0x38,
  SLA_R_Transmited_ACK = 0x40,
  SLA_R_Transmited_NO_ACK = 0x48,
  Data_Received_ACK = 0x50,
  Data_Received_NO_ACK = 0x58,
};

enum class twi_state: uint8_t
{
  waiting,
  starting,
  addressing_w,
  addressing_r,
  transmiting,
  receiving,
  stoping
};

inline void twi_start()
{
  TWCR = _BV(TWINT) | _BV(TWEN) | _BV(TWSTA) | _BV(TWSTO);
}

inline void twi_stop()
{
  TWCR = _BV(TWINT) | _BV(TWEN) | _BV(TWSTO);
}

inline void twi_send(const uint8_t&& byte)
{
  TWDR = byte;
  TWCR = _BV(TWINT) | _BV(TWEN);
}

inline const uint8_t& twi_read()
{
  return TWDR;
}

inline void twi_send_ack()
{
  TWCR = _BV(TWINT) | _BV(TWEN) | _BV(TWEA);
}

inline void twi_send_nack()
{
  TWCR = _BV(TWINT) | _BV(TWEN);
}

inline const uint8_t twi_isReady()
{
  return TWCR & _BV(TWINT);
}

inline const uint8_t twi_getStatus()
{
  return TWSR & 0xF8;
}

namespace lights_and_rollers::hardware
{
  void Twi::Init()
  {
    TWBR = (F_CPU / 100000 - 16) / 2;
    TWCR = 
      (0 << TWINT) |
      (0 << TWEA) | (0 << TWSTA) | (0 << TWSTO) |
      (0 << TWWC) |
      (1 << TWEN) |
      (0 << TWIE);
    
    state_ = twi_state::waiting;
  }

  void Twi::Execute()
  {
    if (!twi_isReady()) {
      return;
    }

    switch (state_)
    {
    case twi_state::starting:
      if (twi_getStatus() == twi_status::Start_OK) {
        twi_send(buffer[0]);
        state_ = buffer[0] & 0x01 
          ? twi_state::addressing_w 
          : twi_state::addressing_r;
      } else {
        state_ = twi_state::stoping;
      }
      break;
    
    case twi_state::addressing_w:
      if (twi_getStatus() == twi_status::SLA_W_Transmited_ACK) {
        twi_send[++bufferIndex_];
        state_ = twi_state::transmiting;
      } else {
        state_ = twi_state::stoping;
      }
      break;

    case twi_state::transmiting:
      if (twi_getStatus() == twi_status::Data_Transmited_ACK) {
        if (bufferIndex_ < count_) {
          twi_send(buffer[++bufferIndex_])
        } else {
          twi_stop();
          state_ = twi_state::waiting;
        }
      } else {
        state_ = twi_state::stoping;
      }
      break;
    
    case twi_state::addressing_r:
      if (twi_getStatus() == twi_status::SLA_R_Transmited_ACK) {
        twi_send_ack();
        ++bufferIndex_;
        state_ = twi_state::receiving;
      } else {
        state_ = twi_state::stoping;
      }
      break;

    case twi_state::receiving:
      if (twi_getStatus() == twi_status::Data_Received_ACK) {
        buffer[bufferIndex_] = twi_read();
        ++bufferIndex_;
        if (bufferIndex_ <= count_) {
          twi_send_ack();
          break;
        } else {
          twi_send_nack();
        }
      }
      state_ = twi_state::stoping;
      break;

    case twi_state::stoping:
      twi_stop();
      state_ = twi_state::waiting;
      break;

    default:
      break;
    }
  }

  bool Twi::is_ready()
  {
    return state_ == twi_state::waiting && twi_isReady();
  }

  bool Twi::is_ok()
  {
    return ok_;
  }

  void Twi::ExecuteBuffer(const uint8_t&& count)
  {
    if (state == twi_state::waiting) {
      ok_ = false;
      bufferIndex_ = 0;
      count_ = count;
      
      if (count) {
        twi_start();
        state_ = twi_state::starting;
      }
    }
  }
}
