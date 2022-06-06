/***
 * @Author: コウ　キガク
 * @         黄   琦岳
 * @Date: 2022-05-31 09:26:03
 * @LastEditors: 黄琦岳
 * @LastEditTime: 2022-05-31 09:26:03
 * @FilePath: \wyuEngine\sources\Framework\Common\AssetLoader.cpp
 * @Description:
 * @Copyright (c)2022 github: wuyukwi email: b1044763336@gmail.com, All Rights
 * Reserved.
 */

#include "AssetLoader.hpp"
#include "stb_image.h"

using namespace std;
using namespace wyuEngine;

int AssetLoader::Initialize()
{
    return 0;
}

void AssetLoader::Finalize()
{
    m_strSearchPath.clear();
}

void AssetLoader::Tick()
{

}

/**
 * \brief 探すパスを追加する
 * \param path パス
 * \return true
 */
bool AssetLoader::AddSearchPath(const char* path)
{
    auto src = m_strSearchPath.begin();

    while (src != m_strSearchPath.end())
    {
        if (*src == path)
            return  true;
        ++src;
    }

    m_strSearchPath.emplace_back(path);
    return true;
}

/**
 * \brief パスを削除する
 * \param path パス
 * \return true
 */
bool AssetLoader::RemoveSearchPath(const char* path)
{
    auto src = m_strSearchPath.begin();

    while (src != m_strSearchPath.end())
    {
        if (*src == path)
        {
            m_strSearchPath.erase(src);
            return true;
        }
        ++src;
    }

    m_strSearchPath.emplace_back(path);
    return true;
}

/**
 * \brief ファイルを閉じる
 * \param filePath ファイルパス
 * \return 成功:true 失敗:false
 */
bool AssetLoader::FileExists(const char* filePath)
{
    AssetFilePtr fp = OpenFile(filePath, ENGINE_OPEN_BINARY);

    if (fp != nullptr)
    {
        CloseFile(fp);
        return true;
    }
    return false;
}

/**
 * \brief ファイルを開く
 * \param name ファイルネーム
 * \param mode ファイルを開くモード
 * \return 成功：AssetFilePtr(void*) 失敗：nullptr
 */
AssetLoader::AssetFilePtr AssetLoader::OpenFile(const char* name, AssetOpenMode mode)
{
    FILE* fp = nullptr;

    //階層パスをN回ループし、各レベルで探します
    string upPath;
    string fullPath;
    for (int32_t i = 0; i < 10; i++)
    {
        auto src = m_strSearchPath.begin();
        bool looping = true;
        while (looping)
        {
            fullPath.assign(upPath);  //今のupPathにリセットする

            if (src != m_strSearchPath.end())
            {
                fullPath.append(*src);
                fullPath.append("/Asset/");
                ++src;
            }
            else
            {
                fullPath.append("Asset/");
                looping = false;
            }

            fullPath.append(name);
#ifdef _DEBUG
            fprintf(stderr, "Trying to open %s\n", fullPath.c_str());
#endif
            switch (mode)
            {
            case ENGINE_OPEN_TEXT:
                fopen_s(&fp, fullPath.c_str(), "r");
                break;
            case ENGINE_OPEN_BINARY:
                fopen_s(&fp, fullPath.c_str(), "rb");
                break;
            case ENGINE_OPEN_IMAGE:
                fopen_s(&fp, fullPath.c_str(), "rb");
                break;
            }

            if (fp) return (AssetFilePtr)fp;

        }

        upPath.append("../");
    }

    return nullptr;
}

/**
 * \brief ファイルを開いてテキストデータとして読み込み関数
 * \param filePath ファイルのパス
 * \return Buffer*テキストデータ
 */
Buffer AssetLoader::SyncOpenAndReadText(const char* filePath)
{
    AssetFilePtr fp = OpenFile(filePath, ENGINE_OPEN_TEXT);
    Buffer* pBuff = nullptr;
    size_t length = 0;

    if (fp)
    {
        length = GetSize(fp);

        pBuff = new Buffer(length + 1);
        fread(pBuff->GetData(), length, 1, static_cast<FILE*>(fp));
        pBuff->GetData()[length] = '\0';

        CloseFile(fp);
    }
    else
    {
        fprintf(stderr, "Error opening file '%s'\n", filePath);
        pBuff = new Buffer();
    }

#ifdef _DEBUG
    fprintf(stderr, "Read file '%s',%d bytes\n", filePath, int(length));
#endif

    return *pBuff;
}

/**
 * \brief ファイルを開いてバイナリデータとして読み込み関数
 * \param filePath ファイルのパス
 * \return Buffer*テキストデータ
 */
Buffer AssetLoader::SyncOpenAndReadBinary(const char* filePath)
{
    AssetFilePtr fp = OpenFile(filePath, ENGINE_OPEN_BINARY);
    Buffer* pBuff = nullptr;
    size_t length = 0;

    if (fp)
    {
        length = GetSize(fp);

        pBuff = new Buffer(length + 1);
        fread(pBuff->GetData(), length, 1, static_cast<FILE*>(fp));

        CloseFile(fp);
    }
    else
    {
        fprintf(stderr, "Error opening file '%s'\n", filePath);
        pBuff = new Buffer();
    }

#ifdef _DEBUG
    fprintf(stderr, "Read file '%s',%d bytes\n", filePath, int(length));
#endif

    return *pBuff;
}

bool AssetLoader::SyncOpenAndReadImage(const char* filePath, Image& pImage)
{

    AssetFilePtr fp = OpenFile(filePath, ENGINE_OPEN_BINARY);
    size_t length = 0;
    int x, y, comp;
    const int info = stbi_info_from_file(static_cast<FILE*>(fp), &x, &y, &comp);

    if (fp && info)
    {
        length = GetSize(fp);
        pImage.pBuffer = new Buffer(length);
        pImage.pBuffer->GetData() = stbi_load_from_file(static_cast<FILE*>(fp), &x, &y, &comp, 4);
        pImage.Width = x;
        pImage.Height = y;
        pImage.channels = comp;

        CloseFile(fp);
    }
    else
    {
        fprintf(stderr, "Error opening file '%s'\n", filePath);
        pImage.pBuffer = new Buffer();
        return false;
    }

#ifdef _DEBUG
    fprintf(stderr, "Read file '%s',%d bytes\n", filePath, int(length));
#endif

    return true;
}

/**
 * \brief ファイルを閉じる
 * \param fp ファイルのポインター
 */
void AssetLoader::CloseFile(AssetFilePtr& fp)
{
    fclose(static_cast<FILE*>(fp));
    fp = nullptr;
}

/**
 * \brief ファイルのlengthを取得
 * \param fp ファイルのポインター
 * \return length
 */
size_t AssetLoader::GetSize(const AssetFilePtr& fp)
{
    FILE* _fp = static_cast<FILE*>(fp);

    const long pos = ftell(_fp);  //最初のoffsetを取得する
    fseek(_fp, 0, SEEK_END);  //ポインターをoffsetを最後まで移動する
    const size_t length = ftell(_fp);  //lengthを取得
    fseek(_fp, pos, SEEK_SET);  //最初のoffsetに戻す

    return length;
}

/**
 * \brief ファイルのデータをバファに読み込む
 * \param fp ファイルのポインター
 * \param buf ファイルのバファ
 * \return ファイルのサイズ　失敗: 0
 */
size_t AssetLoader::SyncRead(const AssetFilePtr& fp, Buffer& buf)
{
    if (!fp)
    {
        fprintf(stderr, "null file discriptor\n");
        return 0;
    }

    const size_t sz = fread(buf.GetData(), buf.GetDataSize(), 1, static_cast<FILE*>(fp));

    //fprintf(stderr,"Read file '%s', %d bytes\n0",)

    return sz;
}

/**
 * \brief ファイルのoffset移動する関数
 * \param fp ファイルのポインター
 * \param offset 移動量
 * \param where どこから移動する
 * \return offset 失敗：0
 */
int32_t AssetLoader::Seek(AssetFilePtr fp, long offset, AssetSeekBase where)
{
    return fseek(static_cast<FILE*>(fp), offset, static_cast<int>(where));
}

