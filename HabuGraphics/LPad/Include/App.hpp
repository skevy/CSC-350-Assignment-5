//***************************************************************************//
// App Object Interface
//
// Created Jan 01, 2005
// By: Jeremy M Miller
//
// Copyright (c) 2005  Jeremy M Miller.  All rights reserved.
// This source code module, and all information, data, and algorithms
// associated with it, are part of BlueHabu technology (tm).
//                 PROPRIETARY AND CONFIDENTIAL
//***************************************************************************//

#ifndef APP_HPP
#define APP_HPP

//***************************************************************************//
// System Includes
#include <windows.h>
//***************************************************************************//

//***************************************************************************//
// BlueHabu technology includes
#include "HabuThreads.hpp"
#include "HabuGraphics.hpp"

#include "HabuInput.hpp"
// TODO fix the need to explictly call these includes here
#include "Devices\Keyboard.hpp"
#include "Devices\Mouse.hpp"
//***************************************************************************//

//***************************************************************************//
class App // Singleton -- There can only be one application running.
{
private:
  //*************************************************************************//
  //-------------------------------------------------------------------------//
  // Static pointer to this instance. Necessary to make this class a singleton
  static class App* mpInstance;
  //-------------------------------------------------------------------------//

  //-------------------------------------------------------------------------//
  // Handles for control windows 
  static HWND smhWindow;
  static HINSTANCE smhInstance;
  // Mutex is so only one instance of this app is running at a time
  static HANDLE mhAppMutex;
  //-------------------------------------------------------------------------//

  //-------------------------------------------------------------------------//      
  // Main window properties
  static WNDCLASS smMainWcl;     
  // Identifies App's window location and size.
  static RECT smMainWindowRect;      
  //-------------------------------------------------------------------------//

  //-------------------------------------------------------------------------//
  static bool smbHasFocus;
  static bool smbWindowActive;
  static bool smbWindowOpen;
  static bool smbWindowed;
  //-------------------------------------------------------------------------//

  static void UpdateWindowRect() { if (smhWindow) GetWindowRect(smhWindow, &smMainWindowRect); }
  static LRESULT CALLBACK WindowProc (HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

  //-------------------------------------------------------------------------//
  static void KillWindow();
  static bool SpawnWindow(long lWidth, long lHeight, bool bWindowed);
  //-------------------------------------------------------------------------//

  static void  MessageLoop();
  
  std::string mstrCommandLine;

  App(HINSTANCE hInstance);

  class HabuTech::Graphics* mpGraphics;
  //***************************************************************************//
public:
  //***************************************************************************//
  ~App();

  static class App* Instance(HINSTANCE hInstance = NULL)
  {
    if(mpInstance == NULL && hInstance)
      mpInstance = new App(hInstance);
    return mpInstance;
  }

  bool Initialize(char* cpCommandline);
  long Run();
  void End();
  //***************************************************************************//
};
//*****************************************************************************//

//*****************************************************************************//
extern App* gpApp;
//*****************************************************************************//

#endif APP_HPP