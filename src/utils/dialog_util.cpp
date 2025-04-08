#include "dialog_util.hpp"

bool DialogUtil::folder_select_dialog(path_t& dir) {
    auto cleanup = [](IFileDialog* pfd, IShellItem* psi = nullptr) {
        if (psi) psi->Release();
        if (pfd) pfd->Release();
        CoUninitialize();
    };

    auto hr = CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
    if (FAILED(hr)) {
        return false;
    }

    IFileDialog* pfd = nullptr;
    hr = CoCreateInstance(CLSID_FileOpenDialog, nullptr, CLSCTX_ALL, IID_IFileDialog, reinterpret_cast<void**>(&pfd));
    if (FAILED(hr)) {
        CoUninitialize();
        return false;
    }

    DWORD dwOptions { };
    hr = pfd->GetOptions(&dwOptions);
    if (FAILED(hr)) {
        cleanup(pfd);
        return false;
    }

    hr = pfd->SetOptions(dwOptions | FOS_PICKFOLDERS);
    if (FAILED(hr)) {
        cleanup(pfd);
        return false;
    }

    hr = pfd->Show(nullptr);
    if (FAILED(hr)) {
        cleanup(pfd);
        return false;
    }

    IShellItem* psi = nullptr;
    hr = pfd->GetResult(&psi);
    if (FAILED(hr)) {
        cleanup(pfd);
        return false;
    }

    LPWSTR pszFilePath = nullptr;
    hr = psi->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);
    if (FAILED(hr)) {
        cleanup(pfd, psi);
        return false;
    }

    dir = pszFilePath;

    CoTaskMemFree(pszFilePath);
    pszFilePath = nullptr;
    cleanup(pfd, psi);
    return true;
}
