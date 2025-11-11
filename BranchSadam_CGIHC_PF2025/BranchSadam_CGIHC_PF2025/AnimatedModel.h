#pragma once
#include "Model.h"
#include <glm/glm.hpp>
#include <vector>
#include <string>
#include <iostream>

class AnimatedModel {
public:
    std::vector<Model*> frames;  // Cada frame es un modelo completo (.obj)
    int currentFrame;
    float t;          // parámetro de interpolación [0,1)
    float speed;      // velocidad de la animación

    AnimatedModel() : currentFrame(0), t(0.0f), speed(1.0f) {}

    // Carga varios modelos que serán los "frames" de la animación
    void loadFrames(const std::vector<std::string>& paths) {
        for (const auto& path : paths) {
            frames.push_back(new Model((char*)path.c_str()));
        }
        std::cout << "Se cargaron " << frames.size() << " frames de animación.\n";
    }

    // Dibuja interpolando entre el frame actual y el siguiente
    void Draw(Shader shader) {
        if (frames.empty()) return;

        int nextFrame = (currentFrame + 1) % frames.size();

        // En este ejemplo básico no modificamos los vértices directamente,
        // solo dibujamos el modelo interpolado "virtualmente".
        // Si quieres interpolar realmente los vértices, tendrías que acceder
        // a las posiciones del Mesh, lo cual requiere ampliar la clase Mesh.
        frames[currentFrame]->Draw(shader);

        // Avanzar el tiempo
        t += 0.01f * speed;
        if (t >= 1.0f) {
            t = 0.0f;
            currentFrame = nextFrame;
        }
    }
};
