/***
 * @Author: コウ　キガク
 * @         黄   琦岳
 * @Date: 2022-06-06 12:05:39
 * @LastEditors: 黄琦岳
 * @LastEditTime: 2022-06-06 12:05:40
 * @FilePath: \wyuEngine\Sources\Framework\Common\SceneObject.hpp
 * @Description:
 * @Copyright (c)2022 github: wuyukwi email: b1044763336@gmail.com, All Rights
 * Reserved.
 */

#pragma once
#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include "crossguid/guid.hpp"
#include "Image.hpp"

namespace wyuEngine
{
    enum SceneObjectType
    {
        SCENEOBJECT2D = 0,
    };

    class BaseSceneObject
    {
    protected:
        xg::Guid m_Guid;
        SceneObjectType m_Type;

        BaseSceneObject(SceneObjectType type) :m_Type(type) { m_Guid = xg::newGuid(); }
        BaseSceneObject(const xg::Guid& guid, SceneObjectType type) : m_Guid(guid), m_Type(type) {}
        BaseSceneObject(const xg::Guid&& guid, SceneObjectType type) : m_Guid(guid), m_Type(type) {}
        BaseSceneObject(BaseSceneObject&& obj) : m_Guid(obj.m_Guid), m_Type(obj.m_Type) {}
        BaseSceneObject& operator=(BaseSceneObject&& obj) { this->m_Guid = obj.m_Guid; this->m_Type = obj.m_Type; return *this; };
        virtual ~BaseSceneObject() = default;


    public:
        //タイプの指定が必要
        BaseSceneObject() = delete;
        //コピー出来ない
        BaseSceneObject(BaseSceneObject& obj) = delete;
        BaseSceneObject& operator=(BaseSceneObject& obj) = delete;

        const xg::Guid& GetGuid() const { return m_Guid; }
        const SceneObjectType GetType() const { return m_Type; }

        friend std::ostream& operator<<(std::ostream& out, const BaseSceneObject& obj)
        {
            out << "SceneObject" << std::endl;
            out << "-----------" << std::endl;
            out << "GUID: " << obj.m_Guid << std::endl;
            out << "Type: " << obj.m_Type << std::endl;

            return out;
        }
    };


    struct Vertex2D
    {
        Vec3 m_pos;
        Vec3 m_colour;
        Vec2 m_tex;
    };
    class SceneObjectIndexArray2D {
    protected:
        uint32_t    m_Index;
        size_t      m_RestartIndex;
        uint16_t* m_pDataI16;
    };

    class SceneObject2D : public BaseSceneObject
    {
    protected:
        std::vector<SceneObjectIndexArray2D>  m_IndexArray;
        std::vector<Vertex2D> m_VertexArray;
        Image m_image;

        bool        m_bVisible;

        const size_t m_szData;

    public:
        SceneObject2D(bool visible = true) : BaseSceneObject(SCENEOBJECT2D), m_bVisible(visible), m_szData(0) {}
        void AddIndexArray(SceneObjectIndexArray2D&& array) { m_IndexArray.push_back(std::move(array)); }
        void AddVertxArray(Vertex2D&& array) { m_VertexArray.push_back(array); }
        void SetTexture(const Image& image) { m_image = image; }
    };




    typedef enum _PrimitiveType {
        PrimitiveTypeNone = 0,        ///< No particular primitive type.
        PrimitiveTypePointList,   ///< For N>=0, vertex N renders a point.
        PrimitiveTypeLineList,    ///< For N>=0, vertices [N*2+0, N*2+1] render a line.
        PrimitiveTypeLineStrip,   ///< For N>=0, vertices [N, N+1] render a line.
        PrimitiveTypeTriList,     ///< For N>=0, vertices [N*3+0, N*3+1, N*3+2] render a triangle.
        PrimitiveTypeTriFan,      ///< For N>=0, vertices [0, (N+1)%M, (N+2)%M] render a triangle, where M is the vertex count.
        PrimitiveTypeTriStrip,    ///< For N>=0, vertices [N*2+0, N*2+1, N*2+2] and [N*2+2, N*2+1, N*2+3] render triangles.
        PrimitiveTypePatch,       ///< Used for tessellation.
        PrimitiveTypeLineListAdjacency,       ///< For N>=0, vertices [N*4..N*4+3] render a line from [1, 2]. Lines [0, 1] and [2, 3] are adjacent to the rendered line.
        PrimitiveTypeLineStripAdjacency,      ///< For N>=0, vertices [N+1, N+2] render a line. Lines [N, N+1] and [N+2, N+3] are adjacent to the rendered line.
        PrimitiveTypeTriListAdjacency,        ///< For N>=0, vertices [N*6..N*6+5] render a triangle from [0, 2, 4]. Triangles [0, 1, 2] [4, 2, 3] and [5, 0, 4] are adjacent to the rendered triangle.
        PrimitiveTypeTriStripAdjacency,       ///< For N>=0, vertices [N*4..N*4+6] render a triangle from [0, 2, 4] and [4, 2, 6]. Odd vertices Nodd form adjacent triangles with indices min(Nodd+1,Nlast) and max(Nodd-3,Nfirst).
        PrimitiveTypeRectList,    ///< For N>=0, vertices [N*3+0, N*3+1, N*3+2] render a screen-aligned rectangle. 0 is upper-left, 1 is upper-right, and 2 is the lower-left corner.
        PrimitiveTypeLineLoop,    ///< Like <c>kPrimitiveTypeLineStrip</c>, but the first and last vertices also render a line.
        PrimitiveTypeQuadList,    ///< For N>=0, vertices [N*4+0, N*4+1, N*4+2] and [N*4+0, N*4+2, N*4+3] render triangles.
        PrimitiveTypeQuadStrip,   ///< For N>=0, vertices [N*2+0, N*2+1, N*2+3] and [N*2+0, N*2+3, N*2+2] render triangles.
        PrimitiveTypePolygon,     ///< For N>=0, vertices [0, N+1, N+2] render a triangle.
    } PrimitiveType;



}
