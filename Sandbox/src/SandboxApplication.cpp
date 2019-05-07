#define SPX_APPLICATION_IMPLEMENTATION
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

    virtual void Initialize() override
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