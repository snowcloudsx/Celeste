#include "GUI.h"
#include <iostream>
#include <chrono>
#include "../../includes/Fonts/icons.h" //icons
#include "globals.h"
#include "UIFunctions.h"
#include "../../../includes/Fonts/mFont.h"
using namespace ImGui;
static bool is_init{};
static bool do_draw{true};

//yes build
// Management functions
// now lets fix errors yes get any omppoinets

// did you fix it?

// 1 sec ill be back in 10 mins 
void SetupImGuiStyle()
{
	// Purple Comfy style by RegularLunar from ImThemes
	ImGuiStyle& style = ImGui::GetStyle();

	style.Alpha = 1.0f;
	style.DisabledAlpha = 0.1000000014901161f;
	style.WindowPadding = ImVec2(8.0f, 8.0f);
	style.WindowRounding = 10.0f;
	style.WindowBorderSize = 0.0f;
	style.WindowMinSize = ImVec2(30.0f, 30.0f);
	style.WindowTitleAlign = ImVec2(0.5f, 0.5f);
	style.WindowMenuButtonPosition = ImGuiDir_Right;
	style.ChildRounding = 5.0f;
	style.ChildBorderSize = 1.0f;
	style.PopupRounding = 10.0f;
	style.PopupBorderSize = 0.0f;
	style.FramePadding = ImVec2(5.0f, 3.5f);
	style.FrameRounding = 5.0f;
	style.FrameBorderSize = 0.0f;
	style.ItemSpacing = ImVec2(5.0f, 4.0f);
	style.ItemInnerSpacing = ImVec2(5.0f, 5.0f);
	style.CellPadding = ImVec2(4.0f, 2.0f);
	style.IndentSpacing = 5.0f;
	style.ColumnsMinSpacing = 5.0f;
	style.ScrollbarSize = 15.0f;
	style.ScrollbarRounding = 9.0f;
	style.GrabMinSize = 15.0f;
	style.GrabRounding = 5.0f;
	style.TabRounding = 5.0f;
	style.TabBorderSize = 0.0f;
	style.TabMinWidthForCloseButton = 0.0f;
	style.ColorButtonPosition = ImGuiDir_Right;
	style.ButtonTextAlign = ImVec2(0.5f, 0.5f);
	style.SelectableTextAlign = ImVec2(0.0f, 0.0f);

	style.Colors[ImGuiCol_Text] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
	style.Colors[ImGuiCol_TextDisabled] = ImVec4(1.0f, 1.0f, 1.0f, 0.3605149984359741f);
	style.Colors[ImGuiCol_WindowBg] = ImVec4(0.09803921729326248f, 0.09803921729326248f, 0.09803921729326248f, 1.0f);
	style.Colors[ImGuiCol_ChildBg] = ImVec4(1.0f, 0.0f, 0.0f, 0.0f);
	style.Colors[ImGuiCol_PopupBg] = ImVec4(0.09803921729326248f, 0.09803921729326248f, 0.09803921729326248f, 1.0f);
	style.Colors[ImGuiCol_Border] = ImVec4(0.501960813999176f, 0.3019607961177826f, 1.0f, 0.5490196347236633f);
	style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
	style.Colors[ImGuiCol_FrameBg] = ImVec4(0.1568627506494522f, 0.1568627506494522f, 0.1568627506494522f, 1.0f);
	style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.3803921639919281f, 0.4235294163227081f, 0.572549045085907f, 0.5490196347236633f);
	style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.501960813999176f, 0.3019607961177826f, 1.0f, 0.5490196347236633f);
	style.Colors[ImGuiCol_TitleBg] = ImVec4(0.09803921729326248f, 0.09803921729326248f, 0.09803921729326248f, 1.0f);
	style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.09803921729326248f, 0.09803921729326248f, 0.09803921729326248f, 1.0f);
	style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.2588235437870026f, 0.2588235437870026f, 0.2588235437870026f, 0.0f);
	style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
	style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.1568627506494522f, 0.1568627506494522f, 0.1568627506494522f, 0.0f);
	style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.1568627506494522f, 0.1568627506494522f, 0.1568627506494522f, 1.0f);
	style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.2352941185235977f, 0.2352941185235977f, 0.2352941185235977f, 1.0f);
	style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.294117659330368f, 0.294117659330368f, 0.294117659330368f, 1.0f);
	style.Colors[ImGuiCol_CheckMark] = ImVec4(0.501960813999176f, 0.3019607961177826f, 1.0f, 0.5490196347236633f);
	style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.501960813999176f, 0.3019607961177826f, 1.0f, 0.5490196347236633f);
	style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.501960813999176f, 0.3019607961177826f, 1.0f, 0.5490196347236633f);
	style.Colors[ImGuiCol_Button] = ImVec4(0.501960813999176f, 0.3019607961177826f, 1.0f, 0.5490196347236633f);
	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.501960813999176f, 0.3019607961177826f, 1.0f, 0.5490196347236633f);
	style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.501960813999176f, 0.3019607961177826f, 1.0f, 0.5490196347236633f);
	style.Colors[ImGuiCol_Header] = ImVec4(0.501960813999176f, 0.3019607961177826f, 1.0f, 0.5490196347236633f);
	style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.501960813999176f, 0.3019607961177826f, 1.0f, 0.5490196347236633f);
	style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.501960813999176f, 0.3019607961177826f, 1.0f, 0.5490196347236633f);
	style.Colors[ImGuiCol_Separator] = ImVec4(0.501960813999176f, 0.3019607961177826f, 1.0f, 0.5490196347236633f);
	style.Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.501960813999176f, 0.3019607961177826f, 1.0f, 0.5490196347236633f);
	style.Colors[ImGuiCol_SeparatorActive] = ImVec4(0.501960813999176f, 0.3019607961177826f, 1.0f, 0.5490196347236633f);
	style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.501960813999176f, 0.3019607961177826f, 1.0f, 0.5490196347236633f);
	style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.501960813999176f, 0.3019607961177826f, 1.0f, 0.5490196347236633f);
	style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.501960813999176f, 0.3019607961177826f, 1.0f, 0.5490196347236633f);
	style.Colors[ImGuiCol_Tab] = ImVec4(0.501960813999176f, 0.3019607961177826f, 1.0f, 0.5490196347236633f);
	style.Colors[ImGuiCol_TabHovered] = ImVec4(0.501960813999176f, 0.3019607961177826f, 1.0f, 0.5490196347236633f);
	style.Colors[ImGuiCol_TabActive] = ImVec4(0.501960813999176f, 0.3019607961177826f, 1.0f, 0.5490196347236633f);
	style.Colors[ImGuiCol_TabUnfocused] = ImVec4(0.0f, 0.4509803950786591f, 1.0f, 0.0f);
	style.Colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.1333333402872086f, 0.2588235437870026f, 0.4235294163227081f, 0.0f);
	style.Colors[ImGuiCol_PlotLines] = ImVec4(0.294117659330368f, 0.294117659330368f, 0.294117659330368f, 1.0f);
	style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.501960813999176f, 0.3019607961177826f, 1.0f, 0.5490196347236633f);
	style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.501960813999176f, 0.3019607961177826f, 1.0f, 0.5490196347236633f);
	style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.7372549176216125f, 0.6941176652908325f, 0.886274516582489f, 0.5490196347236633f);
	style.Colors[ImGuiCol_TableHeaderBg] = ImVec4(0.1882352977991104f, 0.1882352977991104f, 0.2000000029802322f, 1.0f);
	style.Colors[ImGuiCol_TableBorderStrong] = ImVec4(0.501960813999176f, 0.3019607961177826f, 1.0f, 0.5490196347236633f);
	style.Colors[ImGuiCol_TableBorderLight] = ImVec4(0.501960813999176f, 0.3019607961177826f, 1.0f, 0.2901960909366608f);
	style.Colors[ImGuiCol_TableRowBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
	style.Colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.0f, 1.0f, 1.0f, 0.03433477878570557f);
	style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.501960813999176f, 0.3019607961177826f, 1.0f, 0.5490196347236633f);
	style.Colors[ImGuiCol_DragDropTarget] = ImVec4(1.0f, 1.0f, 0.0f, 0.8999999761581421f);
	style.Colors[ImGuiCol_NavHighlight] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
	style.Colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.0f, 1.0f, 1.0f, 0.699999988079071f);
	style.Colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.800000011920929f, 0.800000011920929f, 0.800000011920929f, 0.2000000029802322f);
	style.Colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.800000011920929f, 0.800000011920929f, 0.800000011920929f, 0.3499999940395355f);

	ImGuiIO& io = ImGui::GetIO();

	static const ImWchar icons_ranges[] = { 0xf000, 0xf3ff, 0 };
	ImFontConfig icons_config;

	ImFontConfig CustomFont;
	CustomFont.FontDataOwnedByAtlas = false;

	icons_config.MergeMode = true;
	icons_config.PixelSnapH = true;
	icons_config.OversampleH = 3;
	icons_config.OversampleV = 3;

	io.Fonts->AddFontFromMemoryTTF(const_cast<std::uint8_t*>(mFont), sizeof(mFont), 15, &CustomFont);
	io.Fonts->AddFontFromMemoryCompressedTTF(font_awesome_data, font_awesome_size, 32.5f, &icons_config, icons_ranges);

	io.Fonts->AddFontDefault();
}
bool GUI::init(HWND wnd_handle)
{
	if (is_init)
		return false;

	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplWin32_Init(wnd_handle);
	ImGui_ImplOpenGL3_Init();
	SetupImGuiStyle();

	is_init = true;

	return false;
}

void GUI::shutdown()
{
	if (!is_init)
		return;

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

	is_init = false;
}

//
// Global functions
//

void RenderBlockingBackdrop() {
	ImGuiIO& io = ImGui::GetIO();

	// Create a full-screen, invisible window
	ImGui::SetNextWindowPos(ImVec2(0, 0));
	ImGui::SetNextWindowSize(ImVec2(io.DisplaySize.x, io.DisplaySize.y));
	ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.2f, 0.2f, 0.2f, 0.8f)); // Semi-transparent gray
	if (ImGui::Begin("Backdrop", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoMouseInputs)) {
		// No content needed, just block input
		ImGui::End();
	}
	ImGui::PopStyleColor();
}

void GUI::draw()
{
	if (!do_draw)
		return;

	if (GetAsyncKeyState(VK_DELETE) & 0x0001) {
		GUI::isToggled = !GUI::isToggled;
	}

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();


	auto start = std::chrono::system_clock::now();
	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;
	std::time_t end_time = std::chrono::system_clock::to_time_t(end);

	ImGui::SetNextWindowPos({ 15, 15 });
	ImGui::SetNextWindowSize({ 296,25 });

	ImGui::Begin("WaterMark", NULL, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove);
	{
		ImGui::Text("Velecent.rip | %s", std::ctime(&end_time));
	}

	ImGui::End();

	if (GUI::isToggled) {

		ImGui::SetNextWindowPos(ImVec2(50,50), ImGuiCond_Once);
		ImGui::SetNextWindowSize(ImVec2(800, 500), ImGuiCond_Once);
		ImGui::SetNextWindowBgAlpha(1.0f);

		ImGui::Begin("##Main", &globals.active, ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar);
		{
			// Header Child with "Velecent.rip"
			ImGui::BeginChild("##header", ImVec2(0, 50), true);
			{
				ImGui::SetCursorPosY(15); // Center vertically in the 50px height
				CenterText("Velecent.rip");
			}
			ImGui::EndChild();

			// Sidebar and Content Layout
			ImGui::BeginChild("##main_layout", ImVec2(0, 0), false); // Full remaining height
			{
				// Sidebar (vertical button panel)
				ImGui::BeginChild("##sidebar", ImVec2(126, 0), true, ImGuiWindowFlags_NoScrollbar);
				{
					ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 10));
					ImGui::SetCursorPosY(20);

					if (BetterButton(ICON_FA_CROSSHAIRS)) {
						globals.page = 0;
						globals.subPage = 1;
					}
					if (ImGui::IsItemHovered()) ImGui::SetTooltip("Combat Modules");

					if (BetterButton(ICON_FA_WHEELCHAIR)) {
						globals.page = 3;
						globals.subPage = 4;
					}
					if (ImGui::IsItemHovered()) ImGui::SetTooltip("Movement Modules");

					if (BetterButton(ICON_FA_EYE)) {
						globals.page = 4;
						globals.subPage = 4;
					}
					if (ImGui::IsItemHovered()) ImGui::SetTooltip("Visual Modules (soon)");

					if (BetterButton(ICON_FA_COGS)) {
						globals.page = 2;
						globals.subPage = 0;
					}
					if (ImGui::IsItemHovered()) ImGui::SetTooltip("Settings");

					ImGui::PopStyleVar();
				}
				ImGui::EndChild();

				ImGui::SameLine();
				ImGui::BeginChild("##content", ImVec2(0, 0), true);
				{
					static bool leftClicker = false;
					static bool rightClicker = false;
					static bool backtrackEnabled = false;
					static bool testedPacks = false;
					static bool Sprint = false;
					static bool disableOnHit = false;
					static bool velocity = false;

					static float cps = 1.0f;
					static float rightCps = 1.0f;
					static float delay = 10.0f;
					static float delayMin = 10.0f;
					static float velX = 0.0f;
					static float velY = 0.0f;
					static float velZ = 0.0f;
//good job

					ImGui::SetCursorPosY(10);
					ImGui::Separator();
					// if you send me the link for the other project i can start making the module base yes you dont need to share this one sure so i can go back and fourth 
					if (globals.page == 0) {
						if (BeginTabBar("CombatTabs", ImGuiTabBarFlags_FittingPolicyScroll)) {
							if (globals.subPage == 1) {
								if (BeginTabItem("Clicker")) {
									Checkbox("Left Clicker", &leftClicker);
									Text("Left CPS");

									ImGui::Spacing();
									Checkbox("Right Clicker", &rightClicker);
									Text("Right CPS");									EndTabItem();
								}
								if (BeginTabItem("Backtrack")) {
									Checkbox("Backtrack", &backtrackEnabled);
									ImGui::Text("Delay Min");
									ImGui::Text("Delay Max");									Checkbox("Disable on Hit", &disableOnHit);
									Checkbox("Target Packets Only", &testedPacks);
									EndTabItem();
								}
							}
							EndTabBar();
						}
					}
					else if (globals.page == 3) {
						if (BeginTabBar("MovementTabs")) {
							if (globals.subPage == 4) {
								if (BeginTabItem("Ground")) {
									Checkbox("Sprint", &Sprint);
									ImGui::Separator();
									Checkbox("Velocity", &velocity);
									ImGui::Text("X Value");
									ImGui::Text("Y Value");
									ImGui::Text("Z Value");
									EndTabItem();
								}
								if (BeginTabItem("Air")) {
									ImGui::Text("Coming Soon");
									EndTabItem();
								}
							}
							EndTabBar();
						}
					}
					else if (globals.page == 4) {
						ImGui::Text("Visual Modules - Coming Soon");
					}
					else if (globals.page == 2) {
						ImGui::SetCursorPosX(50);
						ImGui::Text("Select Theme:");

						ImGui::Spacing();
					}
				}
				ImGui::EndChild();
			}
			ImGui::EndChild();
		}
		ImGui::End();
		
	}

	ImGui::EndFrame();
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

//
// Get & Set functions
//

bool GUI::getIsInit()
{
	return is_init;
}


//it works

// was being big back grabbing ice cream
bool GUI::getDoDraw()
{
	return do_draw;
}

void GUI::setDoDraw(bool new_value)
{
	do_draw = new_value;
}

void GUI::CenterText(const char* text) {
	if (!text) return;
	float width = ImGui::CalcTextSize(text).x;
	ImGui::SetCursorPosX((ImGui::GetWindowWidth() - width) * 0.5f);
	ImGui::Text(text);
}