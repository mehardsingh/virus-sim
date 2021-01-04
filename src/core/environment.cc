#include <core/environment.h>

#include <random>

namespace virussim {
    using cinder::distance;
    using std::bernoulli_distribution;
    using std::random_device;
    using std::mt19937;

    Environment::Environment() {
        num_infected_ = 0;
        num_dead_ = 0;
        num_dead_maskless_ = 0;
        time = 0;
    }

    void Environment::Update() {
        time++;

        int num_infected = 0;
        int num_dead = 0;
        int num_dead_maskless = 0;

        for (size_t p1 = 0; p1 < people_.size(); p1++) {
            if (people_[p1].GetReachedDestination()) {
                people_[p1].SetDestination(PickRandLocation());
            }

            if (people_[p1].GetIsInfected()) {
                num_infected++;
            }
            if (people_[p1].GetIsDead()) {
                num_dead++;
                if (!people_[p1].GetWearsMask()) {
                    num_dead_maskless++;
                }
            }

            for (size_t p2 = p1 + 1; p2 < people_.size(); p2++) {

                // checks spread if people are close
                if (distance(people_[p1].GetPos(),
                             people_[p2].GetPos()) < kMinDist) {
                    CheckSpread(people_[p1], people_[p2]);
                }
            }

            people_[p1].Move();
        }

        num_infected_ = num_infected;
        num_dead_ = num_dead;
        num_dead_maskless_ = num_dead_maskless;

        if (time % 200 == 0) {
            std::cout << num_infected_ << std::endl;
        }
    }

    void Environment::AddPerson() {
        random_device rd{}; // use to seed the rng
        mt19937 rng{rd()}; // rng

        bernoulli_distribution is_infected_dist(kInitiallyInfectedProb);
        bernoulli_distribution wears_mask_dist(kWearsMaskProb);

        bool is_infected = is_infected_dist(rng);
        bool wears_mask = wears_mask_dist(rng);

        // randomizes positions
        vec2 initial_pos = PickRandLocation();
        vec2 initial_dest = PickRandLocation();

        people_.push_back(Person(wears_mask, initial_pos, initial_dest, is_infected));
    }

    const Area & Environment::GetArea() const {
        return kArea;
    }

    const vec2 & Environment::GetPosAt(const int index) const {
        return people_[index].GetPos();
    }

    bool Environment::GetIsDeadAt(const int index) const {
        return people_[index].GetIsDead();
    }

    bool Environment::GetIsInfectedAt(const int index) const {
        return people_[index].GetIsInfected();
    }

    bool Environment::GetWearsMaskAt(const int index) const {
        return people_[index].GetWearsMask();
    }

    int Environment::GetNumPeople() const {
        return people_.size();
    }

    int Environment::GetMinDist() const {
        return kMinDist;
    }

    void Environment::CalculateStats() const {
        int num_infected = 0;
        int num_dead = 0;
        int num_dead_maskless = 0;

        for (Person p : people_) {
            if (p.GetIsInfected()) {
                num_infected++;
            }
            if (p.GetIsDead()) {
                num_dead++;
                if (p.GetWearsMask()) {
                    num_dead_maskless++;
                }
            }
        }
    }



    vec2 Environment::PickRandLocation() const {
        double rad = Person::GetRad();

        double x = (kArea.x1 + rad) + ((double) rand() / RAND_MAX) *
                ((kArea.x2 - rad) - (kArea.x1 + rad));
        double y = (kArea.y1 + rad) + ((double) rand() / RAND_MAX) *
                ((kArea.y2 - rad) - (kArea.y1 + rad));

        return vec2(x, y);
    }

    void Environment::CheckSpread(Person &p1, Person &p2) {
        // filters so one person is infected, other isn't
        if ((p1.GetIsInfected() && p2.GetIsInfected()) ||
        (!p1.GetIsInfected() && !p2.GetIsInfected())) {
            return;
        }

        Person* infected = p1.GetIsInfected() ? &p1 : &p2;
        Person* not_infected = !p1.GetIsInfected() ? &p1 : &p2;
        bool trans;
        random_device rd{}; // use to seed the rng
        mt19937 rng{rd()}; // rng

        // sets transmission bool
        if (not_infected->GetWearsMask()) {
            if (infected->GetWearsMask()) {
                bernoulli_distribution spread(kBothMaskTrans);
                trans = spread(rng);
            } else {
                bernoulli_distribution spread(kRecipientMaskTrans);
                trans = spread(rng);
            }
        } else {
            if (infected->GetWearsMask()) {
                bernoulli_distribution spread(kCarrierMaskTrans);
                trans = spread(rng);
            } else {
                bernoulli_distribution spread(kNoMaskTrans);
                trans = spread(rng);
            }
        }

        if (trans) {
            not_infected->Infect();
        }
    }

    int Environment::GetNumInfected() const {
        return num_infected_;
    }

    int Environment::GetNumDead() const {
        return num_dead_;
    }

    int Environment::GetNumDeadMaskless() const {
        return num_dead_maskless_;
    }

} // namespace virussim