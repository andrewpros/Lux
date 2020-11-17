#include "pch.h"
#include "App.h"

using namespace std;
using namespace winrt;
using namespace winrt::Windows::ApplicationModel;
using namespace winrt::Windows::ApplicationModel::Activation;
using namespace winrt::Windows::UI::Xaml;

int __stdcall wWinMain(HINSTANCE, HINSTANCE, PWSTR, int)
{
  init_apartment();

  if (AppInstance::RecommendedInstance())
  {
    AppInstance::RecommendedInstance().RedirectActivationTo();
  }
  else
  {
    hstring instanceId;

    auto activationArgs = AppInstance::GetActivatedEventArgs();
    if (activationArgs && activationArgs.Kind() == ActivationKind::Protocol && activationArgs.as<ProtocolActivatedEventArgs>().Uri().SchemeName() == L"ms-gamebarwidget")
    {
      instanceId = L"gamebar";
    }
    else
    {
      instanceId = L"windowed";
    }
    
    auto instance = AppInstance::FindOrRegisterInstanceForKey(instanceId);
    if (instance.IsCurrentInstance())
    {
      Application::Start([](auto&&) { make<::winrt::Lux::implementation::App>(); });
    }
    else
    {
      instance.RedirectActivationTo();
    }
  }

  return 0;
}