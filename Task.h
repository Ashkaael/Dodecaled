
#include <stdint.h>
#include <WS2812FX.h>

//#include <WiFi.h>
//#include <ESPmDNS.h>
//#include <WiFiUdp.h>
//#include <ArduinoOTA.h>
#include "WifiConParam.h"

//#include <iostream> 
#include <list>
#include <cmath>
#include <iterator> 
using namespace std;

#include "BasicFct_cl.h"
#include "Encoder_cl.h"
#include "Led_cl.h"
#include "Strip_cl.h"
#include "Effect.h"

WS2812FX ws2812fx[7] = {
WS2812FX(0,0,NEO_GRB + NEO_KHZ800),
WS2812FX(120, /*13*/23, NEO_GRB + NEO_KHZ800),
WS2812FX(120, /*12*/21, NEO_GRB + NEO_KHZ800),
WS2812FX(120, /*14*/18, NEO_GRB + NEO_KHZ800),
WS2812FX(120, /*27*/5, NEO_GRB + NEO_KHZ800),
WS2812FX(120, /*15*/17, NEO_GRB + NEO_KHZ800),
WS2812FX(120, /* 2*/16, NEO_GRB + NEO_KHZ800),
};


// Custom show functions which will use the RMT hardware to drive the LEDs.
// Need a separate function for each ws2812fx instance.
void myCustomShow1(void) {
	uint8_t* pixels = ws2812fx[1].getPixels();
	// numBytes is one more then the size of the ws2812fx's *pixels array.
	// the extra byte is used by the driver to insert the LED reset pulse at the end.
	uint16_t numBytes = ws2812fx[1].getNumBytes() + 1;
	rmt_write_sample(RMT_CHANNEL_1, pixels, numBytes, false);
}
void myCustomShow2(void) {
	uint8_t* pixels = ws2812fx[2].getPixels();
	// numBytes is one more then the size of the ws2812fx's *pixels array.
	// the extra byte is used by the driver to insert the LED reset pulse at the end.
	uint16_t numBytes = ws2812fx[2].getNumBytes() + 1;
	rmt_write_sample(RMT_CHANNEL_2, pixels, numBytes, false); // channel 0
}
void myCustomShow3(void) {
	uint8_t* pixels = ws2812fx[3].getPixels();
	// numBytes is one more then the size of the ws2812fx's *pixels array.
	// the extra byte is used by the driver to insert the LED reset pulse at the end.
	uint16_t numBytes = ws2812fx[3].getNumBytes() + 1;
	rmt_write_sample(RMT_CHANNEL_3, pixels, numBytes, false); // channel 0
}
void myCustomShow4(void) {
	uint8_t* pixels = ws2812fx[4].getPixels();
	// numBytes is one more then the size of the ws2812fx's *pixels array.
	// the extra byte is used by the driver to insert the LED reset pulse at the end.
	uint16_t numBytes = ws2812fx[4].getNumBytes() + 1;
	rmt_write_sample(RMT_CHANNEL_4, pixels, numBytes, false); // channel 0
}
void myCustomShow5(void) {
	uint8_t* pixels = ws2812fx[5].getPixels();
	// numBytes is one more then the size of the ws2812fx's *pixels array.
	// the extra byte is used by the driver to insert the LED reset pulse at the end.
	uint16_t numBytes = ws2812fx[5].getNumBytes() + 1;
	rmt_write_sample(RMT_CHANNEL_5, pixels, numBytes, false); // channel 0
}
void myCustomShow6(void) {
	uint8_t* pixels = ws2812fx[6].getPixels();
	// numBytes is one more then the size of the ws2812fx's *pixels array.
	// the extra byte is used by the driver to insert the LED reset pulse at the end.
	uint16_t numBytes = ws2812fx[6].getNumBytes() + 1;
	rmt_write_sample(RMT_CHANNEL_6, pixels, numBytes, false); // channel 0
}


//Class encorder
Encoder_cl EncPrm("Encoder Param", 8, 7, 13, 0, 100, 1, false);
Encoder_cl EncBrigh("Encoder Brightness", 0, 2, 15, 1, 255, 1, false);
Encoder_cl EncPrg("Encoder Programme", 8, 7, 13, 0, 119, 1, true);

//Class Strip
Strip_cl Strip[31]= {
	Strip_cl( 0, 0, 0, false, 0, 0, 0, 0),
	Strip_cl( 1, 1, 1, false, 2, 3, 4, 9),
	Strip_cl( 2, 2, 1, false, 3, 1, 6, 5),
	Strip_cl( 3, 3, 1, false, 1, 2, 8, 7),
	Strip_cl( 4, 4, 1, false, 1, 9,10,13),
	Strip_cl( 5, 2, 2, false, 6, 2,14,10),
	Strip_cl( 6, 5, 1, false, 2, 5,11,15),
	Strip_cl( 7, 3, 2, false, 8, 3,16,11),
	Strip_cl( 8, 6, 1, false, 3, 7,12,17),
	Strip_cl( 9, 1, 2, false, 4, 1,18,12),
	Strip_cl(10, 4, 2, false, 4,13, 5,14),
	Strip_cl(11, 5, 2, false, 6,15, 7,16),
	Strip_cl(12, 6, 2, false, 8,17, 9,18),
	Strip_cl(13, 4, 3, false,10, 4,22,21),
	Strip_cl(14, 2, 3, false, 5,10,19,23),
	Strip_cl(15, 5, 3, false,11, 6,24,19),
	Strip_cl(16, 3, 3, false, 7,11,20,25),
	Strip_cl(17, 6, 3, false,12, 8,26,20),
	Strip_cl(18, 1, 3, false, 9,12,21,27),
	Strip_cl(19, 5, 5,  true,14,23,15,24),
	Strip_cl(20, 6, 5,  true,25,16,26,17),
	Strip_cl(21, 4, 5,  true,18,27,13,22),
	Strip_cl(22, 4, 4, false,13,21,23,28),
	Strip_cl(23, 2, 4, false,19,14,28,22),
	Strip_cl(24, 5, 4, false,15,19,25,29),
	Strip_cl(25, 3, 4, false,20,16,29,24),
	Strip_cl(26, 6, 4, false,17,20,27,30),
	Strip_cl(27, 1, 4, false,21,18,30,26),
	Strip_cl(28, 2, 5, false,23,22,29,30),
	Strip_cl(29, 3, 5, false,25,24,30,28),
	Strip_cl(30, 1, 5, false,27,26,28,29)
};


list <Cursor_cl> cursorList;
list <FadeEffect_cl> FadeEffectList;
vector <FadeEffect_cl> vect1;
vector <FadeEffect_cl*> vect2;

//***************************** Variable de travail ********************************
int Ind=1;
float IndR = 1;
bool IsCompleted = 0;
unsigned long InitTime;
unsigned long Time1,Time2,Time3,Time4;
unsigned long TimeElapsed1, MemTimeElapsed1;


void test1()
{
	
	AnimBuilInLed();

	//EncPrm.RefreshEncVal();
	EncBrigh.RefreshEncVal();
	EncPrg.RefreshEncVal();
	
	//Serial.println(Strip[11].StripBus)

	if ((micros() - Time1) > 5000000) {Time1 = micros();  Ind++;
	//Strip[1].Led[15].InitFadeEffect(RED, 1000, 1000, 1000);
	//Serial.println("init");
	}
	if (Ind > 30) { Ind = 1; };

	for (int i = 1; i <= 30; i++) {
		if (Strip[i].StripBus != 0) {
			Strip[i].SetLedsColor(BLACK);
		}
			
	}

	//Strip[Ind].SetLedsColor(GREEN);

	
	Time2 = micros();
	
	
	list <Cursor_cl> ::iterator it;
	for (it = cursorList.begin(); it != cursorList.end(); ++it)
	{
		it->Refresh(Strip);
		it->AddEffect(Strip, &vect2, 2);
	}
	
	/*
	for (int i = cursorList.size() - 1; i >= 0; i--) {
		cursorList[i]->Refresh(Strip);
	}
	*/

	//Refresh Leds effect
	TimeElapsed1 = micros() - MemTimeElapsed1;
	MemTimeElapsed1 = micros();

	list <FadeEffect_cl> ::iterator it2;
	for (it2 = FadeEffectList.begin(); it2 != FadeEffectList.end(); ++it2)
	{

		//IsCompleted = it2->RefreshEffect(Strip, TimeElapsed1);
		//if (IsCompleted) { delete it2; };
	}

	//for (vect1 : vector)

	

	
	for (int i = vect2.size() - 1; i >= 0; i--) {
		//vect2[i].test1();
		if (vect2[i]->RunEffect(Strip,TimeElapsed1)) {
			delete vect2[i];
			vect2.erase(vect2.begin() + i);
		}
	}
	
	//FadeEffect_cl* p = new FadeEffect_cl(1, 22, GREEN, 600, 0, 600, 0);
	//vect2.push_back(p);
	Serial.println(vect2.size());

	/*
	list <FadeEffect_cl> ::iterator it2;
	for (it2 = FadeEffectList.begin(); it2 != FadeEffectList.end(); ++it2)
	{
		IsCompleted = it2->RefreshEffect(Strip,TimeElapsed1);
		//if (IsCompleted) { delete it2; };
	}
	*/


	
	
	
	//if (EncPrg.IsActPosChanged()) {
	//	Serial.println(Strip[EncPrg.GetEncPos()].StripNbr);
	//}
	

	IndR= IndR + 0.025;

	if (IndR > 24) { IndR= 1; }
	
	for (int i = 1; i <= 30; i++) {
		for (int i2 = 1; i2 <= 24; i2++) {
			Strip[i].Led[i2].SetColor(BLACK);
		}
	}

	

		for (int i2 = 1; i2 <= 24; i2++) {
			Strip[(int)IndR].Led[i2].SetColor(ORANGE);
		}

	
		 

	//Serial.print(" T2:"); Serial.println(micros() - Time2);
	Serial.print(" T3:"); Serial.println(micros() - Time3);
	Time3 = micros();

	//Rendering 
	for (int i = 1; i <= 30; i++) {
		for (int i2 = 1; i2 <= 24; i2++) {
			if (Strip[i].RevertRenderingOrder) {
				ws2812fx[Strip[i].StripBus].
				setPixelColor( 24 -i2 + (Strip[i].StripBusSeg - 1) * 24, Strip[i].Led[i2].Color);
			}
			else {
				ws2812fx[Strip[i].StripBus].
				setPixelColor(i2 - 1 + (Strip[i].StripBusSeg - 1) * 24, Strip[i].Led[i2].Color);
			}
			
		}
	}
	for (int i = 1; i <= 6; i++) {
		//ws2812fx[i].setBrightness(EncBrigh.GetEncPos() * 1);
		ws2812fx[i].show();
	}
	
}



void TaskSetup()
{
	pinMode(12, OUTPUT);

	cursorList.push_back(Cursor_cl(1, 5, 2, 80, BLUE));
	//cursorList.push_back(Cursor_cl(2,5,2,80, PURPLE));
	//cursorList.push_back(Cursor_cl(3, 5, 2, 80, YELLOW));
	//cursorList.push_back(Cursor_cl(3, 5, 2, 80, ORANGE));
	cursorList.push_back(Cursor_cl(3, 5, 2, 80, GREEN));

	//vect1.push_back(FadeEffect_cl(1, 22, GREEN, 600, 0, 600, 0));

	/*
	FadeEffect_cl* p0 = new FadeEffect_cl(1, 22, GREEN, 2600, 0, 2600, 0);
	vect2.push_back(p0);
	FadeEffect_cl* p1 = new FadeEffect_cl(1, 22, BLUE, 2600, 0, 2600, 0);
	vect2.push_back(p1);
	FadeEffect_cl* p2 = new FadeEffect_cl(1, 21, GREEN, 2600, 0, 2600, 0);
	vect2.push_back(p2);
	FadeEffect_cl* p3 = new FadeEffect_cl(1, 23, BLUE, 2600, 0, 2600, 0);
	vect2.push_back(p3);
	*/

	//WiFi.disconnect();
	//WiFi.mode(WIFI_OFF);
	//esp_wifi_start();

	InitTime = micros();
	Time1 = micros();
	MemTimeElapsed1 = micros();

	Serial.begin(115200);

	for (int i = 1; i <= 6; i++) {
		ws2812fx[i].init();
		ws2812fx[i].begin();
		ws2812fx[i].setBrightness(15);
	}

	rmt_tx_int(RMT_CHANNEL_1, ws2812fx[1].getPin()); // assign ws2812fx1 to RMT channel 
	ws2812fx[1].setCustomShow(myCustomShow1); // set the custom show function to forgo the NeoPixel

	rmt_tx_int(RMT_CHANNEL_2, ws2812fx[2].getPin()); // assign ws2812fx2 to RMT channel 
	ws2812fx[2].setCustomShow(myCustomShow2); // set the custom show function to forgo the NeoPixel

	rmt_tx_int(RMT_CHANNEL_3, ws2812fx[3].getPin()); // assign ws2812fx3 to RMT channel 
	ws2812fx[3].setCustomShow(myCustomShow3);

	rmt_tx_int(RMT_CHANNEL_4, ws2812fx[4].getPin()); // assign ws2812fx4 to RMT channel 
	ws2812fx[4].setCustomShow(myCustomShow4); // set the custom show function to forgo the NeoPixel

	rmt_tx_int(RMT_CHANNEL_5, ws2812fx[5].getPin()); // assign ws2812fx5 to RMT channel 
	ws2812fx[5].setCustomShow(myCustomShow5); // set the custom show function to forgo the NeoPixel

	rmt_tx_int(RMT_CHANNEL_6, ws2812fx[6].getPin()); // assign ws2812fx6 to RMT channel 
	ws2812fx[6].setCustomShow(myCustomShow6); // set the custom show function to forgo the NeoPixel

}

void Task0Core0()
{

}

void Task1Core1()
{

}
