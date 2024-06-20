/*
 * test.c
 *
 *  Created on: 17-Jun-2019
 *      Author: poe
 */

#include "test.h"

#define min(a, b) (((a) < (b)) ? (a) : (b))

void TestLines(uint8 color)
{
    uint8 x1, y1, x2, y2;

    oled_Clear ();

    x1 = y1 = 0;
    y2    = oled_HEIGHT - 1;
    for (x2 = 0; x2 < oled_WIDTH; x2 += 6)
    	{
    		oled_DrawLine(x1, y1, x2, y2, color);
    		STK_delayMs(1);
    		oled_UpdateScreen();
    	}
    x2    = oled_WIDTH - 1;
    for (y2 = 0; y2 < oled_HEIGHT; y2 += 6)
    	{
    		oled_DrawLine(x1, y1, x2, y2, color);
    		STK_delayMs(1);
    		oled_UpdateScreen();
    	}

    STK_delayMs(10);


    oled_Clear ();

    x1    = oled_WIDTH - 1;
    y1    = 0;
    y2    = oled_HEIGHT - 1;
    for (x2 = 0; x2 < oled_WIDTH; x2 += 6)
    	{
    		oled_DrawLine(x1, y1, x2, y2, color);
    		oled_UpdateScreen();
    		STK_delayMs(1);
    	}
    x2    = 0;
    for (y2 = 0; y2 < oled_HEIGHT; y2 += 6)
    	{
    		oled_DrawLine(x1, y1, x2, y2, color);
    		oled_UpdateScreen();
    		STK_delayMs(1);
    	}

    STK_delayMs(10);


    oled_Clear ();

    x1    = 0;
    y1    = oled_HEIGHT - 1;
    y2    = 0;
    for (x2 = 0; x2 < oled_WIDTH; x2 += 6)
    {
    	oled_DrawLine(x1, y1, x2, y2, color);
    	STK_delayMs(1);
    	oled_UpdateScreen();
    }
    x2    = oled_WIDTH - 1;
    for (y2 = 0; y2 < oled_HEIGHT; y2 += 6)
    	{
    		oled_DrawLine(x1, y1, x2, y2, color);
    		STK_delayMs(1);
    		oled_UpdateScreen();
    	}

    STK_delayMs(10);


    oled_Clear ();

    x1    = oled_WIDTH - 1;
    y1    = oled_HEIGHT - 1;
    y2    = 0;
    for (x2 = 0; x2 < oled_WIDTH; x2 += 6)
    	{
    		oled_DrawLine(x1, y1, x2, y2, color);
    		STK_delayMs(1);
    		oled_UpdateScreen();
    	}
    x2    = 0;
    for (y2 = 0; y2 < oled_HEIGHT; y2 += 6)
    	{
    		oled_DrawLine(x1, y1, x2, y2, color);
    		STK_delayMs(1);
    		oled_UpdateScreen();
    	}
}


void TestRectangles (uint8 color)
{
    uint8 n, i, i2;

    oled_Clear ();

    n = min(oled_WIDTH, oled_HEIGHT);

    for (i = 2; i < n; i += 6)
    {
        i2 = i / 2;
        oled_DrawRectangle((oled_WIDTH/2) - i2, (oled_HEIGHT/2) - i2, i, i, color);
        oled_UpdateScreen();
        STK_delayMs (10);
    }
}

void TestFilledRectangles (uint8 color)
{
    uint8 n, i, i2,
            cx = oled_WIDTH / 2 - 1,
            cy = oled_HEIGHT / 2 - 1;

    oled_Clear ();

    n = min(oled_WIDTH, oled_HEIGHT);
    for (i = n; i > 0; i -= 6)
    {
        i2    = i / 2;
        oled_DrawFilledRectangle(cx - i2, cy - i2, i, i, color);
        oled_UpdateScreen();
        STK_delayMs (10);
    }
}

void TestFilledCircles(uint8 radius, uint16 color)
{
    uint8 x, y, w = oled_WIDTH, h = oled_HEIGHT, r2 = radius * 2;

    oled_Clear ();

    for (x = radius; x < w; x += r2)
    {
        for (y = radius; y < h; y += r2)
        {
            oled_DrawFilledCircle(x, y, radius, color);
            oled_UpdateScreen();
            STK_delayMs (10);
        }
    }
}

void TestCircles(uint8 radius, uint16 color)
{
	oled_Clear ();

	uint8 x, y, r2 = radius * 2,
            w = oled_WIDTH + radius,
            h = oled_HEIGHT + radius;

    for (x = 0; x < w; x += r2)
    {
        for (y = 0; y < h; y += r2)
        {
            oled_DrawCircle(x, y, radius, color);
            oled_UpdateScreen();
            STK_delayMs (10);
        }
    }
}

void TestTriangles(uint8 color)
{
    uint8 n, i, cx = oled_WIDTH  / 2 - 1,
            cy = oled_HEIGHT / 2 - 1;

    oled_Clear ();

    n = min(cx, cy);
    for (i = 0; i < n; i += 5)
    {
        oled_DrawTriangle(cx , cy - i, cx - i, cy + i, cx + i, cy + i, color);
        oled_UpdateScreen();
        STK_delayMs (10);
    }

}




