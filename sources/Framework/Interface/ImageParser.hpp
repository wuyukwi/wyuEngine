/***
 * @Author: コウ　キガク
 * @         黄   琦岳
 * @Date: 2022-06-01 10:56:54
 * @LastEditors: 黄琦岳
 * @LastEditTime: 2022-06-01 10:56:54
 * @FilePath: \wyuEngine\sources\Framework\Interface\ImageParser.hpp
 * @Description:
 * @Copyright (c)2022 github: wuyukwi email: b1044763336@gmail.com, All Rights
 * Reserved.
 */

#pragma once
#include "Buffer.hpp"
#include "Image.hpp"
#include "Interface.hpp"


namespace wyuEngine {
class ImageParser {
public:
  virtual Image Parse(const Buffer &buf) = 0;
};
} // namespace wyuEngine