

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Thu Oct 31 14:53:47 2019
 */
/* Compiler settings for UDLServer.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 7.00.0555 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


#ifdef __cplusplus
extern "C"{
#endif 


#include <rpc.h>
#include <rpcndr.h>

#ifdef _MIDL_USE_GUIDDEF_

#ifndef INITGUID
#define INITGUID
#include <guiddef.h>
#undef INITGUID
#else
#include <guiddef.h>
#endif

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        DEFINE_GUID(name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8)

#else // !_MIDL_USE_GUIDDEF_

#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        const type name = {l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}}

#endif !_MIDL_USE_GUIDDEF_

MIDL_DEFINE_GUID(IID, IID_IEngineMgr,0x9CEBB9DF,0x8EE5,0x42E8,0xBC,0x16,0x38,0xD0,0xD2,0x22,0x67,0xA7);


MIDL_DEFINE_GUID(IID, LIBID_UDLSERVERLib,0x7FA750BF,0x178D,0x475A,0x9A,0xA1,0xDE,0xB5,0x56,0xBB,0x0E,0x95);


MIDL_DEFINE_GUID(IID, DIID__IEngineMgrEvents,0xF34AE487,0x9066,0x4F9E,0xAF,0x71,0x7C,0x1C,0xBA,0x2E,0x96,0x92);


MIDL_DEFINE_GUID(CLSID, CLSID_EngineMgr,0xB73F2E4C,0xA43F,0x48BB,0xBA,0x61,0xE2,0x5B,0x4D,0x2B,0x96,0xAF);


MIDL_DEFINE_GUID(IID, DIID__IEnginePtrEvents,0xCDF068AB,0xA4F9,0x45FC,0x87,0x42,0xC1,0x27,0x2F,0xC4,0xF1,0xB0);


MIDL_DEFINE_GUID(IID, IID_IITLSInterface,0x0B50A5FA,0x6D5A,0x46D3,0xBA,0x2B,0x36,0x08,0xFE,0xF0,0x97,0x6A);


MIDL_DEFINE_GUID(IID, IID_IIPMInterface,0xA078CFDE,0x41C1,0x45D2,0xAD,0xC9,0x20,0xE8,0xB1,0x28,0x99,0x6B);


MIDL_DEFINE_GUID(IID, IID_IIVOAInterface,0xA1B84183,0xA9EF,0x41D9,0xA8,0x94,0xD0,0x08,0xCB,0xB0,0xD5,0xE4);


MIDL_DEFINE_GUID(IID, IID_IIOSAInterface,0x104889A9,0x452E,0x419F,0x85,0xE0,0xEA,0x5A,0xEB,0x72,0xDB,0xCA);


MIDL_DEFINE_GUID(IID, IID_IIPolInterface,0xAF1A856A,0xF3E6,0x4461,0x9D,0xC4,0xF1,0xF8,0x7E,0xA6,0x1F,0x37);


MIDL_DEFINE_GUID(IID, IID_IScanInterface,0x7CDE6BE4,0x4B5C,0x46DC,0x99,0xC5,0x1B,0x68,0x01,0x78,0x71,0x3F);


MIDL_DEFINE_GUID(IID, IID_IChamberInterface,0x89A6FDE2,0x516B,0x4432,0xAF,0x08,0x1D,0xCE,0x00,0x5D,0x0B,0x1E);


MIDL_DEFINE_GUID(IID, IID_IIComDevInterface,0x309343A5,0xA079,0x4F81,0x9D,0xA2,0xFE,0x2D,0x05,0x38,0xDC,0x2D);


MIDL_DEFINE_GUID(IID, IID_IISwitchBoxInterface,0xBE62156F,0x2AF7,0x4DD0,0xBB,0x5E,0xAA,0xE2,0x5A,0x0B,0x4B,0xFA);


MIDL_DEFINE_GUID(CLSID, CLSID_ITLSInterface,0x82E74FAE,0xD809,0x47C0,0x8C,0xD3,0x7F,0x65,0x3C,0xBB,0x4F,0xD8);


MIDL_DEFINE_GUID(CLSID, CLSID_IPMInterface,0x2AA6F3FA,0x6507,0x49DF,0x87,0x91,0x97,0x1F,0x31,0x30,0x19,0x92);


MIDL_DEFINE_GUID(CLSID, CLSID_IVOAInterface,0xE5B0D9E8,0xE9F9,0x4C14,0x9E,0x48,0xA6,0x0C,0x4E,0xC7,0x42,0x52);


MIDL_DEFINE_GUID(CLSID, CLSID_IOSAInterface,0xB4E0C31C,0x404B,0x41A6,0x84,0x3C,0x64,0x77,0x0A,0xA3,0x49,0xB0);


MIDL_DEFINE_GUID(CLSID, CLSID_IPolInterface,0x17B09D77,0x2E06,0x4678,0x98,0xE3,0x23,0xDF,0xEA,0x82,0x62,0xF9);


MIDL_DEFINE_GUID(CLSID, CLSID_ScanInterface,0x5B3B1877,0x867F,0x4742,0xB3,0xD7,0x30,0x2F,0x08,0xCE,0x03,0x2B);


MIDL_DEFINE_GUID(CLSID, CLSID_ChamberInterface,0x90321366,0xD7CC,0x4F21,0x94,0xF4,0x75,0x6C,0xA1,0xDB,0x1B,0x34);


MIDL_DEFINE_GUID(CLSID, CLSID_IComDevInterface,0xCB4F7BD8,0x2FC4,0x40C9,0x8F,0x8F,0xC2,0xFF,0x01,0xE5,0xEA,0x63);


MIDL_DEFINE_GUID(CLSID, CLSID_ISwitchBoxInterface,0x4885F744,0xA490,0x42F0,0x8F,0xAF,0x7F,0x0F,0x5B,0x90,0xFB,0xC6);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



