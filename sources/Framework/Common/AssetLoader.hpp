/***
 * @Author: コウ　キガク
 * @         黄   琦岳
 * @Date: 2022-05-31 09:25:24
 * @LastEditors: 黄琦岳
 * @LastEditTime: 2022-05-31 09:25:25
 * @FilePath: \wyuEngine\sources\Framework\Common\AssetLoader.hpp
 * @Description:
 * @Copyright (c)2022 github: wuyukwi email: b1044763336@gmail.com, All Rights
 * Reserved.
 */
#pragma once

#include <cstdio>
#include <string>
#include <utility>
#include <vector>
#include "IRuntimeModule.hpp"
#include "Buffer.hpp"

namespace wyuEngine {

    class AssetLoader :public IRuntimeModule {
    public:
        virtual ~AssetLoader() {};

        virtual int Initialize() override;
        virtual void Finalize() override;

        virtual void Tick() override;

        typedef void* AssetFilePtr;

        enum AssetOpenMode
        {
            ENGINE_OPEN_TEXT = 0,
            ENGINE_OPEN_BINARY,
        };

        enum AssetSeekBase {
            ENGINE_SEEK_SET = 0,//ファイルの最初の位置から
            ENGINE_SEEK_CUR,    //現在の位置から
            ENGINE_SEEK_END     //ファイルの最後から
        };

        bool AddSearchPath(const char* path);

        bool RemoveSearchPath(const char* path);

        bool FileExists(const char* filePath);

        AssetFilePtr OpenFile(const char* name, AssetOpenMode mode);

        Buffer SyncOpenAndReadText(const char* filePath);

        Buffer SyncOpenAndReadBinary(const char* filePath);

        size_t SyncRead(const AssetFilePtr& fp, Buffer& buf);

        static void CloseFile(AssetFilePtr& fp);

        static size_t GetSize(const AssetFilePtr& fp);

        static int32_t Seek(AssetFilePtr fp, long offset, AssetSeekBase where);

        inline std::string SyncOpenAndReadTextFileToString(const char* fileName)
        {
            std::string result;
            const Buffer buffer = SyncOpenAndReadText(fileName);
            char* content = reinterpret_cast<char*>(buffer.m_pData);

            if (content)
            {
                result = std::string(content);
            }

            return result;
        }
    private:
        std::vector<std::string> m_strSearchPath;
    };
}