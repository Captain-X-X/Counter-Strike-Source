#include "pch.h"
#include "Menu.h"
#include "Hacks.h"
#include "CSS.h"
namespace Menuc
{
	void RenderImGuiMenu(bool& bOpen)
	{
		ImGui::Begin("Simple CSS", &bOpen);
		if (ImGui::BeginTabBar("tabbar1"))
		{
			if (ImGui::BeginTabItem("Local Player"))
			{
				ImGui::Checkbox("BHop", &Hacks::bBHop);
				ImGui::Checkbox("Triggerbot", &Hacks::bTriggerbot);
				if (ImGui::Button("Dump Entitys"))
				{
					CounterStrikeSourceSE::dumpEntitys();
				}
				ImGui::EndTabItem();
			}

			if (ImGui::BeginTabItem("Misc"))
			{
				ImGui::EndTabItem();
			}
			ImGui::EndTabBar();
		}
		ImGui::End();
	}
}