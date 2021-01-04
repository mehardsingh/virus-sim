#include <visualizer/environment_painter.h>

namespace virussim {

    namespace visualizer {
        using ci::gl::clear;
        using ci::gl::color;
        using ci::gl::drawSolidRect;
        using ci::gl::drawSolidCircle;
        using ci::ColorA;

        const Color EnvironmentPainter::kEnvironmentColor = Color::white();
        const Color8u EnvironmentPainter::kHealthyColor = Color8u(35, 155, 0);
        const Color8u EnvironmentPainter::kInfectedColor = Color8u(200, 0, 0);
        const Color8u EnvironmentPainter::kDeadColor = Color8u(128, 128, 128);

        void EnvironmentPainter::Draw(const vec2& translation, const Environment& environment) {
            color(kEnvironmentColor);
            drawSolidRect(environment.GetArea().getOffset(translation));

            for (size_t index = 0; index < environment.GetNumPeople(); index++) {
                if (environment.GetIsDeadAt(index)) {
                    color(kDeadColor);
                } else if (environment.GetIsInfectedAt(index)) {
                    color(kInfectedColor);
                } else {
                    color(kHealthyColor);
                }

                drawSolidCircle(environment.GetPosAt(index) +
                                translation, Person::GetRad());

                if (environment.GetIsInfectedAt(index)) {
                    color(ColorA(kInfectedColor, 0.2));
                    drawSolidCircle(environment.GetPosAt(index) + translation,
                                    environment.GetMinDist());
                }
            }
        }

    } // namespace visualizer

} // namespace virussim