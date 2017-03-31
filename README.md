# ofxShaderUtill  
### publishing uniform  

```cpp:example  
  ofShader shader;
  ofxShaderUtill shaderUtill;
  ofVec2f vec;
  ofFbo fbo;
  ofTexture tex;
  
  void setup(){
    ...
    shaderUtill.setShader(shader);
    shaderUtill.publishUniformArg("force", vec);
    shaderUtill.publishUniformArg("tex0", tex, 0);
    shaderUtill.publishUniformArg("tex1", fbo, 1);
    ...
  }
  
  void draw(){
    ...
    shaderUtill.begin();
    ...
    
    shaderUtill.end();
    ...
  }
```
