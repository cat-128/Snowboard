#include "interface.h"

void Interface::init(SDL_Window* window, SDL_Renderer* renderer) {

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	
	SetStyles();

	ImGui_ImplSDL3_InitForSDLRenderer(window, renderer);
	ImGui_ImplSDLRenderer3_Init(renderer);
}

void Interface::processEvent(SDL_Event* event) {
	ImGui_ImplSDL3_ProcessEvent(event);
}

void Interface::StartFrame() {
	ImGui_ImplSDLRenderer3_NewFrame();
	ImGui_ImplSDL3_NewFrame();
	ImGui::NewFrame();
}

void Interface::drawFrame(const char* title) {
	ImGuiViewport* viewport = ImGui::GetMainViewport();

	ImGui::SetNextWindowPos(viewport->WorkPos);
	ImGui::SetNextWindowSize(viewport->WorkSize);

	// yo btw if u reading ts, flags are tuff
	ImGuiWindowFlags flags =
		ImGuiWindowFlags_NoTitleBar |
		ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_NoCollapse;

	ImGui::Begin(title, nullptr, flags);
	ImGui::Text("snowboard");

	if (ImGui::Button("Play audio")) {

	}

	ImGui::End();
}

void Interface::ImGuiRender(SDL_Renderer* renderer) {
	ImGui::Render();
	ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), renderer);
}

void Interface::cleanUp() {
	ImGui_ImplSDLRenderer3_Shutdown();
	ImGui_ImplSDL3_Shutdown();
	ImGui::DestroyContext();
}

void Interface::SetStyles() {
	ImGuiStyle& style = ImGui::GetStyle();

	style.Alpha = 1.0f;
	style.DisabledAlpha = 0.6f;
	style.WindowPadding = ImVec2(8.0f, 8.0f);
	style.WindowRounding = 0.0f;
	style.WindowBorderSize = 0.0f;
	style.WindowMinSize = ImVec2(32.0f, 32.0f);
	style.WindowTitleAlign = ImVec2(0.0f, 0.5f);
	style.WindowMenuButtonPosition = ImGuiDir_Left;
	style.ChildRounding = 0.0f;
	style.ChildBorderSize = 1.0f;
	style.PopupRounding = 0.0f;
	style.PopupBorderSize = 0.0f;
	style.FramePadding = ImVec2(4.0f, 3.0f);
	style.FrameRounding = 4.0f;
	style.FrameBorderSize = 0.0f;
	style.ItemSpacing = ImVec2(8.0f, 4.0f);
	style.ItemInnerSpacing = ImVec2(4.0f, 4.0f);
	style.CellPadding = ImVec2(4.0f, 2.0f);
	style.IndentSpacing = 21.0f;
	style.ColumnsMinSpacing = 6.0f;
	style.ScrollbarSize = 14.0f;
	style.ScrollbarRounding = 9.0f;
	style.GrabMinSize = 10.0f;
	style.GrabRounding = 4.0f;
	style.TabRounding = 4.0f;
	style.TabBorderSize = 0.0f;
	style.ColorButtonPosition = ImGuiDir_Right;
	style.ButtonTextAlign = ImVec2(0.5f, 0.5f);
	style.SelectableTextAlign = ImVec2(0.0f, 0.0f);

	style.Colors[ImGuiCol_Text] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
	style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.7294118f, 0.7490196f, 0.7372549f, 1.0f);
	style.Colors[ImGuiCol_WindowBg] = ImVec4(0.08627451f, 0.08627451f, 0.08627451f, 0.94f);
	style.Colors[ImGuiCol_ChildBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
	style.Colors[ImGuiCol_PopupBg] = ImVec4(0.078431375f, 0.078431375f, 0.078431375f, 0.94f);
	style.Colors[ImGuiCol_Border] = ImVec4(0.2f, 0.2f, 0.2f, 0.5f);
	style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
	style.Colors[ImGuiCol_FrameBg] = ImVec4(0.70980394f, 0.3882353f, 0.3882353f, 0.54f);
	style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.8392157f, 0.65882355f, 0.65882355f, 0.4f);
	style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.8392157f, 0.65882355f, 0.65882355f, 0.67f);
	style.Colors[ImGuiCol_TitleBg] = ImVec4(0.46666667f, 0.21960784f, 0.21960784f, 0.67f);
	style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.46666667f, 0.21960784f, 0.21960784f, 1.0f);
	style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.46666667f, 0.21960784f, 0.21960784f, 0.67f);
	style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.3372549f, 0.15686275f, 0.15686275f, 1.0f);
	style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.019607844f, 0.019607844f, 0.019607844f, 0.53f);
	style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.30980393f, 0.30980393f, 0.30980393f, 1.0f);
	style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.40784314f, 0.40784314f, 0.40784314f, 1.0f);
	style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.50980395f, 0.50980395f, 0.50980395f, 1.0f);
	style.Colors[ImGuiCol_CheckMark] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
	style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.70980394f, 0.3882353f, 0.3882353f, 1.0f);
	style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.8392157f, 0.65882355f, 0.65882355f, 1.0f);
	style.Colors[ImGuiCol_Button] = ImVec4(0.46666667f, 0.21960784f, 0.21960784f, 0.65f);
	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.70980394f, 0.3882353f, 0.3882353f, 0.65f);
	style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.2f, 0.2f, 0.2f, 0.5f);
	style.Colors[ImGuiCol_Header] = ImVec4(0.70980394f, 0.3882353f, 0.3882353f, 0.54f);
	style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.8392157f, 0.65882355f, 0.65882355f, 0.65f);
	style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.8392157f, 0.65882355f, 0.65882355f, 0.0f);
	style.Colors[ImGuiCol_Separator] = ImVec4(0.42745098f, 0.42745098f, 0.49803922f, 0.5f);
	style.Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.70980394f, 0.3882353f, 0.3882353f, 0.54f);
	style.Colors[ImGuiCol_SeparatorActive] = ImVec4(0.70980394f, 0.3882353f, 0.3882353f, 0.54f);
	style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.70980394f, 0.3882353f, 0.3882353f, 0.54f);
	style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.8392157f, 0.65882355f, 0.65882355f, 0.66f);
	style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.8392157f, 0.65882355f, 0.65882355f, 0.66f);
	style.Colors[ImGuiCol_Tab] = ImVec4(0.70980394f, 0.3882353f, 0.3882353f, 0.54f);
	style.Colors[ImGuiCol_TabHovered] = ImVec4(0.8392157f, 0.65882355f, 0.65882355f, 0.66f);
	style.Colors[ImGuiCol_TabActive] = ImVec4(0.8392157f, 0.65882355f, 0.65882355f, 0.66f);
	style.Colors[ImGuiCol_TabUnfocused] = ImVec4(0.06666667f, 0.09803922f, 0.14901961f, 0.97f);
	style.Colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.13725491f, 0.25882354f, 0.41960785f, 1.0f);
	style.Colors[ImGuiCol_PlotLines] = ImVec4(0.60784316f, 0.60784316f, 0.60784316f, 1.0f);
	style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.0f, 0.42745098f, 0.34901962f, 1.0f);
	style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.8980392f, 0.69803923f, 0.0f, 1.0f);
	style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.0f, 0.6f, 0.0f, 1.0f);
	style.Colors[ImGuiCol_TableHeaderBg] = ImVec4(0.1882353f, 0.1882353f, 0.2f, 1.0f);
	style.Colors[ImGuiCol_TableBorderStrong] = ImVec4(0.30980393f, 0.30980393f, 0.34901962f, 1.0f);
	style.Colors[ImGuiCol_TableBorderLight] = ImVec4(0.22745098f, 0.22745098f, 0.24705882f, 1.0f);
	style.Colors[ImGuiCol_TableRowBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
	style.Colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.0f, 1.0f, 1.0f, 0.06f);
	style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.25882354f, 0.5882353f, 0.9764706f, 0.35f);
	style.Colors[ImGuiCol_DragDropTarget] = ImVec4(1.0f, 1.0f, 0.0f, 0.9f);
	style.Colors[ImGuiCol_NavHighlight] = ImVec4(0.40784314f, 0.40784314f, 0.40784314f, 1.0f);
	style.Colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.0f, 1.0f, 1.0f, 0.7f);
	style.Colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.8f, 0.8f, 0.8f, 0.2f);
	style.Colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.8f, 0.8f, 0.8f, 0.35f);
}