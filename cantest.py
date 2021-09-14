import time
import can
from BusSetup import get_bus
from Commands import send_canopen, send_set_motor_command

bus = get_bus()

def producer(id):

    for i in range(10):
        msg = can.Message(arbitration_id=0xc0ffee, data=[id, i % 256, 0, 1, 3, 1, 4, 1], is_extended_id = False)
        bus.send(msg)

    time.sleep(1)

# producer(10)

'''
send_canopen(
    node_id=1,
    is_query=False,
    empty_bytes=0,
    index=0x2003,
    subindex=0x02,
    data=0x0a000000
)
'''

send_set_motor_command(
    1,
    2,
    -50
)



