#pragma once

#include <core/environment.h>
#include "cinder/gl/gl.h"

namespace virussim {
    using ci::Color;
    using ci::Color8u;

    namespace visualizer {
        using ci::vec2;

        class EnvironmentPainter {
        public:
            static void Draw(const vec2& translation, const Environment& environment);

        private:
            static const Color kEnvironmentColor;

            static const Color8u kHealthyColor;

            static const Color8u kInfectedColor;

            static const Color8u kDeadColor;
        };

    } // namespace visualizer

} // namespave virussim