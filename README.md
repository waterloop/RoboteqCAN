# RoboteqCAN

Library used: https://github.com/autowp/arduino-mcp2515 

Useful Links: 

	- https://en.wikipedia.org/wiki/CANopen 
	- https://www.generationrobots.com/media/roboteq/can-networking-manual.pdf#page=18&zoom=130,-126,604
	- https://en.wikipedia.org/wiki/CANopen#Object_dictionary

<b> Response from the roboteq device: </b>

|  Header  |  DLC  |  Byte 0  |  Byte 1-2  |  Byte 3  |  Byte 4-7  |
| ---------|-------|----------|------------|----------|------------|
| 0x600 + nd | 8 | *see Byte 0 table* | index | subindex |      data |

<b> Byte 0 table: </b>

|  bits 4-7  |  bits 2-3  |  bits 0-1  |
| -----------|------------|------------|
| ccs=1      | n          |  xx=0      |

*\*each section of Byte 0 is a 4-bit unsigned int*

ccs is the client command specifier of the SDO transfer, this is 0 for SDO segment download, 2 for command, 4 for query, 6 for successful, 8 for error

index is the object dictionary index of the data to be accessed
subindex is the subindex of the object dictionary variable
data contains the data to be uploaded in the case of an expedited transfer (e is set), or the size of the data to be uploaded (s is set, e is not set)
