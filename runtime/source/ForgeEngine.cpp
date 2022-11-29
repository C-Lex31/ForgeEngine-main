 //#include <iostream>
#include <ForgeEngine.h>
#include "platform/windows/winInput.h"
#include "Forge2D.h"
#include "Forge3D.h"
#include "GLFW/glfw3.h"
#include "core/client/entry_point.h"
class Engine_Layer :public Forge::Layer
{
public:
	Engine_Layer()
		:Layer("Base")
	{
	
	};

	void OnUpdate(Forge::Timestep ts) override
	{
	//	glm::mat4 model = glm::mat4(1.0f);
		//model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));
		//rotation += 0.5f;

	/*	static	glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		m_ColorShader->bind();//-----------------------------------CAUTION--------------------
		m_ColorShader->UploadUniformFloat4("u_Color", m_SquareColor);
		for (int y = 0; y < 20; y++)
		{
			for (int x = 0; x < 20; x++)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;					
				Forge::renderer::IR_Submit(SQvertexArray, m_ColorShader, transform);
			}
		}
		m_Texture2D->bind();*/
	
	}

	virtual void OnGUIRender () override
	{
		/*ForgeUI::Begin("Settings");
	    ForgeUI::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	    ForgeUI::End();*/
	}

	void OnEvent(Forge::Event& event)override
	{
		
	}
	bool OnMouseMovedEvent(Forge::MouseMovedEvent& event)
	{
		
		
	}
	

private:


	

	
};

class Sandbox :public Forge::Application
{
public:
	Sandbox()
	{
		//PushLayer(new Engine_Layer());
		PushLayer(new Forge2D());
	}
	~Sandbox()
	{

	}
	
};

Forge::Application* Forge::CreateApplication()
{
	return new Sandbox();
}
