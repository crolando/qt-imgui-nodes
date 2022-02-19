#include <QtImGui.h>
#include <imgui.h>
#include <QApplication>
#include <QTimer>
#include <QSurfaceFormat>
#include <QOpenGLWidget>
#include <QOpenGLExtraFunctions>
#include <QObject>
#include <QDebug>
#include <imgui_node_editor.h>
#include <memory>
#include <texture_manager.h>

class NodosWidget : public QOpenGLWidget, private QOpenGLExtraFunctions
{
    Q_OBJECT

public:
    // re-declare the baseclass constructor and override the default focus policy to pass keyboard events to the event handlers.
    NodosWidget(QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags()) : QOpenGLWidget(parent, f)
    {
        setFocusPolicy(Qt::StrongFocus);
    }

    void shutdown();

protected:
    void initializeGL() override;
    void paintGL() override;


private:
    ImVec4 clear_color = ImColor(114, 144, 154);
    texture_manager textures;
    void NodeWidget_Initialize();
    void NodeWidget_Finalize();
    void NodeWidget_Frame();
};
