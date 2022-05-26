/*********************************************************************************

  *FileName: GUI.cpp
            コウ  キガク
  *Author:  Huang QiYue
  *Version:  1.0
  *Date:  2022/04/05

**********************************************************************************/

#include "GUI.h"

// m_controlの配列を増やす
int CGUISystem::IncreaseControls()
{
    if (!m_controls)
    {
        m_controls = new stGUIControl[1];

        if (!m_controls) 
            return UGP_FAIL;

        memset(&m_controls[0], 0, sizeof(stGUIControl));
    }
    else
    {
        stGUIControl* temp;
        temp = new stGUIControl[m_totalControls + 1];

        if (!temp) 
            return UGP_FAIL;

        memset(temp, 0, sizeof(stGUIControl) *(m_totalControls + 1));

        memcpy(temp, m_controls,sizeof(stGUIControl) * m_totalControls);

        delete[] m_controls;
        m_controls = temp;
    }

    return UGP_OK;
}


bool CGUISystem::AddBackdrop(int texID, int sID)
{
    if (texID < 0 || sID < 0) 
        return false;

    if (m_backDropID < 0)
    {
         // 新しいコントローラー配列を作成
        if (!IncreaseControls()) 
            return false;

        // 必要な情報を保存
        m_controls[m_totalControls].m_type = UGP_GUI_BACKDROP;
        m_controls[m_totalControls].m_upTex = texID;
        m_controls[m_totalControls].m_listID = sID;

        //どのインデックスが背景であるかを追跡用
        m_backDropID = m_totalControls;

        m_totalControls++;
    }
    else
    {
        //// IDを保存するだけ
        m_controls[m_backDropID].m_upTex = texID;
        m_controls[m_backDropID].m_listID = sID;
    }

    return true;
}


bool CGUISystem::AddStaticText(int id, const char* text, int x, int y,unsigned long color, int fontID)
{
    if (!text || fontID < 0) 
        return false;

    // 新しいコントローラー配列を作成
    if (!IncreaseControls()) 
        return false;

    // テキスト必要の情報を保存
    m_controls[m_totalControls].m_type = UGP_GUI_STATICTEXT;
    m_controls[m_totalControls].m_id = id;
    m_controls[m_totalControls].m_color = color;
    m_controls[m_totalControls].m_xPos = x;
    m_controls[m_totalControls].m_yPos = y;
    m_controls[m_totalControls].m_listID = fontID;

    // データをコピーする
    int len = strlen(text);
    m_controls[m_totalControls].m_text = new char[len + 1];

    if (!m_controls[m_totalControls].m_text) 
        return false;

    memcpy(m_controls[m_totalControls].m_text, text, len);
    m_controls[m_totalControls].m_text[len] = '\0';

    m_totalControls++;

    return true;
}


bool CGUISystem::AddButton(int id, int x, int y, int width,int height, int upID, int overID,int downID, int staticID)
{
    // 新しいコントローラー配列を作成
    if (!IncreaseControls()) 
        return false;

    //  ボタン必要の情報を保存
    m_controls[m_totalControls].m_type = UGP_GUI_BUTTON;
    m_controls[m_totalControls].m_id = id;
    m_controls[m_totalControls].m_xPos = x;
    m_controls[m_totalControls].m_yPos = y;
    m_controls[m_totalControls].m_width = width;
    m_controls[m_totalControls].m_height = height;
    m_controls[m_totalControls].m_upTex = upID;
    m_controls[m_totalControls].m_overTex = overID;
    m_controls[m_totalControls].m_downTex = downID;
    m_controls[m_totalControls].m_listID = staticID;

    m_totalControls++;

    return true;
}


void CGUISystem::Shutdown()
{
    // 全てのリソースをリリース
    for (int s = 0; s < m_totalControls; s++)
    {   
        SAFE_DELETE_ARRAY(m_controls[s].m_text);
    }

    m_totalControls = 0;

    SAFE_DELETE_ARRAY(m_controls);
  
}