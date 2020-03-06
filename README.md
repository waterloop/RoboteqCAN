# RoboteqCAN

Library used: https://github.com/autowp/arduino-mcp2515 

Useful Links: 

	- https://en.wikipedia.org/wiki/CANopen 
	- https://www.generationrobots.com/media/roboteq/can-networking-manual.pdf#page=18&zoom=130,-126,604
	- https://en.wikipedia.org/wiki/CANopen#Object_dictionary

See the following on the 

|                      Byte 0                   | Byte 1-2 | Byte 3   | Byte 4-7 |
|-----------------------------------------------|----------|----------|----------|
| 3 bits, ccs=1 				| 2 bytes  | 1 byte   | 4 bytes  |
| 1 bit, reserved(=0) 				| index    | subindex | data     |
| 2 bit, n
| 1 bit, e
| 1 bit, s

|  Header  |  DLC  |  Byte 0  |  Byte 1-2  |  Byte 3  |  Byte 4-7  |
| ---------|-------|----------|------------|----------|------------|
| 0x600 + nd | 8 | *see Byte 0 table* | index | subindex |      data |

<b> Byte 0 table: </b>

|  bits 4-7  |  bits 2-3  |  bits 0-1  |
| -----------|------------|------------|
| ccs=1      | n          |  xx=0      |

ccs is the client command specifier of the SDO transfer, this is 0 for SDO segment download, 1 for initiating download, 2 for initiating upload, 3 for SDO segment upload, 4 for aborting an SDO transfer, 5 for SDO block upload and 6 for SDO block download

n is the number of bytes in the data part of the message which do not contain data, only valid if e and s are set

e, if set, indicates an expedited transfer, i.e. all data exchanged are contained within the message. If this bit is cleared then the message is a segmented transfer where the data does not fit into one message and multiple messages are used.

s, if set, indicates that the data size is specified in n (if e is set) or in the data part of the message

index is the object dictionary index of the data to be accessed
subindex is the subindex of the object dictionary variable
data contains the data to be uploaded in the case of an expedited transfer (e is set), or the size of the data to be uploaded (s is set, e is not set)
