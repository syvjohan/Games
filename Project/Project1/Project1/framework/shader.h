#ifndef SHADER_H
#define SHADER_H

class Renderer;

// Wraps several shaders as a combined effect program
class Effect {
public:
    friend class Renderer;
    ~Effect();

    
    
private:
    explicit Effect();

};

#endif // !SHADER_H
