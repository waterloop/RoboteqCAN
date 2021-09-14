import can
from BusSetup import get_bus

bus = get_bus()

def send_canopen(node_id, is_query, empty_bytes, index, subindex, data):

    byte_0 = 0b00000000 | ((4 if is_query else 2) << 4) | (empty_bytes << 2)
    
    msg = can.Message(
        arbitration_id=0x600 + node_id,
        is_extended_id=False,
        data=[
            byte_0,
            (index >> (8 * 0)) & 0b11111111,
            (index >> (8 * 1)) & 0b11111111,
            subindex,
            (data >> (8 * 0)) & 0b11111111,
            (data >> (8 * 1)) & 0b11111111,
            (data >> (8 * 2)) & 0b11111111,
            (data >> (8 * 3)) & 0b11111111
        ]
    )

    bus.send(msg)


def receive_canopen(can_msg):

    frame_header = can_msg.arbitration_id
    data_bytes = can_msg.data

    byte_0 = data_bytes [0]

    data = 0
    for i in range(4):
        data = data + (data_bytes[7 - i] << (8 * i))

    css = (byte_0 >> 4) & 0b1111

    return {
        "header": frame_header,
        "node_id": frame_header - 0x580,
        "css": css,
        "query_response": css == 4,
        "command_response": css == 6,
        "error": css == 8,
        "empty_data_bits": (byte_0 >> 2) & 0b11,
    
        "index": (data_bytes[1] << 8) | data_bytes[2],
        "subindex": data_bytes[3],
        "data": data
    }


def send_set_motor_command(node_id, max_motors,throttle_percent):
    send_canopen(
        node_id=node_id,
        is_query=False,
        empty_bytes=0,
        index=0x2000,
        subindex=max_motors,
        data=throttle_percent*10 # 1000 for 100%, -1000 for -100%
    )
