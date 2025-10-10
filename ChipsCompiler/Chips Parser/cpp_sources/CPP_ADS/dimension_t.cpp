#include "../ChipsADS.hpp"
#include <cassert>
#include <cstddef>
#include <functional>
#include <numeric>
#include <vector>

size_t chips_ads::dimension_t::get_cardinality(){
    size_t full_size = 1;
    for (int i  : dimension) {
        full_size*=i;
    }
    return full_size;
}

size_t chips_ads::dimension_t::linearize(std::vector<size_t> pos){
    size_t size = pos.size();
    if (size!=dimension.size()) {
        throw chips_exception("Cannot linearize this position : different cardinality of position and dimension.");
    }
    size_t lin = 0;
    for (size_t i = 0; i<size; ++i) {
        if(pos.at(i) >= dimension.at(i)){
            throw chips_exception("Cannot linearize this position : out of bound element.");
        }
        size_t factor = 1;
        if (i>0) {
            factor = std::accumulate(dimension.cbegin(), dimension.cbegin()+i, 1,std::multiplies<size_t>());
        }
        lin +=  factor * pos.at(i);
    }
    return lin;
}

size_t chips_ads::dimension_t::linearize(size_t pos){
    if ( 1 != dimension.size() ) {
        throw chips_exception("Cannot linearize this position : different cardinality of position and dimension.");
    }
    if(pos >= dimension.at(0)){
        throw chips_exception("Cannot linearize this position : out of bound element.");
    }
    return pos;
}


const uint8_t chips_ads::dimension_t::operator==(const std::vector<size_t>& otherv) const{
    size_t depth = this->depth();
    if (otherv.size()!=depth) {
        return false;
    }
    std::vector<size_t> diff(otherv);
    for (size_t i = 0; i<depth; ++i) {
        diff[i]-=dimension[i];
    }
    for (size_t e : diff) {
        if (e!=0) {
            return false;
        }
    }
    return true;
}

const uint8_t chips_ads::dimension_t::operator==(const dimension_t& other) const{
    size_t depth = this->depth();
    if (other.depth()!=depth) {
        return false;
    }
    std::vector<size_t> diff(other.dimension);
    for (size_t i = 0; i<depth; ++i) {
        diff[i]-=dimension[i];
    }
    for (size_t e : diff) {
        if (e!=0) {
            return false;
        }
    }
    return true;
}

uint8_t chips_ads::dimension_t::constains(std::vector<size_t> position) const{
    size_t mydepth = depth();
    size_t theirdepth = position.size();
    if (mydepth != theirdepth) {
        throw chips_exception("Position and dimension depth mismatch.");
    }
    for (size_t i = 0; i<mydepth; ++i){
        if (dimension.at(i)<=position.at(i)) {
            throw chips_exception("Position out of the dimension bound");
        }
    }
    return true;
}
