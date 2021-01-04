#include <visualizer/virus-sim-app.h>

using virussim::visualizer::VirusSimApp;

void prepareSettings(VirusSimApp::Settings* settings) {
    settings->setResizable(false);
}

// This line is a macro that expands into an "int main()" function.
CINDER_APP(VirusSimApp, ci::app::RendererGl, prepareSettings);