
#ifndef DJB2_HASH_H
#define DJB2_HASH_H


/****************** Include Files ********************/
#include "xil_types.h"
#include "xil_io.h"
#include "xstatus.h"

#define DJB2_HASH_S00_AXI_SLV_REG0_OFFSET 0
#define DJB2_HASH_S00_AXI_SLV_REG1_OFFSET 4
#define DJB2_HASH_S00_AXI_SLV_REG2_OFFSET 8
#define DJB2_HASH_S00_AXI_SLV_REG3_OFFSET 12

#define DJB2_HASH_LENGTH_4 0x30000000
#define DJB2_HASH_LENGTH_3 0x20000000
#define DJB2_HASH_LENGTH_2 0x10000000
#define DJB2_HASH_LENGTH_1 0x00000000
#define DJB2_HASH_ENABLE   0x40000000

/**************************** Type Definitions *****************************/
/**
 *
 * Write a value to a DJB2_HASH register. A 32 bit write is performed.
 * If the component is implemented in a smaller width, only the least
 * significant data is written.
 *
 * @param   BaseAddress is the base address of the DJB2_HASHdevice.
 * @param   RegOffset is the register offset from the base to write to.
 * @param   Data is the data written to the register.
 *
 * @return  None.
 *
 * @note
 * C-style signature:
 * 	void DJB2_HASH_mWriteReg(u32 BaseAddress, unsigned RegOffset, u32 Data)
 *
 */
#define DJB2_HASH_mWriteReg(BaseAddress, RegOffset, Data) \
  	Xil_Out32((BaseAddress) + (RegOffset), (u32)(Data))

/**
 *
 * Read a value from a DJB2_HASH register. A 32 bit read is performed.
 * If the component is implemented in a smaller width, only the least
 * significant data is read from the register. The most significant data
 * will be read as 0.
 *
 * @param   BaseAddress is the base address of the DJB2_HASH device.
 * @param   RegOffset is the register offset from the base to write to.
 *
 * @return  Data is the data from the register.
 *
 * @note
 * C-style signature:
 * 	u32 DJB2_HASH_mReadReg(u32 BaseAddress, unsigned RegOffset)
 *
 */
#define DJB2_HASH_mReadReg(BaseAddress, RegOffset) \
    Xil_In32((BaseAddress) + (RegOffset))

#define DJB2_HASH_reset(BaseAddress) \
    DJB2_HASH_mWriteReg((BaseAddress), (DJB2_HASH_S00_AXI_SLV_REG0_OFFSET), 0x80000000)

#define DJB2_HASH_sendData(BaseAddress, Data) \
    do {DJB2_HASH_mWriteReg((BaseAddress), (DJB2_HASH_S00_AXI_SLV_REG0_OFFSET), (Data|DJB2_HASH_ENABLE));\
    DJB2_HASH_mWriteReg((BaseAddress), (DJB2_HASH_S00_AXI_SLV_REG0_OFFSET), (Data));} while(0)

#define DJB2_HASH_isBusy(BaseAddress) \
    (DJB2_HASH_mReadReg((BaseAddress), (DJB2_HASH_S00_AXI_SLV_REG2_OFFSET)))
/************************** Function Prototypes ****************************/
/**
 *
 * Run a self-test on the driver/device. Note this may be a destructive test if
 * resets of the device are performed.
 *
 * If the hardware system is not built correctly, this function may never
 * return to the caller.
 *
 * @param   baseaddr_p is the base address of the DJB2_HASH instance to be worked on.
 *
 * @return
 *
 *    - XST_SUCCESS   if all self-test code passed
 *    - XST_FAILURE   if any self-test code failed
 *
 * @note    Caching must be turned off for this function to work.
 * @note    Self test may fail if data memory and device are not on the same bus.
 *
 */
XStatus DJB2_HASH_Reg_SelfTest(void * baseaddr_p);
u32 djb2_hash(UINTPTR baseAddr, u8* str, u32 length);

#endif // DJB2_HASH_H
