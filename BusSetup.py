import can

bustype = 'socketcan'
channel = 'vcan0'

def get_bus():
    return can.interface.Bus(channel=channel,bustype=bustype)
