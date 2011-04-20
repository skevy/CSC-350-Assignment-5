//***************************************************************************//
// Control Object Interface
//
// Created Jan 01, 2005
// By: Jeremy M Miller
//
// Copyright (c) 2005-2007 Jeremy M Miller.  All rights reserved.
// This source code module, and all information, data, and algorithms
// associated with it, are part of BlueHabu technology (tm).
//                 PROPRIETARY AND CONFIDENTIAL
//***************************************************************************//

#ifndef CONTROL_HPP
#define CONTROL_HPP

enum ControlSignalType
{
	NO_CONTROL_SIGNAL,
	END_CONTROL_SIGNAL,
	CONTINUE_CONTROL_SIGNAL
};

class Control
{
private:
public:
	Control();
	~Control();
	ControlSignalType Update();
};

#endif CONTROL_HPP;