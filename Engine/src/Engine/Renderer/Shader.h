#pragma once  
#include "Engine/Log.h"
#include "glm/glm.hpp"


namespace Engine
{

    class Shader
    {

    public:
        Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
        ~Shader(); 

        void Bind() const;
        void UnBind() const;

                void UploadUniformFloat2(const glm::vec2& values, const std::string& name);
                void UploadUniformFloat3(const glm::vec3& values, const std::string& name);
                void UploadUniformFloat4(const glm::vec4& values, const std::string& name);

                void UploadUniformMat4(const glm::mat4& matrix, const std::string& name);

    private:
        uint32_t m_RendererID;
    };


}