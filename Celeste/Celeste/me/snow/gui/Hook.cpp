
#include "GUI.h"

#include <gl/GL.h>

#include "Hook.h"
#include "../../../includes/MinHook.h"

typedef BOOL(__stdcall* TWglSwapBuffers) (HDC hDc);

static bool is_init{};
static HWND wnd_handle{};
static WNDPROC origin_wndproc{};
void* p_swap_buffers{};
TWglSwapBuffers origin_wglSwapBuffers{};

static LRESULT __stdcall WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
static bool __stdcall wglSwapBuffers(HDC hDc);

//
// Management functions
//

bool Hook::init()
{
	if (is_init)
		return false;

	/* WndProc */
	{
		// Older versions of mincraft
		wnd_handle = FindWindowA("LWJGL", nullptr);

		/* If failed to get window handle, attempt using window class used by more recent versions of minecraft */
		if (!wnd_handle)
		{
			wnd_handle = FindWindowA("GLFW30", nullptr);

			/* At this point cannot find minecraft window */
			if (!wnd_handle)
			{
				printf("[-] Failed to get window handle\n");
				return true;
			}
		}

		origin_wndproc = (WNDPROC)SetWindowLongPtrW(wnd_handle, GWLP_WNDPROC, (LONG_PTR)WndProc);
	}

	MH_Initialize();

	/* wglSwapBuffers */
	{
		p_swap_buffers = (void*)GetProcAddress(GetModuleHandleA("opengl32.dll"), "wglSwapBuffers");

		if (p_swap_buffers == nullptr)
		{
			printf("[-] Failed to get wglSwapBuffers' address\n");
			return true;
		}

		MH_CreateHook(p_swap_buffers, &wglSwapBuffers, (LPVOID*)&origin_wglSwapBuffers);
	}

	MH_EnableHook(MH_ALL_HOOKS);

	is_init = true;

	return false;
}

void Hook::shutdown()
{
	if (!is_init)
		return;

	SetWindowLongPtrW(wnd_handle, GWLP_WNDPROC, (LONG_PTR)origin_wndproc);
	MH_DisableHook(MH_ALL_HOOKS);
	MH_RemoveHook(MH_ALL_HOOKS);

	is_init = false;
}

//
// Get functions
//

bool Hook::getIsInit()
{
	return is_init;
}

//
// Hooks
//

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

static bool g_bRawInputInitialized = false;
static RAWINPUTDEVICE g_RawInputDevices[1];

LRESULT __stdcall WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    static bool bCursorWasVisible = false;

    if (GUI::getIsInit())
    {
        /* Toggle menu with H key */
        if (msg == WM_KEYDOWN && wParam == 'H')
        {
            bool newState = !GUI::isToggled;
            GUI::setDoDraw(newState);

            // Initialize raw input blocking on first toggle
            if (!g_bRawInputInitialized)
            {
                g_RawInputDevices[0].usUsagePage = 0x01; // HID_USAGE_PAGE_GENERIC
                g_RawInputDevices[0].usUsage = 0x02;     // HID_USAGE_GENERIC_MOUSE
                g_RawInputDevices[0].dwFlags = RIDEV_REMOVE; // Remove when not needed
                g_RawInputDevices[0].hwndTarget = nullptr;

                if (RegisterRawInputDevices(g_RawInputDevices, 1, sizeof(g_RawInputDevices[0])))
                {
                    g_bRawInputInitialized = true;
                }
            }

            // Toggle raw input blocking
            if (g_bRawInputInitialized)
            {
                g_RawInputDevices[0].dwFlags = newState ? RIDEV_REMOVE : 0;
                RegisterRawInputDevices(g_RawInputDevices, 1, sizeof(g_RawInputDevices[0]));
            }

            // Handle cursor visibility
            if (newState)
            {
                bCursorWasVisible = ::ShowCursor(TRUE) >= 0;
                if (!bCursorWasVisible) ::ShowCursor(TRUE);
                // Clip cursor to window
                RECT rect;
                GetClientRect(hWnd, &rect);
                ClientToScreen(hWnd, reinterpret_cast<POINT*>(&rect.left));
                ClientToScreen(hWnd, reinterpret_cast<POINT*>(&rect.right));
                ClipCursor(&rect);
            }
            else
            {
                if (!bCursorWasVisible)
                {
                    ::ShowCursor(FALSE);
                }
                ClipCursor(nullptr); // Release cursor clip
            }
            return true;
        }

        if (GUI::isToggled)
        {
            ImGuiIO& io = ImGui::GetIO();

            // Process input with ImGui
            ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam);

            // Block ALL input when menu is open
            switch (msg)
            {
                // Mouse messages
            case WM_INPUT:
            {
                // Block raw mouse input
                UINT dwSize = 0;
                GetRawInputData((HRAWINPUT)lParam, RID_INPUT, nullptr, &dwSize, sizeof(RAWINPUTHEADER));
                LPBYTE lpb = new BYTE[dwSize];
                if (GetRawInputData((HRAWINPUT)lParam, RID_INPUT, lpb, &dwSize, sizeof(RAWINPUTHEADER)) == dwSize)
                {
                    RAWINPUT* raw = (RAWINPUT*)lpb;
                    if (raw->header.dwType == RIM_TYPEMOUSE)
                    {
                        delete[] lpb;
                        return 0;
                    }
                }
                delete[] lpb;
                break;
            }

            case WM_MOUSEMOVE:
            case WM_MOUSEHOVER:
            case WM_MOUSELEAVE:
            case WM_LBUTTONDOWN: case WM_LBUTTONDBLCLK:
            case WM_RBUTTONDOWN: case WM_RBUTTONDBLCLK:
            case WM_MBUTTONDOWN: case WM_MBUTTONDBLCLK:
            case WM_XBUTTONDOWN: case WM_XBUTTONDBLCLK:
            case WM_LBUTTONUP:
            case WM_RBUTTONUP:
            case WM_MBUTTONUP:
            case WM_XBUTTONUP:
            case WM_MOUSEWHEEL:
            case WM_MOUSEHWHEEL:
                return true;

            case WM_KEYDOWN:
            case WM_KEYUP:
            case WM_SYSKEYDOWN:
            case WM_SYSKEYUP:
            case WM_CHAR:
                if (io.WantCaptureKeyboard)
                    return true;
                break;

            case WM_SETCURSOR:
                if (LOWORD(lParam) == HTCLIENT)
                {
                    SetCursor(LoadCursor(nullptr, IDC_ARROW));
                    return true;
                }
                break;
            }
        }
    }

    return CallWindowProcA(origin_wndproc, hWnd, msg, wParam, lParam);
}


bool __stdcall wglSwapBuffers(HDC hDc)
{
	HGLRC origin_context{ wglGetCurrentContext() };
	static HGLRC new_context{};

	if (static bool was_init{}; was_init == false)
	{
		new_context = wglCreateContext(hDc);
		wglMakeCurrent(hDc, new_context);

		GLint viewport[4];
		glGetIntegerv(GL_VIEWPORT, viewport);
		glViewport(0, 0, viewport[2], viewport[3]);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0, viewport[2], viewport[3], 0, -1, 1);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glDisable(GL_DEPTH_TEST);

		GUI::init(wnd_handle);

		was_init = true;
	}
	else
	{
		wglMakeCurrent(hDc, new_context);
		GUI::draw();
	}

	wglMakeCurrent(hDc, origin_context);

	return origin_wglSwapBuffers(hDc);
}
