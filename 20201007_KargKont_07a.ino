  // Kontroller by Karg (Timm Schlegelmilch) kL
// Control your Kaossilator Pro (+) with standard midi notes
// Detailed instructions are published on:
// http://karg-music.blogspot.de
// Licenced under Creative Commons Attribution-ShareAlike 4.0
// http://creativecommons.org/licenses/by-sa/4.0/
//
//  Note that we are translating notes into coordinates on the touch pad's XY-axis of your Kaossilator Pro (+)
//  This means: - the scale set on the Kaossilator will be respected
//              - the octave range set on the Kaossilator will will modulate the notes played
//              - for a one-to-one musical mapping between key pressed and note played, set the octave range to full on your Kaossilator

///////////////////// Mods to support MEGA 2560 (extra serial ports), Axiom 49 key controller  //sc
///////////////////// set Kaossilator Pro to NOTE RANGE = 4 OCTAVE  //sc
///////////////////// set Kaossilator Pro to SCALE - CHROMATIC  //sc
///////////////////// set Kaossilator Pro to KEY = C 
///////////////////// Derivative mods by Steven Campana https://stevencampana.com/   //sc
///////////////////// Validated on Kaossilator Pro  //sc
///////////////////// xPad values derived from Programming the Midisolutions "Event Processor Plus"   //sc
///////////////////// http://www.midisolutions.com/Kaossilator%20Pro%20Midi.doc      //sc
///////////////////// xPad lookup values have been adjusted to compensate for an unknown non-linearity :) //sc
///////////////////// added pitch wheel values  //sc
///////////////////// added OnControlChange code to support bank LSB changes  //sc
//
/* ---( Config Start - change to your likings )-------------------------------------------------------------------------------- */
//
// un-/comment to enable/disable MIDI DINs and USB
//#define DIN /////////////////////////////////////////////////////////////sc
#define USB                  ////////////////////////////////////////////////////////////sc
#define INPUT_MIDI_CHANNEL	 1 // MIDI channel of the input device (keyboard etc.) sending notes
//
// change the numbers according to the settings in your Kaoss device
#define KAOSS_MIDI_CHANNEL       2      // MIDI channel for the Kaoss device
#define KAOSS_CC_PAD            92      // pad on/off control change # (check the manual for more information) //sc (74 doesn't work)
#define KAOSS_CC_X              12      // pad on/off control change # (check the manual for more information)
#define KAOSS_CC_Y              13      // pad on/off control change # (check the manual for more information)
#define KAOSS_CC_00_BankMSB      0      //  CC 00
#define KAOSS_CC_01_Modulation   1      //  CC 01
#define KAOSS_CC_32_BankLSB     32      //  CC 32

// uncomment to enable, comment to disable
#define X_PITCH_CHANGE              // pitch bend wheel modulates the note sc
#define Y_VELOCITY                  // touch pad Y-axis: note velocity is translated into Y axis value sc
//#define Y_CONTROL_CHANGE      1   // touch pad Y-axis: chontrol change # that is translated into Y axes value (e.g. 1 for Modulation Wheel) sc
#define Y_AFTERTOUCH                // touch pad Y-axis: aftertouch modulates Y axis value sc
#define NOTE_INDICATION             // lights up the LED while a note is played
#define Z_PROGRAM_CHANGE        1   // pass program change messages to KAOSSILATOR   sc
#define ANY_CONTROL_CHANGE      1   // sc for the Bank CC 00 32 handle
//
/* ---( Config End - from here on it is better if you know what you are doing )------------------------------------------------ */
//
#ifdef DIN
  	#include <MIDI.h>
 	MIDI_CREATE_INSTANCE(HardwareSerial, Serial3, MIDI); //////////////////////sc-SERIAL3 for MEGA
#endif
//
byte xPad = 0;
byte yPad = 0;
int pitchChange = 0;
int afterTouch = 0;
//
void OnNoteOn(byte channel, byte note, byte velocity)
//initial values taken from Programming the Midisolutions "Event Processor Plus"/////////////////////////////sc
{
    	if (channel == INPUT_MIDI_CHANNEL)
    	{
        	switch (note)
        	{
			case 0:
				xPad = 0; break; //C0
			case 1:
				xPad = 4; break; //#C
			case 2:
				xPad = 7; break; //D
			case 3:
				xPad = 10; break; //D#
			case 4:
				xPad = 12; break; //E
			case 5:
				xPad = 15; break; //F
			case 6:
				xPad = 17; break; //F#
			case 7:
				xPad = 20; break; //G
			case 8:
				xPad = 22; break; //G#
			case 9:
				xPad = 25; break; //A
			case 10:
				xPad = 28; break; //A#
			case 11:
				xPad = 30; break; //B
			//
			case 12:
				xPad = 33; break; //C1
			case 13:
				xPad = 35; break; //#C
			case 14:
				xPad = 38; break; //D
			case 15:
				xPad = 41; break; //D#
			case 16:
				xPad = 43; break; //E
			case 17:
				xPad = 46; break; //F
			case 18:
				xPad = 49; break; //F#
			case 19:
				xPad = 51; break; //G
			case 20:
				xPad = 54; break; //G#
			case 21:
				xPad = 57; break; //A
			case 22:
				xPad = 59; break; //A#
			case 23:
				xPad = 62; break; //B
			//
			case 24:
				xPad = 65; break; //C2
			case 25:
				xPad = 68; break; //#C
			case 26:
				xPad = 70; break; //D
			case 27:
				xPad = 73; break; //D#
			case 28:
				xPad = 76; break; //E
			case 29:
				xPad = 78; break; //F
			case 30:
				xPad = 81; break; //F#
			case 31:
				xPad = 84; break; //G
			case 32:
				xPad = 86; break; //G#
			case 33:
				xPad = 89; break; //A
			case 34:
				xPad = 92; break; //A#
			case 35:
				xPad = 95; break; //B
			//
			case 36:
				xPad = 97; break; //C3
			case 37:
				xPad = 100; break; //#C
			case 38:
				xPad = 101; break; //D
			case 39:
				xPad = 105; break; //D#
			case 40:
				xPad = 108; break; //E
			case 41:
				xPad = 110; break; //F
			case 42:
				xPad = 113; break; //F#
			case 43:
				xPad = 115; break; //G
			case 44:
				xPad = 118; break; //G#
			case 45:
				xPad = 121; break; //A
			case 46:
				xPad = 123; break; //A#
			case 47:
				xPad = 126; break; //B
			case 48:
				xPad = 127; break; //C4
			//
			default:
			break; // if nothing else matches, do the default // default is optional
		}
    
   		#ifdef Y_VELOCITY
    			yPad = velocity;
   		#endif
  
   		if (velocity)
		{
        		#ifdef NOTE_INDICATION
           	 		digitalWrite(13, HIGH);
			#endif

        		#ifdef DIN
            			MIDI.sendControlChange(KAOSS_CC_X, constrain(xPad + pitchChange, 0, 127), KAOSS_MIDI_CHANNEL);
            			MIDI.sendControlChange(KAOSS_CC_Y, constrain(yPad + afterTouch, 0, 127), KAOSS_MIDI_CHANNEL);
           			MIDI.sendControlChange(KAOSS_CC_PAD, 127, KAOSS_MIDI_CHANNEL);
        		#endif
      
        		#ifdef USB
            			//Serial.print("xPad =");
            			//Serial.println(xPad);
            			usbMIDI.sendControlChange(KAOSS_CC_X, constrain(xPad + pitchChange, 0, 127), KAOSS_MIDI_CHANNEL);
            			usbMIDI.sendControlChange(KAOSS_CC_Y, constrain(yPad + afterTouch, 0, 127), KAOSS_MIDI_CHANNEL);
            			usbMIDI.sendControlChange(KAOSS_CC_PAD, 127, KAOSS_MIDI_CHANNEL);
        		#endif
    		}
    		else
    		{
        		OnNoteOff(channel, constrain(xPad + pitchChange, 0, 127), velocity);
    		}
 	}
}

void OnNoteOff(byte channel, byte note, byte velocity)
{
  	if (channel == INPUT_MIDI_CHANNEL)
  	{
		if (1)                        //sc: fixes stuck note issue
		{ 
			#ifdef NOTE_INDICATION
				digitalWrite(13, LOW);
			#endif

			#ifdef DIN
				MIDI.sendControlChange(KAOSS_CC_PAD, 0, KAOSS_MIDI_CHANNEL);
			#endif

			#ifdef USB
				usbMIDI.sendControlChange(KAOSS_CC_PAD, 0, KAOSS_MIDI_CHANNEL);
			#endif
		}
  	}
}

void OnPitchChange(byte channel, int pitch)
{
  	if (channel == INPUT_MIDI_CHANNEL)
  	{
		#ifdef X_PITCH_CHANGE
			#ifdef DIN
				// pitchChange = round(pitch/64.0);
				// pitchChange = round(pitch/8.0); //sc
				// pitchChange = round(pitch/128.0); //sc
				// pitchChange = round(pitch/1024.0); //sc
				pitchChange = round(pitch / 2048.0); //sc
				// pitchChange = round(pitch/4096.0); //sc
				//  pitchChange = round(pitch/8192.0); //sc
				MIDI.sendControlChange(KAOSS_CC_X, constrain(xPad + pitchChange, 0, 127), KAOSS_MIDI_CHANNEL);
			#endif
	
			#ifdef USB
				// pitchChange = round(pitch/64.0);
				// pitchChange = round(pitch/8.0); //sc
				// pitchChange = round(pitch/128.0); //sc
				// pitchChange = round(pitch/1024.0); //sc
				pitchChange = round(pitch / 2048.0); //sc
				// pitchChange = round(pitch/4096.0); //sc
				//  pitchChange = round(pitch/8192.0); //sc
				usbMIDI.sendControlChange(KAOSS_CC_X, constrain(xPad + pitchChange, 0, 127), KAOSS_MIDI_CHANNEL);
			#endif
		#endif
   	}
}

void OnControlChange(byte channel, byte control, byte value)
{
  	if (channel == INPUT_MIDI_CHANNEL)
  	{
		#ifdef DIN
			switch (control)
			{
				case 0:
					MIDI.sendControlChange(KAOSS_CC_00_BankMSB, value, KAOSS_MIDI_CHANNEL); break;                              
				case 1:
					//Serial.print("case 1 value = ");
					MIDI.sendControlChange(KAOSS_CC_Y, value, KAOSS_MIDI_CHANNEL);  break;                
				case 32:
					MIDI.sendControlChange(KAOSS_CC_32_BankLSB, value, KAOSS_MIDI_CHANNEL);break;               
				default:
				break;  // if nothing else matches, do the default // default is optional
			}
		#endif

		#ifdef USB
			switch (control)
			{
				case 0:
				{
					usbMIDI.sendControlChange(KAOSS_CC_00_BankMSB, value, KAOSS_MIDI_CHANNEL); break;              	
				}

				case 1:
				{
					Serial.print("case 1 value = ");
					Serial.println(value);
					//usbMIDI.sendControlChange(KAOSS_CC_01_Modulation, value, KAOSS_MIDI_CHANNEL);
					usbMIDI.sendControlChange(KAOSS_CC_Y, value, KAOSS_MIDI_CHANNEL); break;
				}

				case 32:
				{
					usbMIDI.sendControlChange(KAOSS_CC_32_BankLSB, value, KAOSS_MIDI_CHANNEL); break;
				}

				default:
				break;  // if nothing else matches, do the default // default is optional
			}
		#endif
  	}
}

void OnAfterTouch(byte channel, byte value)
{
  	if (channel == INPUT_MIDI_CHANNEL)
	{
		#ifdef Y_AFTERTOUCH
			afterTouch = value;
			#ifdef DIN
				MIDI.sendControlChange(KAOSS_CC_Y, constrain(yPad + afterTouch, 0, 127), KAOSS_MIDI_CHANNEL);
			#endif

			#ifdef USB
			usbMIDI.sendControlChange(KAOSS_CC_Y, constrain(yPad + afterTouch, 0, 127), KAOSS_MIDI_CHANNEL);
			#endif
		#endif
	}
}

void OnProgramChange(byte channel, byte program)
{
    #ifdef DIN
      	MIDI.sendProgramChange(program, KAOSS_MIDI_CHANNEL);
    #endif

    #ifdef USB
     	usbMIDI.sendProgramChange(program, KAOSS_MIDI_CHANNEL);
    #endif
}

void setup()
{
  	Serial.begin(115200);
  	pinMode(13, OUTPUT);

    	#ifdef DIN
		MIDI.begin(MIDI_CHANNEL_OMNI);
		MIDI.turnThruOff();
		MIDI.setHandleNoteOn(OnNoteOn);
		MIDI.setHandleNoteOff(OnNoteOff);
		#ifdef X_PITCH_CHANGE
			MIDI.setHandlePitchBend(OnPitchChange);
		#endif

		#ifdef Y_AFTERTOUCH
			MIDI.setHandleAfterTouchChannel(OnAfterTouch);
		#endif

		#ifdef Z_PROGRAM_CHANGE
			MIDI.setHandleProgramChange(OnProgramChange); ///////////////sc
		#endif

		#ifdef ANY_CONTROL_CHANGE ///////////////sc
			MIDI.setHandleControlChange(OnControlChange);
		#endif
	#endif

    	#ifdef USB
		usbMIDI.setHandleNoteOn(OnNoteOn);
		usbMIDI.setHandleNoteOff(OnNoteOff);
	
		#ifdef X_PITCH_CHANGE
			usbMIDI.setHandlePitchChange(OnPitchChange); // sc: saw handle error, changes Bend to Pitch
		#endif

		#ifdef Y_AFTERTOUCH
			usbMIDI.setHandleAfterTouchChannel(OnAfterTouch);
		#endif

		#ifdef Z_PROGRAM_CHANGE
			usbMIDI.setHandleProgramChange(OnProgramChange); ///////////////sc
		#endif

		#ifdef ANY_CONTROL_CHANGE ///////////////sc
			usbMIDI.setHandleControlChange(OnControlChange);
		#endif
    	#endif
}

void loop()
{
	#ifdef DIN
     		MIDI.read(); //sc// Call MIDI.read the fastest you can for real-time performance.
    	#endif

    	#ifdef USB
     		usbMIDI.read();
    	#endif
}
