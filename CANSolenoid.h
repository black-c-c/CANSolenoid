#ifndef _CANSolenoid_H_
#define _CANSolenoid_H_

#include "mbed.h"

class CANSolenoid
{
public:

    enum PinDef {
        OFF,
        ON,
        A1,
        A2,
        A3,
        A4,
        A5,
        A6,
        A7,
        B1,
        B2,
        B3,
        B4,
        B5,
        B6,
        B7,
        C1,
        C2,
        C3,
    };
    CANSolenoid(PinName rd, PinName td, int dip);
 
    CANSolenoid(CAN &can_obj, int dip);
 
    ~CANSolenoid();
    
    void send();
    void write(int get_data, int switching);
    
private:

    CAN *_can_p;
    CAN &_can;
    CANMessage _msg;

    int a[7];
    int b[7];
    int c[3];
    int i;
};
#endif