#include "pdo_control.h"
#include "gait.h"
#include "objacces.h"

uint8_t pdoindex = 0;
uint8_t posIndex = 0;

void _post_TPDO(CO_Data* d){
	
	UNS32 data,ByteSize,angle;
	UNS32 retcode;

	(void)retcode;
	ByteSize = 4;
	angle = test_angle[posIndex];

	/** 
	 * 发送控制寄存器0x0F和0x7F, 激活位置模式的改变
	 */
	if(pdoindex % 2 == 0){
		data = 0x0F;
		ByteSize = 2;
		retcode = setODentry( d, 0x6040, 0, &data, &ByteSize, 1 );
		retcode = setODentry( d, 0x607A, 0, &angle, &ByteSize, 1 );
	}
	else{
		data = 0x7F;
		ByteSize = 2;
		retcode = setODentry( d, 0x6040, 0, &data, &ByteSize, 1 );
		retcode = setODentry( d, 0x607A, 0, &angle, &ByteSize, 1 );
		posIndex++;
	}
	pdoindex++;
	
	if(posIndex == 10) posIndex = 0;
}
