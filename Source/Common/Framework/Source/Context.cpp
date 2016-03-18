/************************************************************
*                                                           *
*   Copyright (C) Steven Frost 2016. All Rights Reserved.   *
*                                                           *
************************************************************/

#include "FrameworkPch.h"

#include <Framework/Context.h>

#include <cmath>
#include <cstdint>
#include <stdio.h>

#include <GL/freeglut.h>

#include "Callback.h"

namespace Framework
{

//-----------------------------------------------------------------------------

Context::Context(int argc, char *argv[]) :
    m_width(800), m_height(600), m_caption("OpenGL"), m_scene(std::make_shared<Scene>()), m_previousFrameTime(0)
{
    glutInit(&argc, argv);
}

//-----------------------------------------------------------------------------

void Context::Idle()
{
    m_currentFrameTime = glutGet(GLUT_ELAPSED_TIME);
    uint32_t previousFrameTime = m_previousFrameTime;
    m_previousFrameTime = m_currentFrameTime;

    m_scene->Update(m_currentFrameTime - previousFrameTime);

    glutPostRedisplay();
}

//-----------------------------------------------------------------------------

void Context::Draw()
{
    m_scene->Draw();

    CheckGLError();
    glutSwapBuffers();
}

//-----------------------------------------------------------------------------

void Context::Reshape(int32_t width, int32_t height)
{
    m_width = width;
    m_height = height;

    m_scene->Reshape(width, height);
}

//-----------------------------------------------------------------------------

void Context::Setup(int32_t width, int32_t height, std::string const& caption)
{
    m_width = width;
    m_height = height;
    m_caption = caption;

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_MULTISAMPLE);
    glutInitWindowSize(m_width, m_height);
    m_windowHandle = glutCreateWindow(m_caption.c_str());

    auto instance = Callback::GetInstance();
    instance->RegisterApplication(shared_from_this());

    glutIdleFunc(&Callback::Idle);
    glutDisplayFunc(&Callback::Draw);
    glutReshapeFunc(&Callback::Reshape);

    glutKeyboardUpFunc(&Callback::KeyUp);
    glutKeyboardFunc(&Callback::KeyDown);
    glutSpecialUpFunc(&Callback::SpecialKeyUp);
    glutSpecialFunc(&Callback::SpecialKeyDown);
    glutMouseFunc(&Callback::MouseAction);
    glutMotionFunc(&Callback::MouseMotion);
    glutPassiveMotionFunc(&Callback::PassiveMouseMotion);

    printf("Setup complete. Window created [%dx%d]\n", m_width, m_height);
    printf("OpenGL version: %s\n", glGetString(GL_VERSION));
}

//-----------------------------------------------------------------------------

void Context::Run()
{
    glClearColor(0.5f, 0.6f, 1.6f, 1.0f);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    glEnable(GL_CULL_FACE);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_COLOR_MATERIAL);

    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);

    GLfloat global_ambient[] = { 0.3f, 0.3f, 0.3f, 1.0f };
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);

    glEnable(GL_LIGHTING);
    GLfloat ambience[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat diffuse[]  = { 0.8f, 0.8f, 0.8f, 1.0f };
    GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat position[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambience);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    glEnable(GL_LIGHT0);

    glShadeModel(GL_SMOOTH);
    glEnable(GL_NORMALIZE);

#ifdef ENABLE_FOG
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    GLfloat fogColor[4] = { 0.5f, 0.5f, 0.5f, 1.0f };
    GLfloat density = 0.001f;
    glEnable(GL_FOG);

    glFogi(GL_FOG_MODE, GL_EXP2);
    glFogfv(GL_FOG_COLOR, fogColor);
    glFogf(GL_FOG_DENSITY, density);
    glHint(GL_FOG_HINT, GL_NICEST);
#endif // ENABLE_FOG

    m_scene->Initialise();
    glutMainLoop();
}

//-----------------------------------------------------------------------------

void Context::SetScene(Scene::Ptr const& scene)
{
    m_scene = scene;
}

//-----------------------------------------------------------------------------

void Context::KeyAction(unsigned char key, bool keyDown, int x, int y)
{
    m_scene->KeyAction(key, keyDown, x, y);
}

//-----------------------------------------------------------------------------

void Context::SpecialKeyAction(int key, bool keyDown, int x, int y)
{
    m_scene->SpecialKeyAction(key, keyDown, x, y);
}

//-----------------------------------------------------------------------------

void Context::MouseAction(int button, bool mouseDown, int x, int y)
{
    m_scene->MouseAction(button, mouseDown, x, y);
}

//-----------------------------------------------------------------------------

void Context::MouseMotion(int x, int y)
{
    m_scene->MouseMotion(x, y);
}

//-----------------------------------------------------------------------------

void Context::PassiveMouseMotion(int x, int y)
{
    m_scene->PassiveMouseMotion(x, y);
}

//-----------------------------------------------------------------------------

void Context::CheckGLError()
{
    int n = 0;
    GLenum error = glGetError();
    while (error != GL_NO_ERROR)
    {
        ++n;
        printf("GL Error %i: %s\r\n", n, gluErrorString(error));
        error = glGetError();
    }
}

//-----------------------------------------------------------------------------

} // namespace Framework
