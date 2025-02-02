/******************************************************************************
*
* Copyright (C) 2009 - 2014 Xilinx, Inc.  All rights reserved.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* Use of the Software is limited solely to applications:
* (a) running on a Xilinx device, or
* (b) that interact with a Xilinx device through a bus or interconnect.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
* XILINX  BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
* OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
* Except as contained in this notice, the name of the Xilinx shall not be used
* in advertising or otherwise to promote the sale, use or other dealings in
* this Software without prior written authorization from Xilinx.
*
******************************************************************************/

/*
 * helloworld.c: simple test application
 *
 * This application configures UART 16550 to baud rate 9600.
 * PS7 UART (Zynq) is not initialized by this application, since
 * bootrom/bsp configures it to baud rate 115200
 *
 * ------------------------------------------------
 * | UART TYPE   BAUD RATE                        |
 * ------------------------------------------------
 *   uartns550   9600
 *   uartlite    Configurable only in HW design
 *   ps7_uart    115200 (configured by bootrom/bsp)
 */
/*
#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"


int main()
{
    init_platform();

    print("Hello World\n\r");
    print("Successfully ran Hello World application");
    cleanup_platform();
    return 0;
}
*/
#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"

#include "xil_types.h"
#include "xil_cache.h"
#include "xparameters.h"

#include "xaxivdma.h"
#include "xaxivdma_i.h"
//#include "display_ctrl/display_ctrl.h"
#include "display_ctrl.h"

// Frame size : 32 bits per pixel, using 1280*720 resolution
#define MAX_FRAME (1280*720)
#define FRAME_STRIDE (1280*4)

// XPAR redefines
#define DYNCLK_BASEADDR 		XPAR_AXI_DYNCLK_0_BASEADDR
#define VDMA_ID 				XPAR_AXIVDMA_0_DEVICE_ID
#define HDMI_OUT_VTC_ID 		XPAR_V_TC_OUT_DEVICE_ID

// Define VDMA and Display Struct
DisplayCtrl dispCtrl;
XAxiVdma_Config *vdmaConfig;
XAxiVdma vdma;

u32 frameBuf[DISPLAY_NUM_FRAMES][MAX_FRAME] __attribute__((aligned(0x20))); // Frame buffers for video data
u32 *pFrames[DISPLAY_NUM_FRAMES]; // Array of pointers to the frame buffers

// Define switch or GPIOs variable here
volatile unsigned int sw_value; // switch
volatile unsigned int btn_value; // btn
volatile unsigned int led_value; //pass to LED

int main() {
	print("\nWelcome to the HDMI...\n");
	// Initialise an array of pointers to the 2 frame buffers
	int statusFlag;
	int i;
	for (i = 0; i < DISPLAY_NUM_FRAMES; i++){
		pFrames[i] = frameBuf[i];
	}

	// ------------------------------ INITIALIZE VDMA DRIVER ------------------------------
	vdmaConfig = XAxiVdma_LookupConfig(VDMA_ID);
	if (!vdmaConfig)
		printf("No video DMA found for ID %d\r\n", VDMA_ID);
	else
		printf("video DMA found for ID %d\r\n", VDMA_ID);

	statusFlag = XAxiVdma_CfgInitialize(&vdma, vdmaConfig, vdmaConfig->BaseAddress);
	if (statusFlag != XST_SUCCESS)
		printf("VDMA Configuration Initialization failed %d\r\n", statusFlag);
	else
		printf("VDMA Configuration Initialization passed %d\r\n", statusFlag);


	// ------------------------------ INITIALIZE AND START DISPLAY CONTROLLER ------------------------------

	// Initialise the display controller
	statusFlag= DisplayInitialize(&dispCtrl, &vdma, XPAR_VTC_0_DEVICE_ID, XPAR_DYNCLK_0_S_AXI_LITE_BASEADDR, pFrames, FRAME_STRIDE);
	if (statusFlag != XST_SUCCESS)
		printf("Display Initialization failed %d\r\n", statusFlag);
	else
		printf("Display Initialization passed %d\r\n", statusFlag);

	DisplayChangeFrame(&dispCtrl, 0);
	DisplaySetMode(&dispCtrl, &VMODE_1280x720);
	printf("Display mode set to 1280x720\r\n");

	// Enable video output
	DisplayStart(&dispCtrl);
	printf("HDMI output has started.\n\r");
	printf("\n---------HDMI OUTPUT INFO -------------\n");
	printf("Pixel Clock Frequency: %.3fMHz\n\r", dispCtrl.pxlFreq);
	printf("Resolution: %s\n\r", dispCtrl.vMode.label);


	// ------------------------------ HDMI OUTPUT ------------------------------

	int x, y;
	// Define 2 frames  trying out third frame
	u32 *frame0 = (u32 *)dispCtrl.framePtr[0];
	u32 *frame1 = (u32 *)dispCtrl.framePtr[1];
	//u32 *frame2 = (u32 *)dispCtrl.framePtr[2];

	// Get parameters from display controller struct
	u32 stride = dispCtrl.stride / 4;
	u32 width = dispCtrl.vMode.width;
	u32 height = dispCtrl.vMode.height;


	printf("Width: %lu\n\r", width);
	printf("Height: %lu\n\r", height);
	printf("Stride: %lu\n\r", stride);

	// Define black and white frames
	for (y = 0; y < height; y++)
	{
		for (x = 0; x < width; x++)
		{
			//frame1[y*stride + x] = 0x91B2C7;	//color
			//frame1[y*stride + x] = 0xFFFFFF;
			//frame2[y*stride + x] = 0x91B2C7;
			frame1[y*stride + x] = 0xFF00FF;
			//frame0[y*stride + x] = 0;
			frame0[y*stride + x] = 0x91B2C7;
		}
	}
	Xil_DCacheFlush();

	while(1)
	{
		sw_value = *(unsigned int*) 0x43c00000;
		btn_value = *(unsigned int*) 0x43c00004;
		led_value = sw_value | btn_value;
		*(unsigned int*) 0x43c00008 = led_value;


/*
		if (led_value & 0x01)
		{
			//Display WHITE
			DisplayChangeFrame(&dispCtrl, 1);
		}
		else
		{
			// Display BLACK
			DisplayChangeFrame(&dispCtrl, 0);
		}
*/
		if (sw_value & 0x01)
		{
			//Display WHITE
			DisplayChangeFrame(&dispCtrl, 1);
		}

		else if (btn_value & 0x01)
		{
			DisplayChangeFrame(&dispCtrl, 0);
		}
/*
		else
		{
			//Display BLACK
			DisplayChangeFrame(&dispCtrl, 0);
		}
*/




	}
	return 0;
}
