
//
//  ofxShaderUtill.h
//
//  Created by asai yuta on 2017/03/31.
//
//

#ifndef ofxShaderUtill_h
#define ofxShaderUtill_h

#include "ofMain.h"

class ofxShaderUtill{
public:
    
    class AnyArgHolder{
    public:
        template<typename T>
        AnyArgHolder(ofShader* shader, std::string name, T& arg, int count = 1)
        {
            holder = std::shared_ptr<PlaceHoleder>( new ArgHolder<T>(shader, name, arg, count));
        }
        
        class PlaceHoleder{
        public:
            virtual ~PlaceHoleder(){}
            virtual void setUniformArg(){}
            
            virtual string getName(){}
        };
        
        template<typename ARG>
        class ArgHolder :public PlaceHoleder{
        public:
            ArgHolder(ofShader* shader, std::string name, ARG& arg, int count = 1)
            : name(name)
            , held(&arg)
            , holdShader(shader)
            , count(count)
            {}
            
            void setUniformArg(){
                this -> uniformSetter();
            }
            
            string getName(){
                return this -> name;
            }
            
            void uniformSetter(){}
            
            ARG* held;
            std::string name;
            ofShader* holdShader;
            const int count;
        };
        
        void setUniform(){
            holder -> setUniformArg();
        }
        
        string getName(){
            holder -> getName();
        }
        
        std::shared_ptr<PlaceHoleder> holder;
    };
    
    ofxShaderUtill()
    : shader(nullptr)
    {}
    ofxShaderUtill(ofShader& shader)
    : shader(&shader)
    {}
    ofxShaderUtill(ofShader* shader)
    : shader(shader)
    {}
    
    void setShader(ofShader& ofshader){
        shader = &ofshader;
    }
    
    void setShader(ofShader* ofshader){
        shader = ofshader;
    }
    
    void load(string shaderName){
        shader -> load(shaderName);
    }
    
    void load(string vertName, string fragName){
        shader -> load(vertName, fragName);
    }
    
    
    
    template<typename ARG_TYPE>
    void publishUniformArg(string name, ARG_TYPE& arg,int count = 1){
        uniformArgHolder.emplace_back(this->shader, name, arg, count);
    }
    
    vector<string> getAllArgNames(){
        vector<string> names;
        for(auto& e : uniformArgHolder){
            names.push_back(e.getName());
        }
        return names;
    };
    
    void begin(){
        shader -> begin();
        this -> setUniformAll();
    }
    
    void end(){
        shader -> end();
    }
    
private:
    
    inline void setUniformAll(){
        for(auto& e : uniformArgHolder){
            e.setUniform();
        }
    }
    
    vector<AnyArgHolder> uniformArgHolder;
    ofShader* shader;
};

template<typename T>
using ArgHolder  = typename ofxShaderUtill::AnyArgHolder::ArgHolder<T>;

template<>
void ArgHolder<float>::uniformSetter(){
    this -> holdShader -> setUniform1f(this -> name, *(this -> held));
}

template<>
void ArgHolder<int>::uniformSetter(){
    this -> holdShader -> setUniform1i(this -> name, *(this -> held));
}

template<>
void ArgHolder<ofVec2f>::uniformSetter(){
    this -> holdShader -> setUniform2f(this -> name, *(this -> held));
}

template<>
void ArgHolder<ofVec3f>::uniformSetter(){
    this -> holdShader -> setUniform3f(this -> name, *(this -> held));
}

template<>
void ArgHolder<ofVec4f>::uniformSetter(){
    this -> holdShader -> setUniform4f(this -> name, *(this -> held));
}


template<>
void ArgHolder<ofMatrix3x3>::uniformSetter(){
    this -> holdShader -> setUniformMatrix3f(this -> name, *(this -> held), this -> count);
}

template<>
void ArgHolder<ofMatrix4x4>::uniformSetter(){
    this -> holdShader -> setUniformMatrix4f(this -> name, *(this -> held), this -> count);
}

template<>
void ArgHolder<ofTexture>::uniformSetter(){
    this -> holdShader -> setUniformTexture(this -> name, *(this -> held), this -> count);
}

template<>
void ArgHolder<ofFbo>::uniformSetter(){
    this -> holdShader -> setUniformTexture(this -> name, this -> held -> getTexture(), this -> count);
}
















#endif /* ofxShaderUtill_h */
