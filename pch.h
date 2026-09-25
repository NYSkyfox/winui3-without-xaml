#pragma once

// Windows SDK 基础头（提供 wWinMain、HINSTANCE 等）
// 注意：必须在 C++/WinRT 头之前 include，且 NOMINMAX 应在 vcxproj 中定义，
// 否则 Windows.h 会把 max/min 定义为宏，破坏 std::max/min。
#include <Windows.h>

// Windows.h 里定义了 GetCurrentTime 宏，与 WinUI 3 的方法名冲突，需要 undef
#undef GetCurrentTime

// C++/WinRT 投影头：WindowsAppSDK 的 WinMD 会被自动发现并生成 <winrt/...> 头
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Foundation.Collections.h>
#include <winrt/Windows.UI.Xaml.Interop.h>

// WinUI 3 核心
#include <winrt/Microsoft.UI.Xaml.h>
#include <winrt/Microsoft.UI.Xaml.Controls.h>
#include <winrt/Microsoft.UI.Xaml.Controls.Primitives.h>
#include <winrt/Microsoft.UI.Xaml.Media.h>   // SolidColorBrush 等
#include <winrt/Microsoft.UI.Xaml.XamlTypeInfo.h>
#include <winrt/Microsoft.UI.Xaml.Markup.h>
