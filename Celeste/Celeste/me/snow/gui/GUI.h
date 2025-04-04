#ifndef GUI_H_
#define GUI_H_

#include <cstdio>

#include <Windows.h>
#include "../../../includes/ImGui/imgui.h"
#include "../../../includes/ImGui/imgui_impl_win32.h"
#include "../../../includes/ImGui/imgui_impl_opengl3.h"

#include "../Modules/Sprint/Sprint.h"

namespace GUI
{
	//
	// Management functions
	//

	bool init(HWND wnd_handle);
	void shutdown();
	static int tabs = 0;
	//
	// Global functions
	//

	void draw();

	//
	// Get & Set functions
	//

	bool getIsInit();
	bool getDoDraw();

	static bool isToggled = false;

	void setDoDraw(bool new_value);

	void hudDraw();
}

#endif