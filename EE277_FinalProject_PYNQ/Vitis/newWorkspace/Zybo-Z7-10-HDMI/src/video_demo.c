




/***********************************************************************

	video_demo.c	--	ZYBO Video demonstration

**********************************************************************
	Author: Sam Bobrowicz
	Copyright 2015, Digilent Inc.
**********************************************************************
  Module Description:

		This file contains code for running a demonstration of the
		Video input and output capabilities on the ZYBO. It is a good
		example of how to properly use the display_ctrl and
		video_capture drivers.


**********************************************************************
  Revision History:

		11/25/2015(SamB): Created

**********************************************************************

 ------------------------------------------------------------
				Include File Definitions
 ------------------------------------------------------------*/

#include "video_demo.h"
#include "video_capture/video_capture.h"
#include "display_ctrl/display_ctrl.h"
#include "intc/intc.h"
#include <stdio.h>
#include "xuartps.h"
#include "math.h"
#include <ctype.h>
#include <stdlib.h>
#include "xil_types.h"
#include "xil_cache.h"
#include "timer_ps/timer_ps.h"
#include "xparameters.h"
#include "xil_cache.h"


 //XPAR redefines

#define DYNCLK_BASEADDR 		XPAR_AXI_DYNCLK_0_S_AXI_LITE_BASEADDR
#define VDMA_ID 				XPAR_AXIVDMA_0_DEVICE_ID
#define HDMI_OUT_VTC_ID 		XPAR_V_TC_OUT_DEVICE_ID
#define HDMI_IN_VTC_ID 			XPAR_V_TC_IN_DEVICE_ID
#define HDMI_IN_GPIO_ID 		XPAR_AXI_GPIO_VIDEO_DEVICE_ID
#define HDMI_IN_VTC_IRPT_ID 	XPAR_FABRIC_V_TC_IN_IRQ_INTR
#define HDMI_IN_GPIO_IRPT_ID 	XPAR_FABRIC_AXI_GPIO_VIDEO_IP2INTC_IRPT_INTR
#define SCU_TIMER_ID 			XPAR_SCUTIMER_DEVICE_ID
#define UART_BASEADDR 			XPAR_PS7_UART_1_BASEADDR

 /*------------------------------------------------------------
				Global Variables
 ------------------------------------------------------------*/


 //Display and Video Driver structs

DisplayCtrl dispCtrl;
XAxiVdma vdma;
VideoCapture videoCapt;//no need for volatile because the videoCapt's state is either checked just one time
					   //in functions VideoStart and VideoStop, or (in the DemoGetInactiveFrame function) the worst case scenario is
                       //losing the frame with the inverted colors of the frame gotten from the disconnected input
INTC intc;
char fRefresh; //flag used to trigger a refresh of the Menu on video detect


 //Framebuffers for video data

u8 frameBuf[DISPLAY_NUM_FRAMES][DEMO_MAX_FRAME] __attribute__((aligned(0x20)));
u8 *pFrames[DISPLAY_NUM_FRAMES]; //array of pointers to the frame buffers


 //Interrupt vector table

const ivt_t ivt[] = {
	videoGpioIvt(HDMI_IN_GPIO_IRPT_ID, &videoCapt),
	videoVtcIvt(HDMI_IN_VTC_IRPT_ID, &(videoCapt.vtc))
};

 /*------------------------------------------------------------
				Procedure Definitions
 ------------------------------------------------------------*/
volatile unsigned int swValue=0, btnValue=0, ledValue = 0;
int filterThreshold = 20; // Default threshold

int main(void)
{

	DemoInitialize();

	DemoRun();

	return 0;
}


void DemoInitialize()
{
	int Status;
	XAxiVdma_Config *vdmaConfig;
	int i;


	 //Initialize an array of pointers to the 3 frame buffers

	for (i = 0; i < DISPLAY_NUM_FRAMES; i++)
	{
		pFrames[i] = frameBuf[i];
	}


	 //Initialize a timer used for a simple delay

	TimerInitialize(SCU_TIMER_ID);


	 //Initialize VDMA driver

	vdmaConfig = XAxiVdma_LookupConfig(VDMA_ID);
	if (!vdmaConfig)
	{
		xil_printf("No video DMA found for ID %d\r\n", VDMA_ID);
		return;
	}
	Status = XAxiVdma_CfgInitialize(&vdma, vdmaConfig, vdmaConfig->BaseAddress);
	if (Status != XST_SUCCESS)
	{
		xil_printf("VDMA Configuration Initialization failed %d\r\n", Status);
		return;
	}


	 //Initialize the Display controller and start it

	Status = DisplayInitialize(&dispCtrl, &vdma, HDMI_OUT_VTC_ID, DYNCLK_BASEADDR, pFrames, DEMO_STRIDE);
	if (Status != XST_SUCCESS)
	{
		xil_printf("Display Ctrl initialization failed during demo initialization%d\r\n", Status);
		return;
	}
	Status = DisplayStart(&dispCtrl);
	if (Status != XST_SUCCESS)
	{
		xil_printf("Couldn't start display during demo initialization%d\r\n", Status);
		return;
	}


	 //Initialize the Interrupt controller and start it.

	Status = fnInitInterruptController(&intc);
	if(Status != XST_SUCCESS) {
		xil_printf("Error initializing interrupts");
		return;
	}
	fnEnableInterrupts(&intc, &ivt[0], sizeof(ivt)/sizeof(ivt[0]));


	 //Initialize the Video Capture device

	Status = VideoInitialize(&videoCapt, &intc, &vdma, HDMI_IN_GPIO_ID, HDMI_IN_VTC_ID, HDMI_IN_VTC_IRPT_ID, pFrames, DEMO_STRIDE, DEMO_START_ON_DET);
	if (Status != XST_SUCCESS)
	{
		xil_printf("Video Ctrl initialization failed during demo initialization%d\r\n", Status);
		return;
	}


	 //Set the Video Detect callback to trigger the menu to reset, displaying the new detected resolution

	VideoSetCallback(&videoCapt, DemoISR, &fRefresh);

	DemoPrintTest(dispCtrl.framePtr[dispCtrl.curFrame], dispCtrl.vMode.width, dispCtrl.vMode.height, dispCtrl.stride, DEMO_PATTERN_1);

	return;
}

void DemoRun()
{
    int nextFrame = 0;
    char userInput = 0;
    xil_printf("Stuck 1\n\t\r");
     //Flush UART FIFO
    while (XUartPs_IsReceiveData(UART_BASEADDR))
    {
    	xil_printf("Stuck 2\n\t\r");
        XUartPs_ReadReg(UART_BASEADDR, XUARTPS_FIFO_OFFSET);
    }
    xil_printf("Stuck 3\n\t\r");
    while (userInput != 'q')
    {
        swValue = *(unsigned int *)0x43C30000; // Read switch states
        btnValue = *(unsigned int *)0x43C30004; // Read button states
        *(unsigned int *)0x43C30008 = swValue; // Update LEDs based on switches

        // Set threshold based on the last button pressed
        if (btnValue & 0b0001) filterThreshold = 10; // Button 0
        if (btnValue & 0b0010) filterThreshold = 25; // Button 1
        if (btnValue & 0b0100) filterThreshold = 50; // Button 2
        if (btnValue & 0b1000) filterThreshold = 70; // Button 3

        fRefresh = 0;
        DemoPrintMenu();

         //Wait for data on UART
        while (!XUartPs_IsReceiveData(UART_BASEADDR) && !fRefresh)
        {
        	//xil_printf("Stuck in Loop%c", swValue);
        }

         //Store the first character in the UART receive FIFO and echo it
        if (XUartPs_IsReceiveData(UART_BASEADDR))
        {
            userInput = XUartPs_ReadReg(UART_BASEADDR, XUARTPS_FIFO_OFFSET);
            xil_printf("%c", userInput);
        }
        else // Refresh triggered by video detect interrupt
        {
            userInput = 'r';
        }

        switch (userInput)
        {
        case '1':
            DemoChangeRes();
            break;
        case '2':
            nextFrame = dispCtrl.curFrame + 1;
            if (nextFrame >= DISPLAY_NUM_FRAMES)
            {
                nextFrame = 1;
            }
            DisplayChangeFrame(&dispCtrl, nextFrame);
            break;
        case '3':
            DemoPrintTest(pFrames[dispCtrl.curFrame], dispCtrl.vMode.width, dispCtrl.vMode.height, DEMO_STRIDE, DEMO_PATTERN_0);
            break;
        case '4':
            DemoPrintTest(pFrames[dispCtrl.curFrame], dispCtrl.vMode.width, dispCtrl.vMode.height, DEMO_STRIDE, DEMO_PATTERN_1);
            break;
        case '5':
            if (videoCapt.state == VIDEO_STREAMING)
                VideoStop(&videoCapt);
            else
                VideoStart(&videoCapt);
            break;
        case '6':
            nextFrame = videoCapt.curFrame + 1;
            if (nextFrame >= DISPLAY_NUM_FRAMES)
            {
                nextFrame = 1;
            }
            VideoChangeFrame(&videoCapt, nextFrame);
            break;
        case '7': // Grab Video Frame and Apply Filters
        	ChangeFilter();
        	break;
        case '8':
            nextFrame = DemoGetInactiveFrame(&dispCtrl, &videoCapt);
            VideoStop(&videoCapt);
            DemoScaleFrame(pFrames[videoCapt.curFrame], pFrames[nextFrame], videoCapt.timing.HActiveVideo, videoCapt.timing.VActiveVideo, dispCtrl.vMode.width, dispCtrl.vMode.height, DEMO_STRIDE);
            VideoStart(&videoCapt);
            DisplayChangeFrame(&dispCtrl, nextFrame);
            break;
        case 'q':
            break;
        case 'r':
            break;
        default:
            xil_printf("\n\rInvalid Selection");
            TimerDelay(500000);
        }
    }
}


void DemoPrintMenu()
{
	xil_printf("\x1B[H"); //Set cursor to top left of terminal
	xil_printf("\x1B[2J"); //Clear terminal
	xil_printf("**************************************************\n\r");
	xil_printf("*                ZYBO Video Demo                 *\n\r");
	xil_printf("**************************************************\n\r");
	xil_printf("*Display Resolution: %28s*\n\r", dispCtrl.vMode.label);
	printf("*Display Pixel Clock Freq. (MHz): %15.3f*\n\r", dispCtrl.pxlFreq);
	xil_printf("*Display Frame Index: %27d*\n\r", dispCtrl.curFrame);
	if (videoCapt.state == VIDEO_DISCONNECTED) xil_printf("*Video Capture Resolution: %22s*\n\r", "!HDMI UNPLUGGED!");
	else xil_printf("*Video Capture Resolution: %17dx%-4d*\n\r", videoCapt.timing.HActiveVideo, videoCapt.timing.VActiveVideo);
	xil_printf("*Video Frame Index: %29d*\n\r", videoCapt.curFrame);
	xil_printf("**************************************************\n\r");
	xil_printf("\n\r");
	xil_printf("1 - Change Display Resolution\n\r");
	xil_printf("2 - Change Display Framebuffer Index\n\r");
	xil_printf("3 - Print Blended Test Pattern to Display Framebuffer\n\r");
	xil_printf("4 - Print Color Bar Test Pattern to Display Framebuffer\n\r");
	xil_printf("5 - Start/Stop Video stream into Video Framebuffer\n\r");
	xil_printf("6 - Change Video Framebuffer Index\n\r");
	xil_printf("7 - Grab Video Frame and apply filters with switches\n\r");
	xil_printf("\tSwitches OFF - Normal\n\r");
	xil_printf("\tSwitch 1 ON - Grayscale\n\r");
	xil_printf("\tSwitch 2 ON - Sobel\n\r");
	xil_printf("\tSwitch 3 ON - Robert Cross\n\r");
	xil_printf("\tSwitch 4 ON - Prewitt\n\r");
	xil_printf("\tSwitch 5 ON - Grayscale\n\r");
	xil_printf("\tSwitch 6 ON - Invert\n\r");
	xil_printf("8 - Grab Video Frame and scale to Display resolution\n\r");
	xil_printf("q - Quit\n\r");
	xil_printf("\n\r");
	xil_printf("\n\r");
	xil_printf("Enter a selection:");
}

void DemoChangeRes()
{
	int fResSet = 0;
	int status;
	char userInput = 0;

	 //Flush UART FIFO
	while (XUartPs_IsReceiveData(UART_BASEADDR))
	{
		XUartPs_ReadReg(UART_BASEADDR, XUARTPS_FIFO_OFFSET);
	}

	while (!fResSet)
	{
		DemoCRMenu();

		 //Wait for data on UART
		while (!XUartPs_IsReceiveData(UART_BASEADDR))
		{}

		 //Store the first character in the UART recieve FIFO and echo it
		userInput = XUartPs_ReadReg(UART_BASEADDR, XUARTPS_FIFO_OFFSET);
		xil_printf("%c", userInput);
		status = XST_SUCCESS;
		switch (userInput)
		{
		case '1':
			status = DisplayStop(&dispCtrl);
			DisplaySetMode(&dispCtrl, &VMODE_640x480);
			DisplayStart(&dispCtrl);
			fResSet = 1;
			break;
		case '2':
			status = DisplayStop(&dispCtrl);
			DisplaySetMode(&dispCtrl, &VMODE_800x600);
			DisplayStart(&dispCtrl);
			fResSet = 1;
			break;
		case '3':
			status = DisplayStop(&dispCtrl);
			DisplaySetMode(&dispCtrl, &VMODE_1280x720);
			DisplayStart(&dispCtrl);
			fResSet = 1;
			break;
		case '4':
			status = DisplayStop(&dispCtrl);
			DisplaySetMode(&dispCtrl, &VMODE_1280x1024);
			DisplayStart(&dispCtrl);
			fResSet = 1;
			break;
		case '5':
			status = DisplayStop(&dispCtrl);
			DisplaySetMode(&dispCtrl, &VMODE_1600x900);
			DisplayStart(&dispCtrl);
			fResSet = 1;
			break;
		case '6':
			status = DisplayStop(&dispCtrl);
			DisplaySetMode(&dispCtrl, &VMODE_1920x1080);
			DisplayStart(&dispCtrl);
			fResSet = 1;
			break;
		case 'q':
			fResSet = 1;
			break;
		default :
			xil_printf("\n\rInvalid Selection");
			TimerDelay(500000);
		}
		if (status == XST_DMA_ERROR)
		{
			xil_printf("\n\rWARNING: AXI VDMA Error detected and cleared\n\r");
		}
	}
}

void DemoCRMenu()
{
	xil_printf("\x1B[H"); //Set cursor to top left of terminal
	xil_printf("\x1B[2J"); //Clear terminal
	xil_printf("**********************************************************\n\r");
	xil_printf("*               Hunter's ZYBO Video Demo                 *\n\r");
	xil_printf("**********************************************************\n\r");
	xil_printf("*Current Resolution: %28s*\n\r", dispCtrl.vMode.label);
	printf("*Pixel Clock Freq. (MHz): %23.3f*\n\r", dispCtrl.pxlFreq);
	xil_printf("**********************************************************\n\r");
	xil_printf("\n\r");
	xil_printf("1 - %s\n\r", VMODE_640x480.label);
	xil_printf("2 - %s\n\r", VMODE_800x600.label);
	xil_printf("3 - %s\n\r", VMODE_1280x720.label);
	xil_printf("4 - %s\n\r", VMODE_1280x1024.label);
	xil_printf("5 - %s\n\r", VMODE_1600x900.label);
	xil_printf("6 - %s\n\r", VMODE_1920x1080.label);
	xil_printf("q - Quit (don't change resolution)\n\r");
	xil_printf("\n\r");
	xil_printf("Select a new resolution:");
}

//filter menu
void ChangeFilter()
{
	int fResSet = 0;
	int status;
	char userInput = 0;

	 //Flush UART FIFO
	while (XUartPs_IsReceiveData(UART_BASEADDR))
	{
		XUartPs_ReadReg(UART_BASEADDR, XUARTPS_FIFO_OFFSET);
	}

	while (!fResSet)
	{
		int nextFrame=0;
		FilterMenu();

		 //Wait for data on UART
		while (!XUartPs_IsReceiveData(UART_BASEADDR))
		{}

		 //Store the first character in the UART recieve FIFO and echo it
		userInput = XUartPs_ReadReg(UART_BASEADDR, XUARTPS_FIFO_OFFSET);
		xil_printf("%c", userInput);
		status = XST_SUCCESS;
		switch (userInput)
		{
		case '1':
			swValue = *(unsigned int*)0x43C30000; // Read the current switch state

			Xil_DCacheDisable();
			nextFrame = DemoGetInactiveFrame(&dispCtrl, &videoCapt);

			if (nextFrame == -1) {
				xil_printf("Error: No inactive frame buffer available.\n");
				break; // Skip processing and continue
			}

			VideoStop(&videoCapt);
			Grayscale(pFrames[videoCapt.curFrame], pFrames[nextFrame], videoCapt.timing.HActiveVideo, videoCapt.timing.VActiveVideo, DEMO_STRIDE);
			VideoStart(&videoCapt);
			DisplayChangeFrame(&dispCtrl, nextFrame);
			Xil_DCacheEnable();
			fResSet = 1;
			break;
		case '2':
			swValue = *(unsigned int*)0x43C30000; // Read the current switch state

			Xil_DCacheDisable();
			nextFrame = DemoGetInactiveFrame(&dispCtrl, &videoCapt);

			if (nextFrame == -1) {
				xil_printf("Error: No inactive frame buffer available.\n");
				break; // Skip processing and continue
			}

			VideoStop(&videoCapt);
			SobelFilter(pFrames[videoCapt.curFrame], pFrames[nextFrame], videoCapt.timing.HActiveVideo, videoCapt.timing.VActiveVideo, DEMO_STRIDE, filterThreshold);
			VideoStart(&videoCapt);
			DisplayChangeFrame(&dispCtrl, nextFrame);
			Xil_DCacheEnable();
			fResSet = 1;
			break;
		case '3':
			swValue = *(unsigned int*)0x43C30000; // Read the current switch state

			Xil_DCacheDisable();
			nextFrame = DemoGetInactiveFrame(&dispCtrl, &videoCapt);

			if (nextFrame == -1) {
				xil_printf("Error: No inactive frame buffer available.\n");
				break; // Skip processing and continue
			}

			VideoStop(&videoCapt);
			RobertCrossFilter(pFrames[videoCapt.curFrame], pFrames[nextFrame], videoCapt.timing.HActiveVideo, videoCapt.timing.VActiveVideo, DEMO_STRIDE, filterThreshold);
			VideoStart(&videoCapt);
			DisplayChangeFrame(&dispCtrl, nextFrame);
			Xil_DCacheEnable();
			fResSet = 1;
			break;
		case '4':
			swValue = *(unsigned int*)0x43C30000; // Read the current switch state

			Xil_DCacheDisable();
			nextFrame = DemoGetInactiveFrame(&dispCtrl, &videoCapt);

			if (nextFrame == -1) {
				xil_printf("Error: No inactive frame buffer available.\n");
				break; // Skip processing and continue
			}

			VideoStop(&videoCapt);
			PrewittFilter(pFrames[videoCapt.curFrame], pFrames[nextFrame], videoCapt.timing.HActiveVideo, videoCapt.timing.VActiveVideo, DEMO_STRIDE, filterThreshold);
			VideoStart(&videoCapt);
			DisplayChangeFrame(&dispCtrl, nextFrame);
			Xil_DCacheEnable();
			fResSet = 1;
			break;
		case '5':
			swValue = *(unsigned int*)0x43C30000; // Read the current switch state

			Xil_DCacheDisable();
			nextFrame = DemoGetInactiveFrame(&dispCtrl, &videoCapt);

			if (nextFrame == -1) {
				xil_printf("Error: No inactive frame buffer available.\n");
				break; // Skip processing and continue
			}

			VideoStop(&videoCapt);
			//InvertFrame(pFrames[videoCapt.curFrame], pFrames[nextFrame], videoCapt.timing.HActiveVideo, videoCapt.timing.VActiveVideo, DEMO_STRIDE);
			InvertFrame(pFrames[videoCapt.curFrame], pFrames[nextFrame], videoCapt.timing.HActiveVideo, videoCapt.timing.VActiveVideo, DEMO_STRIDE, filterThreshold);
			VideoStart(&videoCapt);
			DisplayChangeFrame(&dispCtrl, nextFrame);
			Xil_DCacheEnable();
			fResSet = 1;
			break;
		case 'q':
			fResSet = 1;
			break;
		default :
			xil_printf("\n\rInvalid Selection");
			TimerDelay(500000);
		}
		if (status == XST_DMA_ERROR)
		{
			xil_printf("\n\rWARNING: AXI VDMA Error detected and cleared\n\r");
		}
	}
}

void FilterMenu()
{
	xil_printf("\x1B[H"); //Set cursor to top left of terminal
	xil_printf("\x1B[2J"); //Clear terminal
	xil_printf("**********************************************************\n\r");
	xil_printf("*               Hunter's ZYBO Video Demo                 *\n\r");
	xil_printf("**********************************************************\n\r");
	xil_printf("*Current Resolution: %28s*\n\r", dispCtrl.vMode.label);
	printf("*Pixel Clock Freq. (MHz): %23.3f*\n\r", dispCtrl.pxlFreq);
	xil_printf("**********************************************************\n\r");
	xil_printf("\n\r");
	xil_printf("1 - Grayscale\n\r");
	xil_printf("2 - Sobel\n\r");
	xil_printf("3 - Robert Cross\n\r");
	xil_printf("4 - Prewitt\n\r");
	xil_printf("5 - Invert\n\r");
	xil_printf("q - Quit (don't change filter)\n\r");
	xil_printf("\n\r");
	xil_printf("Select a filter:");
}

/*void Grayscale(u8 *srcFrame, u8 *destFrame, u32 width, u32 height, u32 stride)
{
	u32 xcoi, ycoi;
	u32 lineStart = 0;
	u8 gray;

	int a[3][3];
	uint8_t* write_pixel_point;
	uint8_t* read_pixel_point;
	int g_x = 0, g_y = 0;
	int i, j;

	Xil_DCacheInvalidateRange((unsigned int) srcFrame, DEMO_MAX_FRAME);

	for(ycoi = 0; ycoi < height; ycoi++)
	{
		for(xcoi = 0; xcoi < width; xcoi++)
		{
			//read_pixel_point = (uint8_t*)(destFrame + (ycoi * 1280 + xcoi) * 3);
			read_pixel_point = (uint8_t *)(srcFrame + ((ycoi + i - 1) * stride) + ((xcoi + j - 1) * 3));

			     //3x3 grayscale
			    for (i = 0; i < 3; i++)
			    {
			        for (j = 0; j < 3; j++)
			        {
			            //write_pixel_point = (uint8_t*)(srcFrame + ((ycoi + i - 1) * 2 * 1280 + (xcoi + j - 1) * 2) * 3);
			        	write_pixel_point = (uint8_t *)(destFrame + (ycoi * stride) + (xcoi * 3));

			            a[i][j] = (write_pixel_point[0] * 7471 +     //blue
			            		write_pixel_point[1] * 38470 +       //green
								write_pixel_point[2] * 19595)        //red
			                   >> 16;
			        }
			    }

			     //Gradient vector
			    g_x = - a[0][0] + a[0][2]
			          - a[1][0] + a[1][2]
			          - a[2][0] + a[2][2];

			    g_y = - a[0][0] + a[2][0]
			          - a[0][1] + a[2][1]
			          - a[0][2] + a[2][2];

			     //Norm
			    //gray = (g_x * g_x + g_y * g_y) >> 4;
			    gray = (int)sqrt((double)(g_x * g_x + g_y * g_y));


			    read_pixel_point[0] = gray;         //blue
			    read_pixel_point[1] = gray;         //green
			    read_pixel_point[2] = gray;         //red
		}
		lineStart += stride;
	}

	 //Flush the framebuffer memory range to ensure changes are written to the
	 //actual memory, and therefore accessible by the VDMA.

	Xil_DCacheFlushRange((unsigned int) destFrame, DEMO_MAX_FRAME);
}*/

void Grayscale(u8 *srcFrame, u8 *destFrame, u32 width, u32 height, u32 stride)
{
    u32 xcoi, ycoi; // Loop variables
    u8 gray;        // Grayscale intensity
    uint8_t* read_pixel_point;
    uint8_t* write_pixel_point;

    // Invalidate the source frame cache to ensure consistency
    Xil_DCacheInvalidateRange((unsigned int)srcFrame, DEMO_MAX_FRAME);

    for (ycoi = 0; ycoi < height; ycoi++)
    {
        for (xcoi = 0; xcoi < width; xcoi++)
        {
            // Read the source pixel (3 bytes: B, G, R)
            read_pixel_point = (uint8_t*)(srcFrame + (ycoi * stride + xcoi) * 3);

            // Calculate grayscale intensity using weighted formula
            gray = (read_pixel_point[0] * 7471 +     // Blue
                    read_pixel_point[1] * 38470 +    // Green
                    read_pixel_point[2] * 19595)    // Red
                   >> 16;

            // Write the grayscale value to the destination pixel
            write_pixel_point = (uint8_t*)(destFrame + (ycoi * stride + xcoi) * 3);
            write_pixel_point[0] = gray;  // Blue channel
            write_pixel_point[1] = gray;  // Green channel
            write_pixel_point[2] = gray;  // Red channel
        }
    }

    // Flush the destination frame cache to ensure changes are written back to memory
    Xil_DCacheFlushRange((unsigned int)destFrame, DEMO_MAX_FRAME);
}

void InvertFrame(u8 *srcFrame, u8 *destFrame, u32 width, u32 height, u32 stride, int threshold)
{
	u32 xcoi, ycoi;
	u32 lineStart = 0;
	Xil_DCacheInvalidateRange((unsigned int) srcFrame, DEMO_MAX_FRAME);
	for(ycoi = 0; ycoi < height; ycoi++)
	{
		for(xcoi = 0; xcoi < (width * 3); xcoi+=3)
		{
			destFrame[xcoi + lineStart] = ~srcFrame[xcoi + lineStart];         //Red
			destFrame[xcoi + lineStart + 1] = ~srcFrame[xcoi + lineStart + 1]; //Blue
			destFrame[xcoi + lineStart + 2] = ~srcFrame[xcoi + lineStart + 2]; //Green
		}
		lineStart += stride;
	}
	/*
	 * Flush the framebuffer memory range to ensure changes are written to the
	 * actual memory, and therefore accessible by the VDMA.
	 */
	Xil_DCacheFlushRange((unsigned int) destFrame, DEMO_MAX_FRAME);
}



void SobelFilter(u8 *srcFrame, u8 *destFrame, u32 width, u32 height, u32 stride, int threshold)
{
    u32 x, y;
    int g_x, g_y, gray;
    uint8_t *write_pixel_point, *read_pixel_point;
    int a[3][3]; // Matrix for 3x3 pixel values
    int i, j;

    // Invalidate the cache for the source frame
    Xil_DCacheInvalidateRange((unsigned int)srcFrame, DEMO_MAX_FRAME);

    for (y = 1; y < height - 1; y++) { // Skip the top and bottom rows
        for (x = 1; x < width - 1; x++) { // Skip the left and right columns
            // Load 3x3 pixel values into the matrix
            for (i = 0; i < 3; i++) {
                for (j = 0; j < 3; j++) {
                    read_pixel_point = (uint8_t *)(srcFrame + ((y + i - 1) * stride) + ((x + j - 1) * 3));
                    a[i][j] = (read_pixel_point[0] * 7471 +     //Blue
                               read_pixel_point[1] * 38470 +    //Green
                               read_pixel_point[2] * 19595) >> 16;  //Red
                }
            }

            // Apply Sobel kernels
            g_x = -a[0][0] + a[0][2]
                  -2 * a[1][0] + 2 * a[1][2]
                  -a[2][0] + a[2][2];

            g_y = -a[0][0] - 2 * a[0][1] - a[0][2]
                  +a[2][0] + 2 * a[2][1] + a[2][2];

            // Compute the gradient magnitude using square root
            gray = (int)sqrt((double)(g_x * g_x + g_y * g_y));

            // Apply threshold: set to 0 if below threshold
            gray = (gray >= threshold) ? gray : 0;

            // Clamp to [0, 255]
            gray = (gray > 255) ? 255 : gray;

            // Write the result to the destination frame
            write_pixel_point = (uint8_t *)(destFrame + (y * stride) + (x * 3));
            write_pixel_point[0] = gray; // Blue
            write_pixel_point[1] = gray; // Green
            write_pixel_point[2] = gray; // Red
        }
    }

    // Flush the cache for the destination frame
    Xil_DCacheFlushRange((unsigned int)destFrame, DEMO_MAX_FRAME);
}


void RobertCrossFilter(u8 *srcFrame, u8 *destFrame, u32 width, u32 height, u32 stride, int threshold)
{
    u32 x, y;
    int g_x, g_y, gray;
    uint8_t *write_pixel_point, *read_pixel_point;
    int a[2][2]; // Matrix for 2x2 pixel values
    int i, j;

    Xil_DCacheInvalidateRange((unsigned int)srcFrame, DEMO_MAX_FRAME);

    for (y = 0; y < height - 1; y++) // Stop 1 pixel before the bottom
    {
        for (x = 0; x < width - 1; x++) // Stop 1 pixel before the right edge
        {
            // Load 2x2 pixel values into the matrix
            for (i = 0; i < 2; i++)
            {
                for (j = 0; j < 2; j++)
                {
                    read_pixel_point = (uint8_t *)(srcFrame + ((y + i) * stride) + ((x + j) * 3));
                    a[i][j] = (read_pixel_point[0] * 7471 +     //Blue
                               read_pixel_point[1] * 38470 +    //Green
                               read_pixel_point[2] * 19595) >> 16;  //Red
                }
            }

            // Apply Robert Cross kernels
            g_x = a[0][0] - a[1][1];
            g_y = a[0][1] - a[1][0];

            // Fast gradient approximation
            int maxGrad = (abs(g_x) > abs(g_y)) ? abs(g_x) : abs(g_y);
            int minGrad = (abs(g_x) < abs(g_y)) ? abs(g_x) : abs(g_y);
            gray = (3 * maxGrad + minGrad) >> 2; // Equivalent to 0.75*max + 0.25*min

            // Compute the gradient magnitude using square root
            gray = (int)sqrt((double)(g_x * g_x + g_y * g_y));

            // Apply threshold: set to 0 if below threshold
            gray = (gray >= threshold) ? gray : 0;

            // Clamp to [0, 255]
            gray = (gray > 255) ? 255 : gray;

            // Write the result to the destination frame
            write_pixel_point = (uint8_t *)(destFrame + (y * stride) + (x * 3));
            write_pixel_point[0] = gray; // Blue
            write_pixel_point[1] = gray; // Green
            write_pixel_point[2] = gray; // Red
        }
    }

    Xil_DCacheFlushRange((unsigned int)destFrame, DEMO_MAX_FRAME);
}

void PrewittFilter(u8 *srcFrame, u8 *destFrame, u32 width, u32 height, u32 stride, int threshold)
{
    u32 x, y;
    int g_x, g_y, gray;
    uint8_t *write_pixel_point, *read_pixel_point;
    int a[3][3]; // Matrix for 3x3 pixel values
    int i, j;

    Xil_DCacheInvalidateRange((unsigned int)srcFrame, DEMO_MAX_FRAME);

    for (y = 1; y < height - 1; y++) // Skip the top and bottom rows
    {
        for (x = 1; x < width - 1; x++) // Skip the left and right columns
        {
            // Load 3x3 pixel values into the matrix
            for (i = 0; i < 3; i++)
            {
                for (j = 0; j < 3; j++)
                {
                    read_pixel_point = (uint8_t *)(srcFrame + ((y + i - 1) * stride) + ((x + j - 1) * 3));
                    a[i][j] = (read_pixel_point[0] * 7471 +     //Blue
                               read_pixel_point[1] * 38470 +    //Green
                               read_pixel_point[2] * 19595) >> 16;  //Red
                }
            }

            // Apply Prewitt kernels
            g_x = -a[0][0] + a[0][2]
                  -a[1][0] + a[1][2]
                  -a[2][0] + a[2][2];

            g_y = -a[0][0] - a[0][1] - a[0][2]
                  +a[2][0] + a[2][1] + a[2][2];

            // Fast gradient approximation
            int maxGrad = (abs(g_x) > abs(g_y)) ? abs(g_x) : abs(g_y);
            int minGrad = (abs(g_x) < abs(g_y)) ? abs(g_x) : abs(g_y);
            gray = (3 * maxGrad + minGrad) >> 2; // Equivalent to 0.75*max + 0.25*min

            // Compute the gradient magnitude using square root
            gray = (int)sqrt((double)(g_x * g_x + g_y * g_y));

            // Apply threshold: set to 0 if below threshold
            gray = (gray >= threshold) ? gray : 0;

            // Clamp to [0, 255]
            gray = (gray > 255) ? 255 : gray;

            // Write the result to the destination frame
            write_pixel_point = (uint8_t *)(destFrame + (y * stride) + (x * 3));
            write_pixel_point[0] = gray; // Blue
            write_pixel_point[1] = gray; // Green
            write_pixel_point[2] = gray; // Red
        }
    }

    Xil_DCacheFlushRange((unsigned int)destFrame, DEMO_MAX_FRAME);
}

void DemoScaleFrame(u8 *srcFrame, u8 *destFrame, u32 srcWidth, u32 srcHeight, u32 destWidth, u32 destHeight, u32 stride)
{
	float xInc, yInc; // Width/height of a destination frame pixel in the source frame coordinate system
	float xcoSrc, ycoSrc; // Location of the destination pixel being operated on in the source frame coordinate system
	float x1y1, x2y1, x1y2, x2y2; //Used to store the color data of the four nearest source pixels to the destination pixel
	int ix1y1, ix2y1, ix1y2, ix2y2; //indexes into the source frame for the four nearest source pixels to the destination pixel
	float xDist, yDist; //distances between destination pixel and x1y1 source pixels in source frame coordinate system

	int xcoDest, ycoDest; // Location of the destination pixel being operated on in the destination coordinate system
	int iy1; //Used to store the index of the first source pixel in the line with y1
	int iDest; //index of the pixel data in the destination frame being operated on

	int i;

	xInc = ((float) srcWidth - 1.0) / ((float) destWidth);
	yInc = ((float) srcHeight - 1.0) / ((float) destHeight);

	ycoSrc = 0.0;
	for (ycoDest = 0; ycoDest < destHeight; ycoDest++)
	{
		iy1 = ((int) ycoSrc) * stride;
		yDist = ycoSrc - ((float) ((int) ycoSrc));


		 //Save some cycles in the loop below by presetting the destination
		 //index to the first pixel in the current line

		iDest = ycoDest * stride;

		xcoSrc = 0.0;
		for (xcoDest = 0; xcoDest < destWidth; xcoDest++)
		{
			ix1y1 = iy1 + ((int) xcoSrc) * 3;
			ix2y1 = ix1y1 + 3;
			ix1y2 = ix1y1 + stride;
			ix2y2 = ix1y1 + stride + 3;

			xDist = xcoSrc - ((float) ((int) xcoSrc));


			 //For loop handles all three colors

			for (i = 0; i < 3; i++)
			{
				x1y1 = (float) srcFrame[ix1y1 + i];
				x2y1 = (float) srcFrame[ix2y1 + i];
				x1y2 = (float) srcFrame[ix1y2 + i];
				x2y2 = (float) srcFrame[ix2y2 + i];


				 //Bilinear interpolation function

				destFrame[iDest] = (u8) ((1.0-yDist)*((1.0-xDist)*x1y1+xDist*x2y1) + yDist*((1.0-xDist)*x1y2+xDist*x2y2));
				iDest++;
			}
			xcoSrc += xInc;
		}
		ycoSrc += yInc;
	}


	 //Flush the framebuffer memory range to ensure changes are written to the
	 //actual memory, and therefore accessible by the VDMA.

	Xil_DCacheFlushRange((unsigned int) destFrame, DEMO_MAX_FRAME);

	return;
}

void DemoPrintTest(u8 *frame, u32 width, u32 height, u32 stride, int pattern)
{
	u32 xcoi, ycoi;
	u32 iPixelAddr;
	u8 wRed, wBlue, wGreen;
	u32 wCurrentInt;
	double fRed, fBlue, fGreen, fColor;
	u32 xLeft, xMid, xRight, xInt;
	u32 yMid, yInt;
	double xInc, yInc;


	switch (pattern)
	{
	case DEMO_PATTERN_0:

		xInt = width / 4; //Four intervals, each with width/4 pixels
		xLeft = xInt * 3;
		xMid = xInt * 2 * 3;
		xRight = xInt * 3 * 3;
		xInc = 256.0 / ((double) xInt); //256 color intensities are cycled through per interval (overflow must be caught when color=256.0)

		yInt = height / 2; //Two intervals, each with width/2 lines
		yMid = yInt;
		yInc = 256.0 / ((double) yInt); //256 color intensities are cycled through per interval (overflow must be caught when color=256.0)

		fBlue = 0.0;
		fRed = 256.0;
		for(xcoi = 0; xcoi < (width*3); xcoi+=3)
		{

			 //Convert color intensities to integers < 256, and trim values >=256

			wRed = (fRed >= 256.0) ? 255 : ((u8) fRed);
			wBlue = (fBlue >= 256.0) ? 255 : ((u8) fBlue);
			iPixelAddr = xcoi;
			fGreen = 0.0;
			for(ycoi = 0; ycoi < height; ycoi++)
			{

				wGreen = (fGreen >= 256.0) ? 255 : ((u8) fGreen);
				frame[iPixelAddr] = wRed;
				frame[iPixelAddr + 1] = wBlue;
				frame[iPixelAddr + 2] = wGreen;
				if (ycoi < yMid)
				{
					fGreen += yInc;
				}
				else
				{
					fGreen -= yInc;
				}


				 //This pattern is printed one vertical line at a time, so the address must be incremented
				 //by the stride instead of just 1.

				iPixelAddr += stride;
			}

			if (xcoi < xLeft)
			{
				fBlue = 0.0;
				fRed -= xInc;
			}
			else if (xcoi < xMid)
			{
				fBlue += xInc;
				fRed += xInc;
			}
			else if (xcoi < xRight)
			{
				fBlue -= xInc;
				fRed -= xInc;
			}
			else
			{
				fBlue += xInc;
				fRed = 0;
			}
		}

		 //Flush the framebuffer memory range to ensure changes are written to the
		 //actual memory, and therefore accessible by the VDMA.

		Xil_DCacheFlushRange((unsigned int) frame, DEMO_MAX_FRAME);
		break;
	case DEMO_PATTERN_1:

		xInt = width / 7; //Seven intervals, each with width/7 pixels
		xInc = 256.0 / ((double) xInt); //256 color intensities per interval. Notice that overflow is handled for this pattern.

		fColor = 0.0;
		wCurrentInt = 1;
		for(xcoi = 0; xcoi < (width*3); xcoi+=3)
		{


			 //Just draw white in the last partial interval (when width is not divisible by 7)

			if (wCurrentInt > 7)
			{
				wRed = 255;
				wBlue = 255;
				wGreen = 255;
			}
			else
			{
				if (wCurrentInt & 0b001)
					wRed = (u8) fColor;
				else
					wRed = 0;

				if (wCurrentInt & 0b010)
					wBlue = (u8) fColor;
				else
					wBlue = 0;

				if (wCurrentInt & 0b100)
					wGreen = (u8) fColor;
				else
					wGreen = 0;
			}

			iPixelAddr = xcoi;

			for(ycoi = 0; ycoi < height; ycoi++)
			{
				frame[iPixelAddr] = wRed;
				frame[iPixelAddr + 1] = wBlue;
				frame[iPixelAddr + 2] = wGreen;

				 //This pattern is printed one vertical line at a time, so the address must be incremented
				 //by the stride instead of just 1.

				iPixelAddr += stride;
			}

			fColor += xInc;
			if (fColor >= 256.0)
			{
				fColor = 0.0;
				wCurrentInt++;
			}
		}

		 //Flush the framebuffer memory range to ensure changes are written to the
		 //actual memory, and therefore accessible by the VDMA.

		Xil_DCacheFlushRange((unsigned int) frame, DEMO_MAX_FRAME);
		break;
	default :
		xil_printf("Error: invalid pattern passed to DemoPrintTest");
	}
}

int DemoGetInactiveFrame(DisplayCtrl *DispCtrlPtr, VideoCapture *VideoCaptPtr)
{
	int i;
	for (i=1; i<DISPLAY_NUM_FRAMES; i++)
	{
		if (DispCtrlPtr->curFrame == i && DispCtrlPtr->state == DISPLAY_RUNNING)
		{
			continue;
		}
		else if (VideoCaptPtr->curFrame == i && VideoCaptPtr->state == VIDEO_STREAMING)
		{
			continue;
		}
		else
		{
			return i;
		}
	}
	xil_printf("Unreachable error state reached. All buffers are in use.\r\n");
	return -1;
}

void DemoISR(void *callBackRef, void *pVideo)
{
	char *data = (char *) callBackRef;
	*data = 1; //set fRefresh to 1
}
