/*********************************************************************************

  *FileName: GUI.h
            コウ  キガク
  *Author:  Huang QiYue
  *Version:  1.0
  *Date:  2022/04/05

**********************************************************************************/

#ifndef _GUI_H_
#define _GUI_H_

#include "defines.h"

struct stGUIControl
{
    // ボタンタイプ、カラー
    int m_type, m_id;
    unsigned long m_color;

    // テキストの場合、これはフォントIDであり、それ以外の場合は静的バッファーIDです
    int m_listID;

    // オブジェクトの位置、ボタンの幅と高さ
    int m_xPos, m_yPos, m_width, m_height;

    // テキスト
    char* m_text;

    //ボタンのアップ、ダウン、オーバーテクスチャ。 m_upTexは背景画像にも使用されます
    int m_upTex, m_downTex, m_overTex;
};


class CGUISystem
{
public:
    CGUISystem() : m_controls(0), m_totalControls(0),m_backDropID(-1) {}
    ~CGUISystem() { Shutdown(); }

    int IncreaseControls();

    bool AddBackdrop(int texID, int staticID);
    bool AddStaticText(int id, const char* text, int x, int y,unsigned long color, int fontID);
    bool AddButton(int id, int x, int y, int width,int height, int upID, int overID,int downID, int staticID);
    void Shutdown();

    stGUIControl* GetGUIControl(int id)
    {
        if (id < 0 || id >= m_totalControls) 
            return NULL;

        return &m_controls[id];
    }

    int GetTotalControls()
    {
        return m_totalControls;
    }

    stGUIControl* GetBackDrop()
    {
        if (m_backDropID >= 0 && m_totalControls)
            return &m_controls[m_backDropID];

        return NULL;
    }

private:
    stGUIControl* m_controls;
    int m_totalControls;
    int m_backDropID;
};

#endif // _GUI_H_