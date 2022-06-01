/***
 * @Author: コウ　キガク
 * @         黄   琦岳
 * @Date: 2022-06-01 10:27:41
 * @LastEditors: 黄琦岳
 * @LastEditTime: 2022-06-01 10:27:42
 * @FilePath: \wyuEngine\sources\Framework\Common\utility.hpp
 * @Description:
 * @Copyright (c)2022 github: wuyukwi email: b1044763336@gmail.com, All Rights
 * Reserved.
 */
namespace wyuEngine {
    template <class T> inline void SafeRelease(T** ppInterfaceToRelease) {
        if (*ppInterfaceToRelease != nullptr) {
            (*ppInterfaceToRelease)->Release();

            (*ppInterfaceToRelease) = nullptr;
        }
    }
} // namespace My
