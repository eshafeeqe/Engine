#pragma once 
 

namespace Engine{

    class  GraphicsContext
    {
    private:
      
    public:
        virtual void Init() = 0;
        virtual void SwapBuffers() = 0;

    };

}
