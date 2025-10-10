#include "../ChipsADS.hpp"
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <vector>

chips_ads::dataflow_t::dataflow_t(chips_ads::dataflow_t& other)
    :type(other.type), dimension(other.get_dimension())
{
}

chips_ads::dataflow_t::dataflow_t(const DATAFLOW_TYPE type)
    : type(type), dimension(1), is_set(false)
{
}

chips_ads::dataflow_t::dataflow_t(const DATAFLOW_TYPE type, const std::vector<size_t> dimensions) 
    : type(type), dimension(dimensions), is_set(false)
{
    size_t full_size = this->dimension.get_cardinality();
    if (full_size>1) {
        switch (type) {
            case INT_DF:
                value.vi = new std::vector<int>(full_size);
                break;
            case FLOAT_DF:
                value.vf = new std::vector<double>(full_size);
                break;
            case BOOL_DF:
                value.vb = new std::vector<uint8_t>(full_size);
                break;
        }
    }
}

chips_ads::dataflow_t::dataflow_t(const DATAFLOW_TYPE type, dimension_t dimensions)
    : type(type), dimension(dimensions), is_set(false)
{
    size_t full_size = dimensions.get_cardinality();
    if (full_size>1) {
        switch (type) {
            case INT_DF:
                value.vi =  new std::vector<int>(full_size);
                break;
            case FLOAT_DF:
                value.vf = new std::vector<double>(full_size);
                break;
            case BOOL_DF:
                value.vb = new std::vector<uint8_t>(full_size);
                break;
        }
    }
}



chips_ads::dataflow_t::~dataflow_t ()
{
    if (dimension.get_cardinality()==1) {
        return;
    }
    switch (type) {
        case INT_DF:
            delete value.vi;
            break;
        case FLOAT_DF:
            delete value.vf;
            break;
        case BOOL_DF:
            delete value.vb;
            break;
    }
}





void chips_ads::dataflow_t::set_value(int v)
{
    if (type != INT_DF)
        throw chips_exception("Cannot store an int in that variable!");
    size_t nb_elems = dimension.get_cardinality();
    if (1==nb_elems) {
        value.i = v;
    } else {
        for (size_t i = 0; i<nb_elems; ++i) {
            value.vi->at(i) = v;
        }
    }
    is_set = true;
}

void chips_ads::dataflow_t::set_value(double v)
{
    if (type != FLOAT_DF)
        throw chips_exception("Cannot store a float in that variable!");
    size_t nb_elems = dimension.get_cardinality();
    if (1==nb_elems) {
        value.f = v;
    } else {
        for (size_t i = 0; i<nb_elems; ++i) {
            value.vf->at(i) = v;
        }
    }
    is_set = true;
}

void chips_ads::dataflow_t::set_value(bool v)
{
    if (type != BOOL_DF)
        throw chips_exception("Cannot store a bool in that variable!");
    size_t nb_elems = dimension.get_cardinality();
    if (1==nb_elems) {
        value.b = v;
    } else {
        for (size_t i = 0; i<nb_elems; ++i) {
            value.vb->at(i) = (uint8_t) v;
        }
    }
    is_set = true;
    
}

void chips_ads::dataflow_t::set_value(int i, std::vector<size_t> position)
{
    if (INT_DF != type) {
        throw chips_exception("Cannot store an int in that variable!");
    }
    if ( (dimension.get_cardinality()==1)) {
        if ((position.size()==1) && (position[0] == 0)) {
            value.i = i;
            is_set = true;
        }else{
            throw chips_exception("Cannot store a value at a position that doesn't exist.");
        }
    } else{
        if (dimension.constains(position)) {
            size_t pos = dimension.linearize(position);
            value.vi->at(pos) = i;
            is_set = true;
        } // no else needed, contains fct would have thrown an error already 
    }
}

void chips_ads::dataflow_t::set_value(double f, std::vector<size_t> position)
{
    if (FLOAT_DF != type) {
        throw chips_exception("Cannot store a float in that variable!");
    }
    if ( (dimension.get_cardinality()==1)) {
        if ((position.size()==1) && (position[0] == 0)) {
            value.f = f;
            is_set = true;
        }else{
            throw chips_exception("Cannot store a value at a position that doesn't exist.");
        }
    } else{
        if (dimension.constains(position)) {
            size_t pos = dimension.linearize(position);
            value.vf->at(pos) = f;
            is_set = true;
        } // no else needed, contains fct would have thrown an error already 
    }
}

void chips_ads::dataflow_t::set_value(bool b, std::vector<size_t> position)
{
    if (BOOL_DF != type) {
        throw chips_exception("Cannot store a bool in that variable!");
    }
    if ( (dimension.get_cardinality()==1) ) {
        if ((position.size()==1) && (position.at(0) == 0)) {
            value.b = b;
            is_set = true;
        }else{
            throw chips_exception("Cannot store a value at a position that doesn't exist.");
        }
    } else{
        if (dimension.constains(position)) {
            size_t pos = dimension.linearize(position);
            value.vb->at(pos) = (uint8_t) b;
            is_set = true;
        } // no else needed, contains fct would have thrown an error already 
    }
}

void chips_ads::dataflow_t::set_value(const chips_ads::dataflow_t& other){
    if (this == &other )
        return;
    
    if (other.type != type)
        throw chips_exception("Cannot affect dataflows of different types");
    
    size_t cardinality = dimension.get_cardinality();

    if (other.dimension!=dimension) {
        throw chips_exception("Cannot affect other variable's value : Dataflows of different dimensions");
    }

    switch (type) {
        case INT_DF:
            if (cardinality==1) {
                value.i = other.value.i;
            } else {
                delete value.vi;
                value.vi = new std::vector<int>(*other.value.vi);
            }
            break;

        case FLOAT_DF:
            if (cardinality==1) {
                this->value.f = other.value.f;
            } else {
                delete value.vf;
                value.vf = new std::vector<double>(*other.value.vf);
            }
            break;

        case BOOL_DF:
            if (cardinality==1) {
                this->value.b = other.value.b;
            } else {
                delete value.vb;
                value.vb = new std::vector<uint8_t>(*other.value.vb);
            }
            break;
    }
    is_set = true;
}