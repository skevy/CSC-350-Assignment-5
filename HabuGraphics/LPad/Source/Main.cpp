//***************************************************************************//
// HabuGraphics Pad
// Written By Jeremy M Miller (Author of HabuGraphics Engine)
// Description: This is test platform for my OpenGL based graphics engine
// Version 0.01.103004
//
// Copyright (c) 2005-2010 Jeremy M Miller.  All rights reserved.
// This source code module, and all information, data, and algorithms
// associated with it, are part of BlueHabu technology (tm).
//                 PROPRIETARY AND CONFIDENTIAL
//***************************************************************************//

//***************************************************************************//
#include "App.hpp"
//***************************************************************************//

//***************************************************************************//
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreviousInstance, char* cpCmdLine, int nCmdShow)			
{
  App::Instance(hInstance);

  if(App::Instance()->Initialize(cpCmdLine))
    App::Instance()->Run();
  App::Instance()->End();

  return 0;
}
//***************************************************************************//