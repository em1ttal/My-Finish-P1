#include "RayTracing.hh"


RayTracing::RayTracing(QImage *i):
    image(i) {

    setup = Controller::getInstance()->getSetUp();
    scene = Controller::getInstance()->getScene();
}


void RayTracing::play() {

    init();
    auto camera = setup->getCamera();
    int  width = camera->viewportX;
    int  height = camera->viewportY;

    for (int y = height-1; y >= 0; y--) {
        std::cerr << "\rScanlines remaining: " << y << ' ' << std::flush;  // Progrés del càlcul
        for (int x = 0; x < width; x++) {

            //TODO TUTORIAL 2: mostrejar més rajos per pixel segons el valor de "samples"

            float u = (float(x)) / float(width);
            float v = (float(height -y)) / float(height);
            vec3 color(0, 0, 0);

            // CÀLCUL DEL RAIG EN COORDENADES DE MON
            Ray r = camera->computeRay(u, v);

            // CÀLCUL DEL COLOR FINAL DEL PIXEL
            color = this->getColorPixel(r);

            // TODO TUTORIAL 2: Gamma correction

            color *= 255;
            setPixel(x, y, color);
        }
    }
}


void RayTracing::setPixel(int x, int y, vec3 color) {

    if (color.r < 0) color.r = 0;
    if (color.g < 0) color.g = 0;
    if (color.b < 0) color.b = 0;

    if (color.r > 255) color.r = 255;
    if (color.g > 255) color.g = 255;
    if (color.b > 255) color.b  = 255;

    image->setPixelColor(x, y, QColor(color.r, color.g, color.b));

}

/* Mètode RayPixel
** TODO: Cal modificar la funcio RayPixel es la funcio recursiva del RayTracing. Cal retocar-lo per:
** TUTORIAL 0 per a fer el degradat del fons
** FASES 0 i 1 per a cridar a la intersecció amb l'escena i posar el color de l'objecte (via color, depth o normal)
** TUTORIAL 2 per incloure els shading més realistes (Blinn-Phong  i ombres)
** TUTORIAL 2 per a tractar reflexions i transparències
**
*/

// Funcio recursiva que calcula el color.
vec3 RayTracing::getColorPixel(Ray &ray) {

    vec3 color = vec3(0);
    vec3 unit_direction;
    HitRecord info;
    
    if (setup->getBackground()) {
        vec3 colorTop = setup -> getTopBackground();
        vec3 colorBottom = setup -> getDownBackground();
        vec3 ray2 = normalize(ray.getDirection());

        float t = 0.5f * (ray2.y + 1);
        color = t*colorTop + (1-t)*colorBottom;
    } else {
        color = vec3(0,0,0);
    }

    if (scene -> hit(ray, ray.getTmin(), ray.getTmax())) {
        if (setup -> getShadingStrategy() != nullptr) {
            color = setup -> getShadingStrategy() -> shading(scene, ray.getHitRecords(), setup -> getCamera() -> getLookFrom(), setup -> getShadows());
        } else {
            color = ray.getHit(0) -> mat -> Kd;
        }
    }
    
    return color;
}


void RayTracing::init() {
    auto s = setup->getShadingStrategy();
}

