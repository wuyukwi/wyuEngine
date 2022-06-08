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
    //#define SAFE_RELEASE( p )      { if( p ) { ( p )->Release(); ( p ) = NULL; } }
        //template <typename T>
        //inline void SAFE_DELETE(T** p)
        //{
        //    if (*p != nullptr)
        //    {
        //        delete(*p);

        //        (*p) = nullptr;
        //    }

        //}
        //template <typename T>
        //inline void SAFE_DELETE_ARRAY(T** p)
        //{
        //    if (*p)
        //    {
        //        delete[](*p);
        //        (*p) = nullptr;
        //    }
        //}
    template <class T>
    inline void SAFE_RELEASE(T& p)
    {
        if (p)
        {
            (p)->Release();
            (p) = nullptr;
        }
    }
} // namespace My
