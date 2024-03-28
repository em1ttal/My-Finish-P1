#include "BlinnPhongShading.hh"


vec3 BlinnPhongShading::shading(shared_ptr<Scene> scene, vector<shared_ptr<HitRecord>> infos, vec3 lookFrom, bool shadow, vector<shared_ptr<Light>> lights, vec3 globalLight) {
    if (infos.empty()) {
        auto m = infos[0]->mat;
        return m->Kd;
    }

    vec3 totalColor = vec3(0.0f);
    for (auto light : lights)
    {
        vec3 aux = vec3(0.0f);
        vec3 l = light->vectorL(infos[0]->p); //Calculem el vector L. 
        vec3 v = lookFrom - infos[0]->p; //Calculem el vector V
        vec3 n = infos[0]->normal; //Calculem el vector N
        l = glm::normalize(l); //Normalize the L vector
        v = glm::normalize(v); //Normalitzem el vector V
        n = glm::normalize(n); //Normalitzem el vector N
        aux += light->getId() * infos[0]->mat->Kd * glm::max(0.0f, glm::dot(n, l)); //Calcul del color difús
        vec3 r = 2.0f * glm::dot(n, l) * n - l; //Calcul del vector R
        r = glm::normalize(r); //Normalitzem el vector R
        aux += light->getIs() * infos[0]->mat->Ks * pow(glm::max(0.0f, glm::dot(r, v)), infos[0]->mat->shininess); //Calcul del color especular
        aux *= light->attenuation(infos[0]->p); //Calcul de l'atenuació
        aux += light->getIa() * infos[0]->mat->Ka; //Calcul del color ambient
        totalColor += aux;
    }
    totalColor += globalLight * infos[0]->mat->Ka; //Calcul del color ambient global
    return totalColor;
}
