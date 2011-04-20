//***************************************************************************//
// App Object Implementation
//
// Created Jan 01, 2005
// By: Jeremy M Miller
//
// Copyright (c) 2005-2010 Jeremy M Miller.  All rights reserved.
// This source code module, and all information, data, and algorithms
// associated with it, are part of BlueHabu technology (tm).
//                 PROPRIETARY AND CONFIDENTIAL
//***************************************************************************//

//***************************************************************************//
#include "App.hpp"

#include <assert.h>
#include <string>
//***************************************************************************//

//***************************************************************************//
using namespace HabuTech;
using namespace std;
//***************************************************************************//

#define APP_TITLE "LPad"
#define APP_MUTEX_NAME         "Global\\" APP_TITLE "_APP_MUTEX_"
#define APP_WINDOW_NAME        "HabuGraphicsWindow"
#define APP_SLEEP_TIME         25
#define APP_VERSION            0.050F


HINSTANCE  App::smhInstance;
HANDLE     App::mhAppMutex;

WNDCLASS   App::smMainWcl;
HWND       App::smhWindow             = NULL;
RECT       App::smMainWindowRect;

bool       App::smbWindowActive        = false;
bool       App::smbHasFocus            = true;
bool       App::smbWindowOpen          = true;
bool       App::smbWindowed            = true;

class App* App::mpInstance = NULL;
//***************************************************************************//
App::App(HINSTANCE hInstance)
{
  mpGraphics = NULL;
  this->smhInstance = hInstance;
  smbHasFocus = false;
}
//***************************************************************************//

//***************************************************************************//
App::~App()
{
}
//***************************************************************************//

//***************************************************************************//
bool App::Initialize(char* cpCommandLine)
{
  if(cpCommandLine)
    this->mstrCommandLine = static_cast<string>(cpCommandLine);

  bool bReturnValue = false;
  mpGraphics = new Graphics(true);
  if(this->SpawnWindow(800, 600, true) && mpGraphics->Initialize(this->smhWindow, 800, 600) >= 0)
  {
    mpGraphics->WindowDimensions(800, 600);
    Input::Instance()->Initialize(this->smhInstance, this->smhWindow);
    bReturnValue = true;
  }
  return bReturnValue;
}
//***************************************************************************//

//***************************************************************************//
long App::Run() 
{  
  bool bEscapePressed = false;
  class HabuTech::Timer oTimer;
  class HabuTech::Random<float> oRandom;
  class Scene*  pScene   = this->mpGraphics->CreateScene(static_cast<string>("DEFAULT_SCENE"));

  class Mesh*   pMesh    = NULL;
  class Camera* pCamera  = NULL;
  class Light*  pLight   = NULL;

  // Load the scene if we can find one.
  ifstream ifsSceneFile;
  ifsSceneFile.open(this->mstrCommandLine.c_str());
  if(ifsSceneFile.is_open())
  {
    pScene->Load(ifsSceneFile);
    pCamera = pScene->GetActiveCamera();
    pMesh = pScene->GetMesh("Cone");

    pLight = pScene->GetLight(static_cast<string>("Default"));
    if(pLight)
      pLight->TurnLightOn();
    float fHeight = 0.0F;

    if(pMesh)
    {
      fHeight = pMesh->BoundVolume()->Height();
      pMesh->Position(0.0, 0.0, 0.0);
      pMesh->Elevate(fHeight/2.0f);
      Mesh* pGround = pScene->GetMesh("Ground");
      float fWidth = 100.0f;
      float fDepth = 100.0f;

      if(pGround)
      {
        fWidth = pGround->BoundVolume()->Width();
        fDepth = pGround->BoundVolume()->Depth();
      }
      for(unsigned long ulIndex = 0; ulIndex < 512; ulIndex++)
      {
        stringstream sstmNewName;
        sstmNewName << pMesh->Name();
        sstmNewName << ulIndex;
        
        Mesh* pNewClone = pScene->CloneMesh(pMesh->Name(), sstmNewName.str());
        float fHeight = pNewClone->BoundVolume()->Height();
        pNewClone->Position(oRandom.Generate(-fWidth/2.0f, fWidth/2.0f), fHeight/2.0F, oRandom.Generate(-fDepth/2.0f, fDepth/2.0f));
      }
    }

    unsigned long ulLOD = 0;
    bool bWireFrame = false;
    bool upkeydown = false;
    bool downkeydown = false;
    bool xkeydown = false;
    double timer = 0.0;

    float rX = 0.0F;
    float rY = 0.0F;
    float rZ = 0.0F;

    while(smbWindowOpen && !bEscapePressed)
    {
      float fDT = (float)oTimer.DT(TIMER_1);

      if(Input::Instance()->GetKeyboard()->KeyDown(HIK_V) && 
        !Input::Instance()->GetKeyboard()->KeyDown(HIK_RSHIFT))
      {
        pCamera->ChangeFOV(0.001F);
      }
      if(Input::Instance()->GetKeyboard()->KeyDown(HIK_V) && 
        Input::Instance()->GetKeyboard()->KeyDown(HIK_RSHIFT))
      {
        pCamera->ChangeFOV(-0.001F);
      }
      if(Input::Instance()->GetKeyboard()->KeyDown(HIK_D) && 
        !Input::Instance()->GetKeyboard()->KeyDown(HIK_RSHIFT))
      {
        pCamera->Strafe(2.0F * fDT);
      }
      if(Input::Instance()->GetKeyboard()->KeyDown(HIK_A) && 
        !Input::Instance()->GetKeyboard()->KeyDown(HIK_RSHIFT))
      {
        pCamera->Strafe(-2.0F * fDT);
      }
      if(Input::Instance()->GetKeyboard()->KeyDown(HIK_S) && 
        !Input::Instance()->GetKeyboard()->KeyDown(HIK_RSHIFT))
      {
        pCamera->Advance(2.0F * fDT);
      }
      if(Input::Instance()->GetKeyboard()->KeyDown(HIK_W) && 
        !Input::Instance()->GetKeyboard()->KeyDown(HIK_RSHIFT))
      {
        pCamera->Advance(-2.0F * fDT);
      }

      if(Input::Instance()->GetKeyboard()->KeyDown(HIK_Q) && 
        !Input::Instance()->GetKeyboard()->KeyDown(HIK_RSHIFT))
      {
        pCamera->Elevate(2.0F * fDT);
      }
      if(Input::Instance()->GetKeyboard()->KeyDown(HIK_Z) && 
        !Input::Instance()->GetKeyboard()->KeyDown(HIK_RSHIFT))
      {
        pCamera->Elevate(-2.0F * fDT);
      }
      if(Input::Instance()->GetKeyboard()->KeyDown(HIK_ESCAPE))
      {
        bEscapePressed = true;
      }

      if(Input::Instance()->GetKeyboard()->KeyDown(HIK_G))
      {
        pMesh->RelativeYaw(fDT * -0.5F);
      }
      if(Input::Instance()->GetKeyboard()->KeyDown(HIK_J))
      {
        pMesh->RelativeYaw(fDT * 0.5F);
      }
      if(Input::Instance()->GetKeyboard()->KeyDown(HIK_Y))
      {
        pMesh->RelativePitch(fDT * -0.5F);
      }
      if(Input::Instance()->GetKeyboard()->KeyDown(HIK_H))
      {
        pMesh->RelativePitch(fDT * 0.5F);
      }

      if(Input::Instance()->GetMouse()->LeftButton())
      {
          pCamera->RelativePitch (Input::Instance()->GetMouse()->Direct_DY() * .00005f);
          pCamera->RelativeYaw  (Input::Instance()->GetMouse()->Direct_DX() * .00005f);
      }


      Input::Instance()->Poll();

      this->MessageLoop();

      mpGraphics->Render();
      mpGraphics->SwapBuffer();
    }
  }
  else
  {
    pMesh    = pScene->CreateMesh(static_cast<string>("CUBE"));
    pCamera  = pScene->CreateCamera(static_cast<string>("DEFAULT_CAMERA"));
    pLight   = pScene->CreateLight(static_cast<string>("DEFAULT_LIGHT"), LIGHT_ID_0);
  }

  return 0;
}
//***************************************************************************//

//***************************************************************************//
void App::End()
{
  mpGraphics->Uninitialize();
  this->KillWindow();
  delete mpGraphics;
  return;
}
//***************************************************************************//


//***************************************************************************//
LRESULT CALLBACK App::WindowProc( HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam )
{
  static bool unPauseAfterRestore = false;
  long ret = 0;

  switch (message)
  {
  case WM_ERASEBKGND:
    ret = 1;
    break;

  case WM_SETFOCUS:
    smbHasFocus = true;
    ret = 1;
    break;

  case WM_KILLFOCUS:
    smbHasFocus = false;
    ret = 1;
    break;

  case WM_ACTIVATE:
    if (LOWORD( wParam ) == WA_INACTIVE)
    {
      if (smbWindowActive)
      {
        smbWindowActive = false;
        ShowWindow( smhWindow, SW_MINIMIZE );
      }
    }
    else
    {
      if (!smbWindowActive)
      {
        smbWindowActive = true;
        SetForegroundWindow( smhWindow );
        ShowWindow( smhWindow, SW_RESTORE );
      }
    }  
    ret = 1;
    break;

  case WM_MOVE:
  case WM_SIZE:
    UpdateWindowRect();
    break;

  case WM_CLOSE:
    smbWindowOpen = false;
    break;

  case WM_DESTROY:
    ShowWindow (hwnd, SW_HIDE);
    PostQuitMessage(0);
    ret = 0;
    break;

  case WM_SETCURSOR:
    // set cursor to proper state
    //Input::Instance()->GetMouse()->SetCursor();
    //ret = 1;
    break;

  case WM_SYSCOMMAND:
    // low order nibble used by internally by windows
    switch (wParam & 0xFFF0)
    {
      // no suspension or screen saver while this app is running
    case SC_MONITORPOWER:
    case SC_SCREENSAVE:
      ret = FALSE;
      break;

      // don't allow window menu activations by a keypress (really annoying in windowed mode)
    case SC_KEYMENU:
      ret = FALSE;
      break;

    default: return (DefWindowProc( hwnd, message, wParam, lParam ));
    }
    break;

  default:
    return (DefWindowProc( hwnd, message, wParam, lParam ));
    // return before break
  }


  return (ret);
}
//***************************************************************************//

//***************************************************************************//
void App::MessageLoop()
{
  MSG msg;

  while (PeekMessage( &msg, smhWindow, 0, 0, PM_NOREMOVE ))
  {
    if (!GetMessage( &msg, smhWindow, 0, 0 ))
      return;

    TranslateMessage( &msg );
    DispatchMessage( &msg );
  }

  // If the app isn't the active app, throw in a small Sleep() call 
  // to give other apps a chance to do processing.
  if (!smbWindowActive)
    Sleep(APP_SLEEP_TIME);
}
//***************************************************************************//

//***************************************************************************//
bool App::SpawnWindow(long lWidth, long lHeight, bool bWindowed)
{
  bool bErrorOccured = false;
  smbWindowed = bWindowed;

  smMainWcl.hInstance     = smhInstance;
  smMainWcl.lpszClassName = APP_WINDOW_NAME;
  smMainWcl.lpfnWndProc   = WindowProc;
  smMainWcl.style         = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
  smMainWcl.hIcon         = LoadIcon(NULL, IDI_WINLOGO);
  smMainWcl.hCursor       = LoadCursor(NULL, IDC_ARROW);
  smMainWcl.lpszMenuName  = NULL;
  smMainWcl.cbClsExtra    = 0;
  smMainWcl.cbWndExtra    = 0;
  smMainWcl.hbrBackground = (HBRUSH) GetStockObject( NULL_BRUSH );
  DWORD dwExStyle;
  DWORD dwStyle;
  smMainWindowRect.left   = 0; // Set Left Value To 0
  smMainWindowRect.right  = lWidth;
  smMainWindowRect.top    = 0;			// Set Top Value To 0
  smMainWindowRect.bottom = lHeight;

  if (!RegisterClass(&smMainWcl))
    bErrorOccured = true;

  if(!bErrorOccured)
  {
    // Set window title
    char caAppTitle[64];
    sprintf (caAppTitle, "%s v%0.3f", APP_TITLE, APP_VERSION);

    if(!smbWindowed)												// Attempt Fullscreen Mode?
    {
      DEVMODE dmScreenSettings;								// Device Mode
      memset(&dmScreenSettings,0,sizeof(dmScreenSettings));	// Makes Sure Memory's Cleared
      dmScreenSettings.dmSize       = sizeof(dmScreenSettings);		// Size Of The Devmode Structure
      dmScreenSettings.dmPelsWidth	= lWidth;				// Selected Screen Width
      dmScreenSettings.dmPelsHeight	= lHeight;				// Selected Screen Height
      dmScreenSettings.dmBitsPerPel	= 32;					// Selected Bits Per Pixel
      dmScreenSettings.dmFields     = DM_BITSPERPEL|DM_PELSWIDTH|DM_PELSHEIGHT;

      // Try To Set Selected Mode And Get Results.  NOTE: CDS_FULLSCREEN Gets Rid Of Start Bar.
      if(ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
      {
        // If The Mode Fails, Offer Two Options.  Quit Or Use Windowed Mode.
        if (MessageBox(NULL,"The Requested Fullscreen Mode Is Not Supported By\nYour Video Card. Use Windowed Mode Instead?", "HabuGraphics" , MB_YESNO | MB_ICONEXCLAMATION) == IDYES)
        {
          smbWindowed = true;		// Windowed Mode Selected.
        }
        else
        {
          // Pop Up A Message Box Letting User Know The Program Is Closing.
          MessageBox(NULL,"Program Will Now Close.","ERROR",MB_OK|MB_ICONSTOP);
          bErrorOccured = true;
        }
      }
    }

    if(!bErrorOccured)
    {
      if(!smbWindowed)												// Are We Still In Fullscreen Mode?
      {
        dwExStyle = WS_EX_APPWINDOW;								// Window Extended Style
        dwStyle   = WS_POPUP;										// Windows Style
        ShowCursor(FALSE);										// Hide Mouse Pointer
      }
      else
      {
        dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;			// Window Extended Style
        dwStyle   = WS_OVERLAPPEDWINDOW;							// Windows Style
      }

      long sx;
      long sy;
      if(smbWindowed)
      {
        RECT vp_rect;
        GetClientRect( GetDesktopWindow(), &vp_rect );
        sx = max (0, ((vp_rect.right-vp_rect.left) >> 1) - (lWidth >> 1));
        sy = max (0, ((vp_rect.bottom-vp_rect.top) >> 1) - (lHeight >> 1));
      }
      else
      {
        sx = 0;
        sy = 0;
      }

      AdjustWindowRectEx(&smMainWindowRect, dwStyle, FALSE, dwExStyle);		// Adjust Window To True Requested Size

      // Create The Window
      if (!(smhWindow = CreateWindowEx(	dwExStyle,							// Extended Style For The Window
        APP_WINDOW_NAME,							// Class Name
        caAppTitle,								// Window Title
        dwStyle |							// Defined Window Style
        WS_CLIPSIBLINGS |					// Required Window Style
        WS_CLIPCHILDREN,					// Required Window Style
        sx, sy,								// Window Position
        smMainWindowRect.right  - smMainWindowRect.left,	// Calculate Window Width
        smMainWindowRect.bottom - smMainWindowRect.top,	// Calculate Window Height
        NULL,								// No Parent Window
        NULL,								// No Menu
        smhInstance,							// Instance
        NULL)))								// Dont Pass Anything To WM_CREATE
      {
        App::KillWindow();								// Reset The Display
        MessageBox(NULL,"Window Creation Error.","ERROR",MB_OK|MB_ICONEXCLAMATION);
        return FALSE;								// Return FALSE
      }

      ShowWindow(smhWindow,SW_SHOW);						// Show The Window
      SetForegroundWindow(smhWindow);						// Slightly Higher Priority
      SetFocus(smhWindow);									// Sets Keyboard Focus To The Window

      smbWindowActive = true;
      UpdateWindowRect();     // Fill in our window rect structure.
    }
    else// bErrorOccured == true
    {
    }

  }
  else // bErrorOccured == true
  {
    //unsigned long ulError = GetLastError();
  }

  return !bErrorOccured;
}
//***************************************************************************//

//***************************************************************************//
void App::KillWindow()
{
  if(!smbWindowed)										// Are We In Fullscreen Mode?
  {
    ChangeDisplaySettings(NULL,0);					// If So Switch Back To The Desktop
    ShowCursor(TRUE);								// Show Mouse Pointer
  }

  if (smhWindow && !DestroyWindow(smhWindow))					// Are We Able To Destroy The Window?
  {
    MessageBox(NULL,"Could Not Release hWnd.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
    smhWindow = NULL;										// Set hWnd To NULL
  }

  if (!UnregisterClass(APP_WINDOW_NAME,smhInstance))			// Are We Able To Unregister Class
  {
    MessageBox(NULL,"Could Not Unregister Class.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
    smhInstance = NULL;									// Set hInstance To NULL
  }

  ClipCursor(NULL);
}
//***************************************************************************//
