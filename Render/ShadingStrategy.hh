#pragma once

#include "Scene.hh"
#include "Light.hh"

class ShadingStrategy {
 public:
    // TODO: Fase 2: Canviar el mètode per passar les llums per calcular el shading
    virtual vec3 shading(shared_ptr<Scene> scene, vector<shared_ptr<HitRecord>> info, vec3 lookFrom, bool shadow, vector<shared_ptr<Light>> lights, vec3 globalLight) {


        return vec3(0.0, 0.0, 0.0);
    };

    // TUTORIAL 2: Calcula si el punt "point" és a l'ombra segons si el flag està activat o no
    float computeShadow(shared_ptr<Scene> scene, shared_ptr<Light> light, vec3 point) 
    {
        vec3 L = normalize(light->vectorL(point));
        point += 0.01f;
        Ray shadowRay(point,L);
        float t_min = 0.00000001f;
        float t_max = light->distanceToLight(point);

        if (scene->hit(shadowRay, t_min, t_max, false)) {
            return 0.0f;
        }

        return 1.0f;
    };

    virtual ~ShadingStrategy() {};
};
