#include "spxpch.h"

#include "Spixii.h"

class Sandbox : public Spixii::Application
{
public:
    Sandbox()
    {
    }

    ~Sandbox()
    {
    }

private:
};

Spixii::Application *Spixii::CreateApplication()
{
    return new Sandbox();
}