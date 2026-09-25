// 本示例使用 WindowsAppSDK 2.5.1 + CppWinRT 3.0（原项目为 1.2 / 2.0）。
// 核心 API 在 1.x → 2.x 之间保持稳定，仅需 NuGet 版本升级即可运行。
// 注意：WinUI 3 是"非打包"场景，需要 SelfContained 部署（见 vcxproj 配置）。
#include "pch.h"

using namespace winrt;
using namespace Microsoft::UI::Xaml;
using namespace Microsoft::UI::Xaml::Controls;
using namespace Microsoft::UI::Xaml::XamlTypeInfo;
using namespace Microsoft::UI::Xaml::Markup;
using namespace Windows::UI::Xaml::Interop;
using namespace Windows::Foundation;

// ─────────────────────────────────────────────────────────────
// MainWindow：所有 UI 都用 C++ API 拼装，不写任何 XAML
// ─────────────────────────────────────────────────────────────
class MainWindow : public WindowT<MainWindow>
{
public:
    MainWindow()
    {
        // 窗口标题
        Title(L"WinUI 3 in C++ Without XAML");

        // 根容器：StackPanel（垂直堆叠，居中）
        StackPanel stackPanel;
        stackPanel.HorizontalAlignment(HorizontalAlignment::Center);
        stackPanel.VerticalAlignment(VerticalAlignment::Center);

        // 标题文字：套用应用资源里的 TitleTextBlockStyle
        TextBlock title;
        title.Style(
            Application::Current().Resources()
                .Lookup(box_value(L"TitleTextBlockStyle"))
                .as<Style>());
        title.Text(L"WinUI 3 in C++ Without XAML!");
        title.HorizontalAlignment(HorizontalAlignment::Center);

        // 副标题：小字说明当前 SDK 版本
        TextBlock subtitle;
        subtitle.Text(L"WindowsAppSDK 2.5  ·  CppWinRT 3.0");
        subtitle.HorizontalAlignment(HorizontalAlignment::Center);
        subtitle.FontSize(14);
        subtitle.Foreground(winrt::Microsoft::UI::Xaml::Media::SolidColorBrush(
            winrt::Windows::UI::Color{ 0x99, 0x99, 0x99, 0x00 }));

        // 超链接按钮：点击打开 GitHub 仓库
        HyperlinkButton project;
        project.Content(box_value(L"Github Project Repository"));
        project.NavigateUri(Uri(L"https://github.com/sotanakamura/winui3-without-xaml"));
        project.HorizontalAlignment(HorizontalAlignment::Center);

        // 普通按钮：点击时把文字改成 "Thank You!"
        Button button;
        button.Content(box_value(L"Click"));
        button.Click(
            [](IInspectable const& sender, RoutedEventArgs)
            {
                sender.as<Button>().Content(box_value(L"Thank You!"));
            });
        button.HorizontalAlignment(HorizontalAlignment::Center);
        button.Margin(ThicknessHelper::FromUniformLength(20));

        // 组装视图树
        Content(stackPanel);
        stackPanel.Children().Append(title);
        stackPanel.Children().Append(subtitle);
        stackPanel.Children().Append(project);
        stackPanel.Children().Append(button);
    }
};

// ─────────────────────────────────────────────────────────────
// App：继承 ApplicationT 并实现 IXamlMetadataProvider
//       —— 这是"无 XAML 也能获得 Fluent 外观"的关键
// ─────────────────────────────────────────────────────────────
class App : public ApplicationT<App, IXamlMetadataProvider>
{
public:
    void OnLaunched(LaunchActivatedEventArgs const&)
    {
        // 注入 WinUI 3 默认主题（Fluent 控件样式）
        Resources().MergedDictionaries().Append(XamlControlsResources());

        // 创建并激活主窗口
        window = make<MainWindow>();
        window.Activate();
    }

    // IXamlMetadataProvider 三个方法：全部转发给 XamlControlsXamlMetaDataProvider
    IXamlType GetXamlType(TypeName const& type)
    {
        return provider.GetXamlType(type);
    }
    IXamlType GetXamlType(hstring const& fullname)
    {
        return provider.GetXamlType(fullname);
    }
    com_array<XmlnsDefinition> GetXmlnsDefinitions()
    {
        return provider.GetXmlnsDefinitions();
    }

private:
    Window window{ nullptr };
    XamlControlsXamlMetaDataProvider provider;
};

// ─────────────────────────────────────────────────────────────
// 入口
// ─────────────────────────────────────────────────────────────
int WINAPI wWinMain(HINSTANCE, HINSTANCE, LPWSTR, int)
{
    // 初始化 COM/WinRT 线程（STA）
    init_apartment();

    // 启动 WinUI 3 应用框架
    Application::Start([](auto&&) { make<App>(); });

    return 0;
}