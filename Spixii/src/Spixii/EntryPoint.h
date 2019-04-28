#pragma once


#ifdef SPX_PLATFORM_WINDOWS
	
	extern Spixii::Application* Spixii::CreateApplication();

	int main(int argc, char** argv)
	{
		Spixii::Log::Init();
		
		Spixii::Application* app = Spixii::CreateApplication();
		app->Run();
		delete app;
	}

#endif