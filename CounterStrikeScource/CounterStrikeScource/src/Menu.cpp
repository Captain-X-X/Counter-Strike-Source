#include "pch.h"
#include "Menu.h"
#include "Hacks.h"
#include "CSS.h"
namespace Menuc
{
	void RenderImGuiMenu(bool& bOpen)
	{
		ImGui::SetNextWindowSize({ 686, 435 });
		ImGui::Begin("Simple CSS", &bOpen, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
		if (ImGui::BeginTabBar("tabbar1"))
		{
			if (ImGui::BeginTabItem("Local Player"))
			{
				ImGui::Checkbox("BHop", &Hacks::bBHop);
				ImGui::Checkbox("Crosshair", &ESP::bCrosshair);
				ImGui::Checkbox("Triggerbot", &Aimbot::bAutoShoot);
				ImGui::Checkbox("Aimbot", &Aimbot::bAimbot);
				ImGui::EndTabItem();
			}

			if (ImGui::BeginTabItem("Misc"))
			{
				ImGui::SeparatorText("Game Testing");
				viewAngles* vAngles = *(viewAngles**)ClientViewAngles;
				if (ImGui::Button("Reset Cam"))
				{
					vAngles->viewAngles.x = 0.0f;
					vAngles->viewAngles.y = 0.0f;
					vAngles->viewAngles.z = 0.0f;
				}

				ImGui::SeparatorText("Memory Testing");
				if (ImGui::Button("Dump Entitys"))
				{
					CounterStrikeSourceSE::dumpEntitys();
				}
				if (ImGui::Button("TestPrintDev"))
				{
					CounterStrikeSourceSE::testPrint("Hello, World!");
				}
				if (ImGui::Button("Get number of clients"))
				{
					printf("number of players[%i]\n", CounterStrikeSourceSE::getNumberOfPlayersAlive());
				}
				ImGui::EndTabItem();
			}
			ImGui::EndTabBar();
		}
		ImGui::End();
	}
}