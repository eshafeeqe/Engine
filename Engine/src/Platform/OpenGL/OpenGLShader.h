#pragma once  
#include "Engine/Renderer/Shader.h"


namespace Engine
{

    class OpenGLShader : public Shader
    {

    public:
        OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc);
        virtual ~OpenGLShader(); 

        virtual void Bind() const override;
        virtual void UnBind() const override;
        
        void UploadUniformInt (const int value, const std::string& name);
        
        void UploadUniformFloat (const float value, const std::string& name);
        void UploadUniformFloat2(const glm::vec2& values, const std::string& name);
        void UploadUniformFloat3(const glm::vec3& values, const std::string& name);
        void UploadUniformFloat4(const glm::vec4& values, const std::string& name);

        void UploadUniformMat3(const glm::mat3& matrix, const std::string& name);
        void UploadUniformMat4(const glm::mat4& matrix, const std::string& name);

    private:
        uint32_t m_RendererID;
    };


}