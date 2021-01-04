#pragma once

#include "cinder/gl/gl.h"
#include <core/person.h>

namespace virussim {
    using std::vector;
    using ci::Area;

    class Environment {
    public:
        Environment();

        void Update();

        void AddPerson();

        const Area& GetArea() const;

        const vec2& GetPosAt(const int index) const;

        bool GetIsDeadAt(const int index) const;

        bool GetIsInfectedAt(const int index) const;

        bool GetWearsMaskAt(const int index) const;

        int GetNumPeople() const;

        int GetMinDist() const;

        int GetNumInfected() const;

        int GetNumDead() const;

        int GetNumDeadMaskless() const;

    private:
        vector<Person> people_;

        const Area kArea = Area(0, 0, 700, 500);

        const double kWearsMaskProb = 0.9;

        const double kInitiallyInfectedProb = 0.1;

        const double kNoMaskTrans = 0.9;

        const double kRecipientMaskTrans = 0.7;

        const double kCarrierMaskTrans = 0.05;

        const double kBothMaskTrans = 0.015;

        const double kMinDist = 25;

        int num_infected_;

        int num_dead_;

        int num_dead_maskless_;

        int time;

        vec2 PickRandLocation() const;

        void CheckSpread(Person& p1, Person& p2);

        void CalculateStats() const;
    };

} // namespace virussim