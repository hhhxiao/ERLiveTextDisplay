#ifndef ER_H
#define ER_H
namespace er {
    // void init_hooks();

    void init_signatures();

    void try_refresh_instances();

    namespace api {
        int death_count();
        int today_death_count();

    }  // namespace api
}  // namespace er

#endif
