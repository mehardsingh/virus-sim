#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include <core/environment.h>

namespace virussim {

    namespace visualizer {
        using ci::app::KeyEvent;
        using ci::Color;
        using ci::Color8u;

        class VirusSimApp : public ci::app::App {
            public:
                VirusSimApp();

                void update() override;

                void draw() override;

                void keyDown(KeyEvent event) override;

            private:
                int speed;

                const double kWindowSize = 800;

                const double kMargin = 50;

                const Color kBackgroundColor = Color::black();

                const Color kEnvironmentColor = Color::white();

                const Color8u kHealthyColor = Color8u(35, 155, 0);

                const Color8u kInfectedColor = Color8u(200, 0, 0);

                const Color8u kDeadColor = Color8u(128, 128, 128);

                Environment environment_;
            };

    } // namespace visualizer

} // namespace virussim