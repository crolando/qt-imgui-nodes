#include <NodosWidget.h>
#include <application.h>

void NodosWidget::initializeGL()
{
    initializeOpenGLFunctions();
    QtImGui::initialize(this);

    // There is a ImGui context with the default font.
    // Build a custom font atlas and replace the default one.
    const ImWchar ranges[] =
    {
        0x0020, 0x00FF, // Basic Latin + Latin Supplement
        0x0104, 0x017C, // Polish characters and more
        0,
    };

    ImFontConfig config;
    config.OversampleH = 4;
    config.OversampleV = 4;
    config.PixelSnapH = false;

    ImFontAtlas* fa = ImGui::GetIO().Fonts;
    fa->AddFontFromFileTTF("..\\qt-imgui-nodes\\Data\\selawk.ttf", 22.0f, &config, ranges);
    fa->Build();

    // Now that there's an opengl context, we can init the node editor
    Application_Initialize();


}

void NodosWidget::paintGL()
{
    QtImGui::newFrame();

    // Clear the viewport
    glViewport(0, 0, width(), height());
    glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
    glClear(GL_COLOR_BUFFER_BIT);

    // This was copied from the frame portion of the blueprint host application
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGuiIO& io = ImGui::GetIO();
    ImGui::SetNextWindowSize(io.DisplaySize);
    ImGui::Begin("Content", nullptr,
        ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoSavedSettings |
        ImGuiWindowFlags_NoBringToFrontOnFocus);

    // Tell imGui to assemble the blueprint drawlist
    Application_Frame();

    // DEV
    //ImGui::ShowStyleEditor();

    ImGui::End();
    ImGui::EndFrame();

    // Tell imGui / QtimGui to paint the drawlist
    ImGui::Render();
}

// cleanup routines
void NodosWidget::shutdown() {
    Application_Finalize();
}
