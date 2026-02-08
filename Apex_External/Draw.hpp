#pragma once
#include "OS-ImGui/OS-ImGui.h"

void DrawBox(float x1, float y1, float x2, float y2, ULONG color, float strokeWidth) {
    ImGui::GetBackgroundDrawList()->AddLine(ImVec2(x1, y1), ImVec2(x2, y1), color, strokeWidth);
    ImGui::GetBackgroundDrawList()->AddLine(ImVec2(x1, y2), ImVec2(x2, y2), color, strokeWidth);
    float height = y2 - y1;
    float smallLineLength = height;

    ImGui::GetBackgroundDrawList()->AddLine(ImVec2(x1, y1), ImVec2(x1, y1 + smallLineLength), color, strokeWidth);
    ImGui::GetBackgroundDrawList()->AddLine(ImVec2(x2, y1), ImVec2(x2, y1 + smallLineLength), color, strokeWidth);

    ImGui::GetBackgroundDrawList()->AddLine(ImVec2(x1, y2 - smallLineLength), ImVec2(x1, y2), color, strokeWidth);
    ImGui::GetBackgroundDrawList()->AddLine(ImVec2(x2, y2 - smallLineLength), ImVec2(x2, y2), color, strokeWidth);
}