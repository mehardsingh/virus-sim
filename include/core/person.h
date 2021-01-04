#pragma once

#include "cinder/gl/gl.h"

namespace virussim {
    using ci::vec2;

    class Person {
    public:
        Person(const bool wears_mask, const vec2& initial_pos,
               const vec2& initial_destination, const bool is_infected);

        void Move();

        void Infect();

        void SetDestination(const vec2& destination);

        const vec2& GetPos() const;

        bool GetIsInfected() const;

        bool GetWearsMask() const;

        bool GetIsDead() const;

        bool GetReachedDestination() const;

        static double GetRad();

    private:
        vec2 position_;

        vec2 destination_;

        vec2 unit_dir_;

        bool reached_destination_;

        bool is_infected_;

        bool wears_mask_;

        bool is_dead_;

        int time_infected_;

        static const double kRad;

        static const double kRecoveryProb;

        static const int kInfectionTime = 1000;

        void Disinfect();
    };

} // namespace virussim