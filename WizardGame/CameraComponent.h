#ifndef CAMCOMPONENT_H
#define CAMCOMPONENT_H
#include <map>
#include <typeindex>
#include <string>
#include <glm/glm.hpp>
#include "animatedObject.h"

#include <LuaBridge/LuaBridge.h>
#include "Component.h"
#include "camera.h"
#include "Globals.h"

extern float Width;
extern float Height;
extern bool resetCamera;
extern bool shakeScreen;
class CameraComponent : public Component {
public:
  CameraComponent(luabridge::LuaRef& componentTable) {
    auto fovRef = componentTable["fov"];
    auto fPersonRef = componentTable["fPersonRef"];
    if (fovRef.isNumber()) {
      camera.InitCam(glm::vec3(0,0,-5), fovRef.cast<float>(), Width / Height,0.01f, 3000.0f);
      camera.m_position = glm::vec3(0.0f,0.0f,0.0f);
      isFirstPerson = fPersonRef.cast<bool>();
      if (isFirstPerson == false) {
        camera.Pitch(1.570796f);
      }
    }else{
      std::cout << "Error, FOV is not a NUMBER!" << '\n';
    }
  }
  Camera& getCamera() {
    return camera;
  }
  void setFOV(float fov) {
    camera.ReInitCam(fov, Width / Height, 0.01f, 3000.0f);
  }
  void setResolution() {
      camera.ReInitCam(camera.fov, Width / Height, 0.01f, 3000.0f);
  }
  void setPos(glm::vec3 p) {
    camera.m_position = p;
  }
  void Shake(float amount) {
    camera.Shake(amount);
  }
  void UpdateCamera() {
      if (resetCamera == true) {
          setResolution();
          resetCamera = false;
      }
    //if (isFirstPerson == false) {
    //  camera.m_position = glm::vec3(0.0f,500.0f,0.0f);
    //}
     // std::cout << "forward.x: " << camera.m_forward.x << "   forward.z: " << camera.m_forward.z << "\n";
      if (shakeScreen == true) {
          camera.UpdateShake();
      }
    
  }

  int x = 0;
  int y = 0;
  int lastX = 0;
  int lastY = 0;
  Camera camera;
  bool isFirstPerson = true;
protected:
private:
};
#endif
