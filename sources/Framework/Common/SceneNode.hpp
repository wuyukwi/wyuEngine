/***
 * @Author: コウ　キガク
 * @         黄   琦岳
 * @Date: 2022-06-06 23:21:23
 * @LastEditors: 黄琦岳
 * @LastEditTime: 2022-06-06 23:24:58
 * @FilePath: \wyuEngine\Sources\Framework\Common\SceneNode.hpp
 * @Description:
 * @Copyright (c)2022 github: wuyukwi email: b1044763336@gmail.com, All Rights
 * Reserved.
 */

#pragma once
#include <iostream>
#include <list>
#include <memory>
#include <string>
#include <vector>
#include "SceneObject.hpp"

namespace wyuEngine
{
    class BaseSceneNode
    {
    protected:
        std::string m_strName;
        std::list<std::unique_ptr<BaseSceneNode>> m_Children;

        virtual void dump(std::ostream& out) const {};


    public:
        BaseSceneNode() = default;
        BaseSceneNode(const char* name) { m_strName = name; }
        BaseSceneNode(const std::string& name) { m_strName = name; }
        BaseSceneNode(const std::string&& name) { m_strName = name; }
        virtual ~BaseSceneNode() = default;

        void AppendChild(std::unique_ptr<BaseSceneNode>&& sub_node)
        {
            m_Children.push_back(std::move(sub_node));
        }

        friend std::ostream& operator<<(std::ostream& out, const BaseSceneNode& node)
        {
            static thread_local int32_t indent = 0;
            indent++;

            out << std::string(indent, ' ') << "Scene Node" << std::endl;
            out << std::string(indent, ' ') << "----------" << std::endl;
            out << std::string(indent, ' ') << "Name: " << node.m_strName << std::endl;
            node.dump(out);
            out << std::endl;

            for (const std::unique_ptr<BaseSceneNode>& sub_node : node.m_Children) {
                out << *sub_node << std::endl;
            }

            indent--;

            return out;
        }
    };

    template <typename T>
    class SceneNode : public BaseSceneNode
    {
    protected:
        std::shared_ptr<T> m_pSceneObject;

        void dump(std::ostream& out) const override
        {
            if (m_pSceneObject)
            {
                out << *m_pSceneObject << std::endl;
            }
        }

    public:
        //using BaseSceneNode::BaseSceneNode;
        SceneNode() = default;
        SceneNode(const std::shared_ptr<T>& object) { m_pSceneObject = object; }
        SceneNode(const std::shared_ptr<T>&& object) { m_pSceneObject = std::move(object); }

        void AddSceneObjectRef(const std::shared_ptr<T>& object) { m_pSceneObject = object; }
        void AddSceneObjectRef(const std::shared_ptr<T>&& object) { m_pSceneObject = std::move(object); }
    };

    typedef BaseSceneNode SceneEmptyNode;

    class SceneNode2D :public SceneNode<SceneObject2D>
    {
    protected:
        bool        m_bVisible;

        virtual void dump(std::ostream& out) const
        {
            SceneNode::dump(out);
            out << "Visible: " << m_bVisible << std::endl;
        }

    public:
        using SceneNode::SceneNode;

        void SetVisibility(bool visible) { m_bVisible = visible; }
        bool Visible() const { return m_bVisible; }
    };
};


