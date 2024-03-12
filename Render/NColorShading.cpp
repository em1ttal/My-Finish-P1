#include "NColorShading.hh"


vec3 NColorShading::shading(shared_ptr<Scene> scene, vector<shared_ptr<HitRecord>> infos, vec3 lookFrom, bool shadow) 
{
    if (infos.empty()) return vec3(0.0f);
    
    vec3 color = infos[0]->mat->Kd * (vec3(1.0f) - infos[0]->mat->kt);
    vec3 factor = infos[0]->mat->kt;
    for (size_t i = 1; i < infos.size(); i++) 
    {
        color += (vec3(1.0f) - infos[i]->mat->kt) * factor * infos[i]->mat->Kd;
        factor *= infos[i]->mat->kt;
    }
    // Get color from background and apply formula: colorBackground = 
    // color += (infos[infos.size()-1]->mat->kt) * colorBackground;
    return color;
}