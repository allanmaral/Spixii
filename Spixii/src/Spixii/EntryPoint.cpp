#pragma once

#include "spxpch.h"

#include "Spixii.h"

Spixii::SpixiiSystems      g_systems;
Spixii::ApplicationSystems g_application;

int main(int argc, char **argv)
{
    Spixii::Engine::Initialize();

    Spixii::Engine::s_isRunning = true;

    while(Spixii::Engine::s_isRunning)
    {
        Spixii::Engine::Update();
    }

    Spixii::Engine::Shutdown();

    return 0;
    ;
}