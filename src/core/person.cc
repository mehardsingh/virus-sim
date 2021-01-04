#include <core/person.h>

#include <random>

namespace virussim {
    using cinder::distance;
    using std::bernoulli_distribution;
    using std::random_device;
    using std::mt19937;

    const double Person::kRecoveryProb = 0.98;
    const double Person::kRad = 5;

    Person::Person(const bool wears_mask, const vec2& initial_pos,
                   const vec2& initial_destination, const bool is_infected) {
        // sets bools
        wears_mask_ = wears_mask;
        is_infected_ = is_infected;
        is_dead_ = false;
        reached_destination_ = false;
        time_infected_ = 0;

        // sets positions
        position_ = initial_pos;
        SetDestination(initial_destination);
    }

    void Person::Move() {
        // does nothing if dead
        if (is_dead_) {
            return;
        }

        // checks if person reached destination
        if (distance(position_, destination_) <= 1) {
            reached_destination_ = true;
            return;
        }

        // manages person's infection
        if (is_infected_) {
            if (time_infected_ == kInfectionTime) {
                random_device rd{}; // use to seed the rng
                mt19937 rng{rd()}; // rng
                bernoulli_distribution survival_dist(kRecoveryProb);

                if (survival_dist(rng)) {
                    Disinfect();
                } else {
                    is_dead_ = true;
                    is_infected_ = false;
                }
            } else {
                time_infected_++;
            }
        }

        position_ += unit_dir_;
    }

    void Person::Infect() {
        if (is_dead_) {
            return;
        }

        is_infected_ = true;
    }

    void Person::SetDestination(const vec2& destination) {
        destination_ = destination;
        unit_dir_ = (destination - position_) / distance(destination, position_);
        reached_destination_ = false;
    }

    const vec2 & Person::GetPos() const {
        return position_;
    }

    bool Person::GetIsInfected() const {
        return is_infected_;
    }

    bool Person::GetWearsMask() const {
        return wears_mask_;
    }

    bool Person::GetIsDead() const {
        return is_dead_;
    }

    bool Person::GetReachedDestination() const {
        return reached_destination_;
    }

    double Person::GetRad() {
        return kRad;
    }

    void Person::Disinfect() {
        is_infected_ = false;
        time_infected_ = 0;
    }

} // namespace virussim