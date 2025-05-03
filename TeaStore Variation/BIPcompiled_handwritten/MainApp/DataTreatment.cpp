#include <cstddef>
#include <deque>
#include <map>
#include <string>
#include <utility>
#include <vector>

namespace dtreatment {

    using treatabledata = std::map<std::string, std::vector<float>>;

    treatabledata to_float(const std::vector<std::vector<std::string>> stringtable) {
        treatabledata data;
        std::vector<std::string> column_names(stringtable[0]);
        for (auto name : column_names) {
            std::pair<std::string, std::vector<float>> column;
            column.first = name;
            column.second = std::vector<float>();
            column.second.reserve(stringtable.size());
            data.insert(column);
        }
        for (size_t row = 1; row < stringtable.size(); ++row) {
            for (size_t col = 0; col<stringtable[0].size(); ++col) {
                data[column_names[col]].push_back(std::stof(stringtable[row][col]));
            }
        }
        return data;
    }
    
    std::vector<std::vector<std::string>> to_string(const treatabledata data) {
        std::vector<std::vector<std::string>> stringtable;
        std::vector<std::string> first_line;
        for (auto name_data : data) {
            first_line.push_back(name_data.first);
        }
        stringtable.push_back(first_line);
        size_t nb_data_cols = first_line.size();
        size_t nb_data_rows = data.at(first_line[0]).size();
    
        for (size_t row = 0; row < nb_data_rows; ++row) {
            std::vector<std::string> current_row;
            for (size_t col = 0; col < nb_data_cols; ++col) {
                std::string col_name = stringtable[0][col];
                current_row.push_back(std::to_string(data.at(col_name)[row]));
            }
            stringtable.push_back(current_row);
        }
    
        return stringtable;
    }


    float avg(const std::deque<float> data){
        float avg = 0;
        size_t nb_elem = 0;
        for (auto elem : data) {
            avg+=elem;
            ++nb_elem;
        }
        return avg/nb_elem;
    }
}


