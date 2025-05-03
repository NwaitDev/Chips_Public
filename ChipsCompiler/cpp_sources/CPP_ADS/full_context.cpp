#include "../ChipsADS.hpp"

namespace chips_ads {

    void full_context::set_state(COMPILE_STATE new_state){
        if ((   new_state == IN_PHYSICAL
             || new_state == IN_PURE
             || new_state == IN_VIRTUAL) && st != DEFINING
        ) {
            throw chips_exception("Cannot set the state to IN_FUNCTION kind of state if not currently in the DEFINING state.");
        }

        if ((   st != IN_PHYSICAL
             && st != IN_PURE
             && st != IN_VIRTUAL) && new_state == DEFINING
        ) {
           throw chips_exception("Cannot set the state back to DEFINING if not currently in a IN_FUNCTION state.");
        }

        if ( new_state == CONFIGURING && st != DEFINING) {
          throw chips_exception("Cannot set the state to CONFIGURING if not currently in the DEFINING state.");
        }
        st = new_state;
    }

    void full_context::set_state(COMPILE_STATE new_state, std::string state_attr){
        set_state(new_state);
        st_attr = state_attr;
    }

}