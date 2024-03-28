#include "NormalShading.hh"


vec3 NormalShading::shading(shared_ptr<Scene> scene, vector<shared_ptr<HitRecord>> infos, vec3 lookFrom, bool shadow, vector<shared_ptr<Light>> lights, vec3 globalLight) {
    if (!infos.empty()) {
            vec3 norm = normalize(infos[0]->normal);
            return 0.5f * vec3(norm.x + 1, norm.y + 1, norm.z + 1);
        } else {
            // Tracta la situació on el vector infos és buit
            // Retorna un valor predeterminat o maneja-ho segons les teves necessitats.
            return vec3(0.0f);
        }
}