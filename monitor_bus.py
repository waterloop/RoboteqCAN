import can
from BusSetup import get_bus
from Commands import receive_canopen

bus = get_bus()

while True:
    for msg in bus:
        print(msg)
        print(receive_canopen(msg))
