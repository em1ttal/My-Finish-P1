#include "Builder.hh"


void Builder::newSphere()
{
    vec3 position(0.0, 0.0, 0.0);
    float radius = 0.5;
    QMessageBox msgBox;
    if (Controller::getInstance()->createSceneSphere(position, radius))
            msgBox.setText("One Sphere is created.");
    else msgBox.setText("Not enough memory. Error.");
    msgBox.exec();
}

void Builder::newBox()
{
    vec3 p1(-0.5, -0.5, -0.5);
    vec3 p2(0.5, 0.5, 0.5);
    QMessageBox msgBox;
    if (Controller::getInstance()->createSceneBox(p1, p2))
            msgBox.setText("One Box is created.");
    else msgBox.setText("Not enough memory. Error.");
    msgBox.exec();
}

void Builder::newTriangle()
{
    vec3 p1(-0.5, 0.0, 0.0);
    vec3 p2(0.5, 0.0, 0.0);
    vec3 p3(0, 1, 0);
    QMessageBox msgBox;
    if (Controller::getInstance()->createSceneTriangle(p1, p2, p3))
            msgBox.setText("One Triangle is created.");
    else msgBox.setText("Not enough memory. Error.");
    msgBox.exec();
}

void Builder::newSimulatedScene()
{
   QMessageBox msgBox;
   if (Controller::getInstance()->createScene()) {
        msgBox.setText("A simulated Scene is created.");
        Controller::getInstance()->setScene(Controller::getInstance()->getScene());
   }
   else msgBox.setText("Not enough memory. Error.");
   msgBox.exec();
}


void Builder::newVirtualScene()
{
    QString fileName = QFileDialog::getOpenFileName();
    if (!fileName.isNull()) {
        QMessageBox msgBox;
        if(Controller::getInstance()->createScene(SceneFactory::SCENE_TYPES::VIRTUALWORLD, fileName))
            msgBox.setText("Virtual Scene well loaded.");
        else msgBox.setText("Scene NOT loaded. Error reading data.");
        msgBox.exec();
    }
}


void Builder::loadSettings() {
    QString fileName = QFileDialog::getOpenFileName();
    if (!fileName.isNull()) {
        QMessageBox msgBox;
        if (Controller::getInstance()->createSettings(fileName)) {
                msgBox.setText("Visual Settings well loaded.");

        } else msgBox.setText("Settings NOT loaded. Error reading data.");
        msgBox.exec();
        emit settingsChanged();
    }
}

void Builder::activaColorShading() {
    QMessageBox msgBox;
    if (Controller::getInstance()->createShading(ShadingFactory::SHADING_TYPES::COLORSHADING)) {
        msgBox.setText("Color Shading created.");
    } else msgBox.setText("Error creating shading");
    msgBox.exec();
}

void Builder::activaNormalShader() {
    QMessageBox msgBox;
    if (Controller::getInstance()->createShading(ShadingFactory::SHADING_TYPES::NORMAL)) {
        msgBox.setText("Normal Shading created.");
    } else msgBox.setText("Error creating shading");
    msgBox.exec();
}

void Builder::activaNColorShader() {
    QMessageBox msgBox;
    if (Controller::getInstance()->createShading(ShadingFactory::SHADING_TYPES::NCOLORSHADING)) {
        msgBox.setText("N-Hits Shading created.");
    } else msgBox.setText("Error creating shading");
    msgBox.exec();
}
