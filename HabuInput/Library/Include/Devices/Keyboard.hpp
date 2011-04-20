//***************************************************************************//
// Keyboard Class Interface
//
// Created Sept 13, 2006
// By: Jeremy M Miller
//
// Copyright (c) 2006 Jeremy M Miller.  All rights reserved.
// This source code module, and all information, data, and algorithms
// associated with it, are part of Habu technology (tm).
//
// Usage of HabuInput is subject to the appropriate license agreement.
// A proprietary/commercial licenses are available. (info@bluehabu.com)
//                 
// HabuInput is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// HabuInput is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with HabuThreads.  If not, see <http://www.gnu.org/licenses/>.
//***************************************************************************//

#ifndef HABU_INPUT_KEYBOARD_HPP
#define HABU_INPUT_KEYBOARD_HPP

//***************************************************************************//
#include "HabuInput.hpp"
#include "Devices\Device.hpp"
//***************************************************************************//

//***************************************************************************//
// This enum simply maskes that we are using DirectInput keys
enum HabuInputKey
{
  HIK_ESCAPE =       DIK_ESCAPE,
  HIK_1 =            DIK_1,
  HIK_2 =            DIK_2,
  HIK_3 =            DIK_3,
  HIK_4 =            DIK_4,
  HIK_5 =            DIK_5,
  HIK_6 =            DIK_6,
  HIK_7 =            DIK_7,
  HIK_8 =            DIK_8,
  HIK_9 =            DIK_9,
  HIK_0 =            DIK_0,
  HIK_MINUS =        DIK_MINUS,        /* - on main keyboard */
  HIK_EQUALS =       DIK_EQUALS,
  HIK_BACK =         DIK_BACK,         /* backspace */
  HIK_TAB =          DIK_TAB,
  HIK_Q =            DIK_Q,
  HIK_W =            DIK_W,
  HIK_E =            DIK_E,
  HIK_R =            DIK_R,
  HIK_T =            DIK_T,
  HIK_Y =            DIK_Y,
  HIK_U =            DIK_U,
  HIK_I =            DIK_I,
  HIK_O =            DIK_O,
  HIK_P =            DIK_P,
  HIK_LBRACKET =     DIK_LBRACKET,
  HIK_RBRACKET =     DIK_RBRACKET,
  HIK_RETURN =       DIK_RETURN,       /* Enter on main keyboard */
  HIK_LCONTROL =     DIK_LCONTROL,
  HIK_A =            DIK_A,
  HIK_S =            DIK_S,
  HIK_D =            DIK_D,
  HIK_F =            DIK_F,
  HIK_G =            DIK_G,
  HIK_H =            DIK_H,
  HIK_J =            DIK_J,
  HIK_K =            DIK_K,
  HIK_L =            DIK_L,
  HIK_SEMICOLON =    DIK_SEMICOLON,
  HIK_APOSTROPHE =   DIK_APOSTROPHE,
  HIK_GRAVE =        DIK_GRAVE,        /* accent grave */
  HIK_LSHIFT =       DIK_LSHIFT,
  HIK_BACKSLASH =    DIK_BACKSLASH,
  HIK_Z =            DIK_Z,
  HIK_X =            DIK_X,
  HIK_C =            DIK_C,
  HIK_V =            DIK_V,
  HIK_B =            DIK_B,
  HIK_N =            DIK_N,
  HIK_M =            DIK_M,
  HIK_COMMA =        DIK_COMMA,
  HIK_PERIOD =       DIK_PERIOD,       /* . on main keyboard */
  HIK_SLASH =        DIK_SLASH,        /* / on main keyboard */
  HIK_RSHIFT =       DIK_RSHIFT,
  HIK_MULTIPLY =     DIK_MULTIPLY,     /* * on numeric keypad */
  HIK_LMENU =        DIK_LMENU,        /* left Alt */
  HIK_SPACE =        DIK_SPACE,
  HIK_CAPITAL =      DIK_CAPITAL,
  HIK_F1 =           DIK_F1,
  HIK_F2 =           DIK_F2,
  HIK_F3 =           DIK_F3,
  HIK_F4 =           DIK_F4,
  HIK_F5 =           DIK_F5,
  HIK_F6 =           DIK_F6,
  HIK_F7 =           DIK_F7,
  HIK_F8 =           DIK_F8,
  HIK_F9 =           DIK_F9,
  HIK_F10 =          DIK_F10,
  HIK_NUMLOCK =      DIK_NUMLOCK,
  HIK_SCROLL =       DIK_SCROLL,       /* Scroll Lock */
  HIK_NUMPAD7 =      DIK_NUMPAD7,
  HIK_NUMPAD8 =      DIK_NUMPAD8,
  HIK_NUMPAD9 =      DIK_NUMPAD9,
  HIK_SUBTRACT =     DIK_SUBTRACT,     /* - on numeric keypad */
  HIK_NUMPAD4 =      DIK_NUMPAD4,
  HIK_NUMPAD5 =      DIK_NUMPAD5,
  HIK_NUMPAD6 =      DIK_NUMPAD6,
  HIK_ADD =          DIK_ADD,          /* + on numeric keypad */
  HIK_NUMPAD1 =      DIK_NUMPAD1,
  HIK_NUMPAD2 =      DIK_NUMPAD2,
  HIK_NUMPAD3 =      DIK_NUMPAD3,
  HIK_NUMPAD0 =      DIK_NUMPAD0,
  HIK_DECIMAL =      DIK_DECIMAL,      /* . on numeric keypad */
  HIK_OEM_102 =      DIK_OEM_102,      /* <> or \| on RT 102-key keyboard (Non-U.S.) */
  HIK_F11 =          DIK_F11,
  HIK_F12 =          DIK_F12,
  HIK_F13 =          DIK_F13,          /* (NEC PC98) */
  HIK_F14 =          DIK_F14,          /* (NEC PC98) */
  HIK_F15 =          DIK_F15,          /* (NEC PC98) */
  HIK_KANA =         DIK_KANA,         /* (Japanese keyboard) */
  HIK_ABNT_C1 =      DIK_ABNT_C1,      /* /? on Brazilian keyboard */
  HIK_CONVERT =      DIK_CONVERT,      /* (Japanese keyboard) */
  HIK_NOCONVERT =    DIK_NOCONVERT,    /* (Japanese keyboard) */
  HIK_YEN =          DIK_YEN,          /* (Japanese keyboard) */
  HIK_ABNT_C2 =      DIK_ABNT_C2,      /* Numpad . on Brazilian keyboard */
  HIK_NUMPADEQUALS = DIK_NUMPADEQUALS, /* = on numeric keypad (NEC PC98) */
  HIK_PREVTRACK =    DIK_PREVTRACK,    /* Previous Track (DIK_CIRCUMFLEX on Japanese keyboard) */
  HIK_AT =           DIK_AT,           /* (NEC PC98) */
  HIK_COLON =        DIK_COLON,        /* (NEC PC98) */
  HIK_UNDERLINE =    DIK_UNDERLINE,    /* (NEC PC98) */
  HIK_KANJI =        DIK_KANJI,        /* (Japanese keyboard) */
  HIK_STOP =         DIK_STOP,         /* (NEC PC98) */
  HIK_AX =           DIK_AX,           /* (Japan AX) */
  HIK_UNLABELED =    DIK_UNLABELED,    /* (J3100) */
  HIK_NEXTTRACK =    DIK_NEXTTRACK,    /* Next Track */
  HIK_NUMPADENTER =  DIK_NUMPADENTER,  /* Enter on numeric keypad */
  HIK_RCONTROL =     DIK_RCONTROL,
  HIK_MUTE =         DIK_MUTE,         /* Mute */
  HIK_CALCULATOR =   DIK_CALCULATOR,   /* Calculator */
  HIK_PLAYPAUSE =    DIK_PLAYPAUSE,    /* Play / Pause */
  HIK_MEDIASTOP =    DIK_MEDIASTOP,    /* Media Stop */
  HIK_VOLUMEDOWN =   DIK_VOLUMEDOWN,   /* Volume - */
  HIK_VOLUMEUP =     DIK_VOLUMEUP,     /* Volume + */
  HIK_WEBHOME =      DIK_WEBHOME,      /* Web home */
  HIK_NUMPADCOMMA =  DIK_NUMPADCOMMA,  /* , on numeric keypad (NEC PC98) */
  HIK_DIVIDE =       DIK_DIVIDE,       /* / on numeric keypad */
  HIK_SYSRQ =        DIK_SYSRQ,
  HIK_RMENU =        DIK_RMENU,        /* right Alt */
  HIK_PAUSE =        DIK_PAUSE,        /* Pause */
  HIK_HOME =         DIK_HOME,         /* Home on arrow keypad */
  HIK_UP =           DIK_UP,           /* UpArrow on arrow keypad */
  HIK_PRIOR =        DIK_PRIOR,        /* PgUp on arrow keypad */
  HIK_LEFT =         DIK_LEFT,         /* LeftArrow on arrow keypad */
  HIK_RIGHT =        DIK_RIGHT,        /* RightArrow on arrow keypad */
  HIK_END =          DIK_END,          /* End on arrow keypad */
  HIK_DOWN =         DIK_DOWN,         /* DownArrow on arrow keypad */
  HIK_NEXT =         DIK_NEXT,         /* PgDn on arrow keypad */
  HIK_INSERT =       DIK_INSERT,       /* Insert on arrow keypad */
  HIK_DELETE =       DIK_DELETE,       /* Delete on arrow keypad */
  HIK_LWIN =         DIK_LWIN,         /* Left Windows key */
  HIK_RWIN =         DIK_RWIN,         /* Right Windows key */
  HIK_APPS =         DIK_APPS,         /* AppMenu key */
  HIK_POWER =        DIK_POWER,        /* System Power */
  HIK_SLEEP =        DIK_SLEEP,        /* System Sleep */
  HIK_WAKE =         DIK_WAKE,         /* System Wake */
  HIK_WEBSEARCH =    DIK_WEBSEARCH,    /* Web Search */
  HIK_WEBFAVORITES = DIK_WEBFAVORITES, /* Web Favorites */
  HIK_WEBREFRESH =   DIK_WEBREFRESH,   /* Web Refresh */
  HIK_WEBSTOP =      DIK_WEBSTOP,      /* Web Stop */
  HIK_WEBFORWARD =   DIK_WEBFORWARD,   /* Web Forward */
  HIK_WEBBACK =      DIK_WEBBACK,      /* Web Back */
  HIK_MYCOMPUTER =   DIK_MYCOMPUTER,   /* My Computer */
  HIK_MAIL =         DIK_MAIL,         /* Mail */
  HIK_MEDIASELECT =  DIK_MEDIASELECT,  /* Media Select */
}; // End of enum HabuInputKey
//***************************************************************************//

//***************************************************************************//
namespace HabuTech
{
  //*************************************************************************//
  // This class reads the state of keys on the machines keyboard
  class Keyboard : public Device
  {
  private:
    //***********************************************************************//
    //-----------------------------------------------------------------------//
    // This member is the pointer to DirectInput's keybaord interface device
    IDirectInputDevice8* mpKeyBoard;
    // This member array holds the state of the keys for the last time this
    // classes Poll method was called
    char mcaKeyBoardState[256];
    //-----------------------------------------------------------------------//
    //***********************************************************************//
  public:
    //***********************************************************************//
    //-----------------------------------------------------------------------//
    // Constructor
    Keyboard();
    // Desturctor
    // Note this destructor is not virtual. Do not derive from this class.
    ~Keyboard();
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    // The below method uses a pointer from a the directinput interface to 
    // create and initialze communication with the keyboard using directinput.  
    // This method also sets cooperation level for the window. This method 
    // is required by the Device base class.
    // Parameter 1: An establised pointer to a directinput interface.
    // Parameter 2: A valid window handle so we know when the windows is infocus
    //              and therefore know if we should capture the state of the device.
    // Return Value: If the method was unable to setup directinput for the mouse
    //               this method will return false. Otherwise it will return true.
    //               We assume that we can always use the mouse windows calls.
    bool Initialize(IDirectInput8* pDirectInput, HWND hMainWindow);
    // The below method will uninitialize and release the keyboard from directinput.
    // This method is required by the Device base class.
    // Return Value: This method will return true if the release and uninitialization
    //               was sucessful. Otherwise it will return false.
    bool Uninitialize();
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    // This method will return true if the a specified key was held down when 
    // the keyboard was last polled.
    // Parameter 1: The key the method will check.
    // Return Value: The methid will return true if the key specifed in parameter
    //               1 is pressed. Otherwise it will return false.
    bool KeyDown(enum HabuInputKey eKey) const
    {
      return ((this->mcaKeyBoardState[eKey] & 0x80) != 0);
    }
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    // This is method is required to poll the mouse and should be called once per
    // program loop.  This method is required by the Device base class.
    void Poll(); 
    //-----------------------------------------------------------------------//
  }; // End of class Keyboard : public Device
  //*************************************************************************//
} // End of namespace HabuTech
//***************************************************************************//

#endif HABU_INPUT_KEYBOARD_HPP