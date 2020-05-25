
/* File generated by gen_cfile.py. Should not be modified. */

#include "TestSlave.h"

/**************************************************************************/
/* Declaration of mapped variables                                        */
/**************************************************************************/

/**************************************************************************/
/* Declaration of value range types                                       */
/**************************************************************************/

#define valueRange_EMC 0x9F /* Type for index 0x1003 subindex 0x00 (only set of value 0 is possible) */
UNS32 TestSlave_valueRangeTest (UNS8 typeValue, void * value)
{
  switch (typeValue) {
    case valueRange_EMC:
      if (*(UNS8*)value != (UNS8)0) return OD_VALUE_RANGE_EXCEEDED;
      break;
  }
  return 0;
}

/**************************************************************************/
/* The node id                                                            */
/**************************************************************************/
/* node_id default value.*/
UNS8 TestSlave_bDeviceNodeId = 0x00;

/**************************************************************************/
/* Array of message processing information */

const UNS8 TestSlave_iam_a_slave = 1;

TIMER_HANDLE TestSlave_heartBeatTimers[1];

/*
$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$

                               OBJECT DICTIONARY

$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
*/

/* index 0x1000 :   Device Type. */
                    UNS32 TestSlave_obj1000 = 0x0;	/* 0 */
                    subindex TestSlave_Index1000[] = 
                     {
                       { RO, uint32, sizeof (UNS32), (void*)&TestSlave_obj1000, NULL }
                     };

/* index 0x1001 :   Error Register. */
                    UNS8 TestSlave_obj1001 = 0x0;	/* 0 */
                    subindex TestSlave_Index1001[] = 
                     {
                       { RO, uint8, sizeof (UNS8), (void*)&TestSlave_obj1001, NULL }
                     };

/* index 0x1003 :   Pre-defined Error Field */
                    UNS8 TestSlave_highestSubIndex_obj1003 = 0; /* number of subindex - 1*/
                    UNS32 TestSlave_obj1003[] = 
                    {
                      0x0	/* 0 */
                    };
                    subindex TestSlave_Index1003[] = 
                     {
                       { RW, valueRange_EMC, sizeof (UNS8), (void*)&TestSlave_highestSubIndex_obj1003, NULL },
                       { RO, uint32, sizeof (UNS32), (void*)&TestSlave_obj1003[0], NULL }
                     };

/* index 0x1005 :   SYNC COB ID */
                    UNS32 TestSlave_obj1005 = 0x0;   /* 0 */

/* index 0x1006 :   Communication / Cycle Period */
                    UNS32 TestSlave_obj1006 = 0x0;   /* 0 */

/* index 0x100C :   Guard Time */ 
                    UNS16 TestSlave_obj100C = 0x0;   /* 0 */

/* index 0x100D :   Life Time Factor */ 
                    UNS8 TestSlave_obj100D = 0x0;   /* 0 */

/* index 0x1014 :   Emergency COB ID */
                    UNS32 TestSlave_obj1014 = 0x80 + 0x00;   /* 128 + NodeID */

/* index 0x1016 :   Consumer Heartbeat Time */
                    UNS8 TestSlave_highestSubIndex_obj1016 = 0;
                    UNS32 TestSlave_obj1016[]={0};

/* index 0x1017 :   Producer Heartbeat Time. */
                    UNS16 TestSlave_obj1017 = 0x3E8;	/* 1000 */
                    subindex TestSlave_Index1017[] = 
                     {
                       { RW, uint16, sizeof (UNS16), (void*)&TestSlave_obj1017, NULL }
                     };

/* index 0x1018 :   Identity. */
                    UNS8 TestSlave_highestSubIndex_obj1018 = 4; /* number of subindex - 1*/
                    UNS32 TestSlave_obj1018_Vendor_ID = 0x0;	/* 0 */
                    UNS32 TestSlave_obj1018_Product_Code = 0x0;	/* 0 */
                    UNS32 TestSlave_obj1018_Revision_Number = 0x0;	/* 0 */
                    UNS32 TestSlave_obj1018_Serial_Number = 0x0;	/* 0 */
                    subindex TestSlave_Index1018[] = 
                     {
                       { RO, uint8, sizeof (UNS8), (void*)&TestSlave_highestSubIndex_obj1018, NULL },
                       { RO, uint32, sizeof (UNS32), (void*)&TestSlave_obj1018_Vendor_ID, NULL },
                       { RO, uint32, sizeof (UNS32), (void*)&TestSlave_obj1018_Product_Code, NULL },
                       { RO, uint32, sizeof (UNS32), (void*)&TestSlave_obj1018_Revision_Number, NULL },
                       { RO, uint32, sizeof (UNS32), (void*)&TestSlave_obj1018_Serial_Number, NULL }
                     };

/**************************************************************************/
/* Declaration of pointed variables                                       */
/**************************************************************************/

const indextable TestSlave_objdict[] = 
{
  { (subindex*)TestSlave_Index1000,sizeof(TestSlave_Index1000)/sizeof(TestSlave_Index1000[0]), 0x1000},
  { (subindex*)TestSlave_Index1001,sizeof(TestSlave_Index1001)/sizeof(TestSlave_Index1001[0]), 0x1001},
  { (subindex*)TestSlave_Index1017,sizeof(TestSlave_Index1017)/sizeof(TestSlave_Index1017[0]), 0x1017},
  { (subindex*)TestSlave_Index1018,sizeof(TestSlave_Index1018)/sizeof(TestSlave_Index1018[0]), 0x1018},
};

const indextable * TestSlave_scanIndexOD (CO_Data *d, UNS16 wIndex, UNS32 * errorCode)
{
	(void)d;
	int i;
	switch(wIndex){
		case 0x1000: i = 0;break;
		case 0x1001: i = 1;break;
		case 0x1017: i = 2;break;
		case 0x1018: i = 3;break;
		default:
			*errorCode = OD_NO_SUCH_OBJECT;
			return NULL;
	}
	*errorCode = OD_SUCCESSFUL;
	return &TestSlave_objdict[i];
}

/* 
 * To count at which received SYNC a PDO must be sent.
 * Even if no pdoTransmit are defined, at least one entry is computed
 * for compilations issues.
 */
s_PDO_status TestSlave_PDO_status[1] = {s_PDO_status_Initializer};

const quick_index TestSlave_firstIndex = {
  0, /* SDO_SVR */
  0, /* SDO_CLT */
  0, /* PDO_RCV */
  0, /* PDO_RCV_MAP */
  0, /* PDO_TRS */
  0 /* PDO_TRS_MAP */
};

const quick_index TestSlave_lastIndex = {
  0, /* SDO_SVR */
  0, /* SDO_CLT */
  0, /* PDO_RCV */
  0, /* PDO_RCV_MAP */
  0, /* PDO_TRS */
  0 /* PDO_TRS_MAP */
};

const UNS16 TestSlave_ObjdictSize = sizeof(TestSlave_objdict)/sizeof(TestSlave_objdict[0]); 

CO_Data TestSlave_Data = CANOPEN_NODE_DATA_INITIALIZER(TestSlave);

