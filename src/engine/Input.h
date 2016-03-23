/**
\author		Korotkov Andrey aka DRON
\date		23.03.2016 (c)Korotkov Andrey

This file is a part of DGLE project and is distributed
under the terms of the GNU Lesser General Public License.
See "DGLE.h" for more details.
*/

#pragma once

#include "Common.h"

#ifndef NO_BUILTIN_INPUT

#ifdef PLATFORM_WINDOWS
#	include "platform\windows\BaseInput.h"
#endif

class CInput: private CBaseInput, public IInput
{
	bool		 _bExclusive;
	bool		 _bHideCursor;
	bool		 _bFocused;
	bool		 _bCurBeyond;

	bool		 _bIsTxtInput;
	char		*_pcBuffer;
	std::string	 _strInputTxt;
	uint		 _uiBufSize;

	bool		 _abKeys[256];
	TMouseStates _stMsts;
	int			 _uiOldMouseX, _uiOldMouseY, _iDeltaWheel;

	void		 _ClipCursor();
	void		 _MessageProc(const TWindowMessage &stMsg);
	void		 _Loop();
	void		 _Update();

	static void DGLE_API _s_MessageProc(void *pParameter, const TWindowMessage &stMsg);
	static void DGLE_API _s_Update(void *pParameter);
	static void DGLE_API _s_Loop(void *pParameter);

public:

	CInput(uint uiInstIdx);
	~CInput();

	DGLE_RESULT DGLE_API Configure(E_INPUT_CONFIGURATION_FLAGS eParams) override;
	DGLE_RESULT DGLE_API GetMouseStates(TMouseStates &stMs) override;
	DGLE_RESULT DGLE_API GetKey(E_KEYBOARD_KEY_CODES eKey, bool &bPressed) override;
	DGLE_RESULT DGLE_API GetKeyName(E_KEYBOARD_KEY_CODES eKey, uchar &cAsciiCode) override;
	DGLE_RESULT DGLE_API BeginTextInput(char *cBuffer, uint uiBufferSize) override;
	DGLE_RESULT DGLE_API EndTextInput() override;
	DGLE_RESULT DGLE_API GetJoysticksCount(uint &uiCount) override;
	DGLE_RESULT DGLE_API GetJoystickName(uint uiJoyId, char *pcName, uint &uiCharsCount) override;
	DGLE_RESULT DGLE_API GetJoystickStates(uint uiJoyId, TJoystickStates &stJoyStates) override;
	DGLE_RESULT DGLE_API GetType(E_ENGINE_SUB_SYSTEM &eSubsysType) override;

	IDGLE_BASE_IMPLEMENTATION(IInput, INTERFACE_IMPL(IEngineSubSystem, INTERFACE_IMPL_END))
};

#endif