#define SPX_APPLICATION_IMPLEMENTATION
#include "Spixii.h"

#include <iostream>

class foo
{
public:
    foo(int a)
        : m_a(a)
    {
    }
    int m_a;
};

class Sandbox : public Spixii::Application
{
public:
    Sandbox()
    {
    }

    ~Sandbox()
    {
    }

    virtual void OnStatup() override
    {
    }

    virtual void OnUpdate() override
    {
    }

    virtual void OnShutdown() override
    {
    }

    virtual void OnEvent(Spixii::Event &event) override
    {
    }

private:
};

Spixii::Application *Spixii::CreateApplication()
{
    return new Sandbox();
}