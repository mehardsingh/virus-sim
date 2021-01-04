#include <visualizer/virus-sim-app.h>
#include <visualizer/environment_painter.h>
#include <core/person.h>

namespace virussim {

    namespace visualizer {
        using std::string;
        using std::to_string;
        using ci::gl::drawStringCentered;
        using ci::ColorA;
        using ci::gl::clear;
        using ci::gl::color;
        using ci::gl::drawSolidRect;
        using ci::gl::drawSolidCircle;

        VirusSimApp::VirusSimApp() {
            speed = 1;
            setWindowSize((int) kWindowSize, (int) kWindowSize);
        }

        void VirusSimApp::update() {
            for (size_t index = 0; index < speed; index++) {
                environment_.Update();
            }
        }

        void VirusSimApp::draw() {
            vec2 translation = vec2(kMargin, kMargin);

            clear(kBackgroundColor);

            EnvironmentPainter::Draw(translation, environment_);

            string output = "# People: " + to_string(environment_.GetNumPeople()) +
                            ". # Infected: " + to_string(environment_.GetNumInfected()) +
                            ". # Dead: " + to_string(environment_.GetNumDead()) + ". # Maskless Dead: " +
                            to_string(environment_.GetNumDeadMaskless()) + ".";
            drawStringCentered(output, vec2(kWindowSize / 2, kMargin / 4));
        }

        void VirusSimApp::keyDown(KeyEvent event) {
            if (event.getCode() == KeyEvent::KEY_SPACE) {
                environment_.AddPerson();
            }

            if (event.getCode() == KeyEvent::KEY_LEFT) {
                if (speed == 0) {
                    return;
                } else {
                    speed--;
                }
            }

            if (event.getCode() == KeyEvent::KEY_RIGHT) {
                speed++;
            }
        }

    } // namespace visualizer

} // namespace virussim