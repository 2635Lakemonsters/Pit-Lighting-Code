#include <bitswap.h>
#include <chipsets.h>
#include <color.h>
#include <colorpalettes.h>
#include <colorutils.h>
#include <controller.h>
#include <dmx.h>
#include <FastLED.h>
#include <fastled_config.h>
#include <fastled_delay.h>
#include <fastled_progmem.h>
#include <fastpin.h>
#include <fastspi.h>
#include <fastspi_bitbang.h>
#include <fastspi_dma.h>
#include <fastspi_nop.h>
#include <fastspi_ref.h>
#include <fastspi_types.h>
#include <hsv2rgb.h>
#include <led_sysdefs.h>
#include <lib8tion.h>
#include <noise.h>
#include <pixeltypes.h>
#include <platforms.h>
#include <power_mgt.h>

//#include <DmxMaster.h>
#include <DmxSimple.h>


void setup() 
{
  //Set the DMX Output Pin. Is 3 by default, but just to be sure
  DmxSimple.usePin(3);

  //Max Number of DMX Channels. If not set, will be set by the highest .write(). 
  //Using 4 lights with 1-8 each, so using 35 for wiggle room
  DmxSimple.maxChannel(35);
}

void loop() 
{
 moodLighting();
 //workLighting();
}

int setColor(int f, int r, int g, int b, int u)
{
  DmxSimple.write(f, r);
  DmxSimple.write(f+1, g);
  DmxSimple.write(f+2, b);
  DmxSimple.write(f+3, u);
}

void moodLighting()
{
  setColor(1, 0, 200, 200, 0);
  setColor(5, 0, 200, 200, 0);
  setColor(9, 0, 200, 200, 0);
  setColor(13, 0, 200, 200, 0);
}

void workLighting()
{
  setColor(1, 255, 255, 255, 0);
  setColor(5, 255, 255, 255, 0);
  setColor(9, 255, 255, 255, 0);
  setColor(13, 255, 255, 255, 0);
}


