#include <cassert>
#include <cstddef>
#include <deque>
#include <iostream>
#include <fstream>
#include <sstream>
#include <utility>
#include <vector>
#include <string>
#include "DataTreatment.cpp"

using namespace std;

vector<vector<string>> loadCSV(const string& filename) {
    vector<vector<string>> data;
    ifstream file(filename);
    string line;

    while (getline(file, line)) {
        vector<string> row;
        stringstream ss(line);
        string value;


        while (getline(ss, value, ';')) {
            row.push_back(value);
        }
        data.push_back(row);
    }

    file.close();
    return data;
}

void saveCSV(const string& filename, const vector<vector<string>>& data) {
    ofstream file(filename);

    for (const auto& row : data) {
        for (size_t i = 0; i < row.size(); ++i) {
            file << row[i];
            if (i < row.size() - 1) file << ";";
        }
        file << "\n";
    }

    file.close();
}

void add_string_row(vector<vector<string>>& data, const vector<string>& newRow) {
    data.push_back(newRow);
}

void add_string_column(vector<vector<string>>& data, const vector<string>& newColumn) {
    assert(newColumn.size()==data.size());
    for(size_t row = 0; row < data.size(); ++row){
        data[row].push_back(newColumn[row]);
    }
}
void add_data_column(dtreatment::treatabledata& data, const string column_name, const vector<float> column_data) {
    data.insert(pair<string, vector<float>>({column_name,column_data}));
}

void remove_data_column(dtreatment::treatabledata& data, const string column_name){
    data.erase(column_name);
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        cerr << "Usage: " << argv[0] << " <csv_input_filename> <csv_output_filename>" << endl;
        return 1;
    }

    string filename = argv[1];
    string csv_output_filename = argv[2];
    vector<vector<string>> data = loadCSV(filename);
    dtreatment::treatabledata treatable_data = dtreatment::to_float(data);
    // DO OPERATIONS HERE
    float window_length = 300.0; // seconds
    assert(window_length > 0);



    vector<float> sliding_avg;
    deque<float> window;
    vector<float> x_column = treatable_data.at("1.TIME");
    vector<float> y_column = treatable_data.at("3.RES_TIME");
    
    sliding_avg.clear();
    window.clear();
    
    int late_index = 0;
    double front_time = x_column[late_index];
    double back_time = x_column[late_index];
    bool windowing = false;

    window.push_back(y_column[late_index]);
    sliding_avg.push_back(y_column[late_index]);
    
    for (size_t i = 1; i < y_column.size(); ++i) {
        while (front_time < back_time-window_length) {
            window.pop_front();
            front_time = x_column[++late_index];
            windowing = true;
        }
        
        // do not separate the 2 following lines
        back_time = x_column[i];
        window.push_back(y_column[i]);
        
        float curr_len = back_time-front_time;
        if(windowing){
            sliding_avg.push_back(window_length*dtreatment::avg(window)/curr_len);
        } else {
            sliding_avg.push_back(dtreatment::avg(window));
        }
    }

    //remove_data_column(treatable_data, "3.RES_TIME");
    add_data_column(treatable_data, "3.RES_TIME_AVG", sliding_avg);

    // SAVING OPERATIONS IN NEW FILE
    vector<vector<string>> modified_data = dtreatment::to_string(treatable_data);
    saveCSV(csv_output_filename, modified_data);

    return 0;
}
