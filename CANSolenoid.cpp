#include "mbed.h"
#include "CANSolenoid.h"

CANSolenoid::CANSolenoid(PinName rd, PinName td, int dip)
    : _can_p(new CAN(rd, td)), _can(*_can_p)
{
    _msg.id = (dip * 3) + 1500;
    _msg.len = (TotalPinDef - 1) / 8 + 1;
    for(int i=0; i<TotalPinDef; i++) {
        solenoid[i] = OFF;
    }
}

CANSolenoid::CANSolenoid(CAN &can_obj, int dip)
    : _can_p(NULL), _can(can_obj)
{
    _msg.id = (dip * 3) + 1500;
    _msg.len = (TotalPinDef - 1) / 8 + 1;
    for(int i=0; i<TotalPinDef; i++) {
        solenoid[i] = OFF;
    }
}

CANSolenoid::~CANSolenoid()
{
    delete _can_p;
}

void CANSolenoid::write(int get_data, int switching)
{
    if(get_data >= TotalPinDef)
        return;
    if (switching >= TotalSwitching)
        return;

    solenoid[get_data] = switching;

    unsigned int index = get_data / 8;
    if (switching == ON)
        _msg.data[index] |= 1 << (7 - (get_data % 8));
    else
        _msg.data[index] &= ~(1 << (7 - (get_data % 8)));
}

void CANSolenoid::send()
{
    _can.write(_msg);
}