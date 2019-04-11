#pragma once


#ifdef SP_PLATFORM_WINDOWS
	
	extern Spixii::Application* Spixii::CreateApplication();

	int main(int argc, char** argv)
	{
		Spixii::Application* app = Spixii::CreateApplication();
		app->Run();
		delete app;
	}

#endif